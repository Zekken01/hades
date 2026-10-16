#include "SavedFilms/saved_film.hpp"

#include <stdlib.h>
#include <string.h>
#include <time.h>

namespace SavedFilms
{
	namespace
	{
		auto const s_blf_saved_film_constructor = reinterpret_cast<void(__thiscall *)(void *)>(0x00ADC520);
		auto const simulation_update_write_to_buffer = reinterpret_cast<bool (*)(void const *, long, unsigned char *, long *)>(0x00442840);
		auto const simulation_update_read_from_buffer = reinterpret_cast<bool (*)(void *, long, unsigned char const *)>(0x004427C0);

		long const k_game_options_size = 0x24B48;

		// One encode/decode buffer; updates are far smaller than this.
		unsigned char g_update_buffer[k_saved_film_header_size];

		unsigned long byteswap(unsigned long value)
		{
			return _byteswap_ulong(value);
		}
	}

	c_saved_film::c_saved_film() :
		m_file(nullptr),
		m_writing(false),
		m_big_endian(false),
		m_fatal_error(false),
		m_current_offset(0),
		m_end_of_data_offset(0),
		m_current_tick(0)
	{
	}

	c_saved_film::~c_saved_film()
	{
		close();
	}

	unsigned long c_saved_film::read_header_long(long offset) const
	{
		unsigned long value;
		memcpy(&value, &m_header[offset], sizeof(value));
		return m_big_endian ? byteswap(value) : value;
	}

	void c_saved_film::write_header_long(long offset, unsigned long value)
	{
		if (m_big_endian)
			value = byteswap(value);
		memcpy(&m_header[offset], &value, sizeof(value));
	}

	bool c_saved_film::has_mod_info() const
	{
		return !m_header.empty() && memcmp(&m_header[k_film_header_mod_offset], "HADESMOD", 8) == 0;
	}

	std::string c_saved_film::get_mod_hash() const
	{
		if (m_header.empty() || memcmp(&m_header[k_film_header_mod_offset], "HADESMOD", 8) != 0)
			return "";
		return std::string(reinterpret_cast<char const *>(&m_header[k_film_header_mod_hash_offset]), strnlen(reinterpret_cast<char const *>(&m_header[k_film_header_mod_hash_offset]), 63));
	}

	std::string c_saved_film::get_mod_file() const
	{
		if (m_header.empty() || memcmp(&m_header[k_film_header_mod_offset], "HADESMOD", 8) != 0)
			return "";
		return std::string(reinterpret_cast<char const *>(&m_header[k_film_header_mod_file_offset]), strnlen(reinterpret_cast<char const *>(&m_header[k_film_header_mod_file_offset]), 259));
	}

	bool c_saved_film::open_for_write(char const *path, s_game_options const *options, char const *mod_hash, char const *mod_file)
	{
		close();

		if (fopen_s(&m_file, path, "wb") != 0 || !m_file)
		{
			m_file = nullptr;
			return false;
		}

		// The game's own constructor lays out the chunk headers.
		m_header.assign(k_saved_film_header_size, 0);
		s_blf_saved_film_constructor(m_header.data());

		// 'flmd' reads as text in memory when the chunks are big-endian.
		m_big_endian = memcmp(&m_header[k_film_data_offset], "flmd", 4) == 0;

		memcpy(&m_header[k_film_header_game_options_offset], options, k_game_options_size);
		write_header_long(k_film_header_recorded_time_offset, unsigned long(time(nullptr)));

		memcpy(&m_header[k_film_header_mod_offset], "HADESMOD", 8);
		strncpy_s(reinterpret_cast<char *>(&m_header[k_film_header_mod_hash_offset]), 64, mod_hash ? mod_hash : "", _TRUNCATE);
		strncpy_s(reinterpret_cast<char *>(&m_header[k_film_header_mod_file_offset]), 260, mod_file ? mod_file : "", _TRUNCATE);

		m_writing = true;
		m_fatal_error = false;
		m_current_tick = 0;
		m_path = path;

		if (fwrite(m_header.data(), 1, m_header.size(), m_file) != m_header.size())
		{
			close();
			return false;
		}
		m_current_offset = k_saved_film_header_size;
		return true;
	}

	bool c_saved_film::write_simulation_update(void const *simulation_update)
	{
		if (!m_file || !m_writing || m_fatal_error)
			return false;

		long length = 0;
		if (!simulation_update_write_to_buffer(simulation_update, sizeof(g_update_buffer), g_update_buffer, &length) || length <= 0 || length > k_saved_film_update_size_max)
		{
			m_fatal_error = true;
			return false;
		}

		if (m_current_offset + long(sizeof(unsigned long)) + length + k_saved_film_header_size >= k_saved_film_maximum_size)
			return false;

		unsigned long record = unsigned long(length) | (unsigned long(_saved_film_update_type_simulation_update) << k_saved_film_update_size_bits);
		if (fwrite(&record, sizeof(record), 1, m_file) != 1 || fwrite(g_update_buffer, 1, length, m_file) != size_t(length))
		{
			m_fatal_error = true;
			return false;
		}

		m_current_offset += sizeof(record) + length;
		m_current_tick++;
		return true;
	}

	bool c_saved_film::write_finish()
	{
		long data_end = m_current_offset;

		// '_eof' chunk: header, total file size, authentication type.
		unsigned char end_of_file[0x11] = {};
		auto put_long = [&](long offset, unsigned long value)
		{
			if (m_big_endian)
				value = byteswap(value);
			memcpy(&end_of_file[offset], &value, sizeof(value));
		};
		memcpy(end_of_file, m_big_endian ? "_eof" : "foe_", 4);
		put_long(4, sizeof(end_of_file));
		unsigned short version = m_big_endian ? 0x0100 : 0x0001;
		memcpy(&end_of_file[8], &version, 2);
		memcpy(&end_of_file[10], &version, 2);
		put_long(12, unsigned long(data_end));
		if (fwrite(end_of_file, 1, sizeof(end_of_file), m_file) != sizeof(end_of_file))
			return false;

		write_header_long(k_film_header_length_in_ticks_offset, unsigned long(m_current_tick));
		write_header_long(k_film_data_offset + 4, unsigned long(data_end - k_saved_film_header_size + 0xC));

		if (fseek(m_file, 0, SEEK_SET) != 0 || fwrite(m_header.data(), 1, m_header.size(), m_file) != m_header.size())
			return false;
		return true;
	}

	bool c_saved_film::open_for_read(char const *path)
	{
		close();

		if (fopen_s(&m_file, path, "rb") != 0 || !m_file)
		{
			m_file = nullptr;
			return false;
		}

		m_header.assign(k_saved_film_header_size, 0);
		if (fread(m_header.data(), 1, m_header.size(), m_file) != m_header.size())
		{
			close();
			return false;
		}

		if (memcmp(&m_header[k_film_data_offset], "flmd", 4) == 0)
			m_big_endian = true;
		else if (memcmp(&m_header[k_film_data_offset], "dmlf", 4) == 0)
			m_big_endian = false;
		else
		{
			close();
			return false;
		}

		long data_size = long(read_header_long(k_film_data_offset + 4)) - 0xC;
		if (data_size < 0 || data_size > k_saved_film_maximum_size)
		{
			close();
			return false;
		}

		m_writing = false;
		m_current_offset = k_saved_film_header_size;
		m_end_of_data_offset = k_saved_film_header_size + data_size;
		m_current_tick = 0;
		m_path = path;
		return true;
	}

	bool c_saved_film::read_simulation_update(void *simulation_update_out)
	{
		if (!m_file || m_writing || at_end())
			return false;

		unsigned long record;
		if (fread(&record, sizeof(record), 1, m_file) != 1)
			return false;

		long type = long(record >> k_saved_film_update_size_bits);
		long size = long(record & k_saved_film_update_size_max);
		if (size <= 0 || size > long(sizeof(g_update_buffer)) || fread(g_update_buffer, 1, size, m_file) != size_t(size))
			return false;
		m_current_offset += sizeof(record) + size;

		if (type != _saved_film_update_type_simulation_update)
			return read_simulation_update(simulation_update_out); // game states are not used for playback from the start

		memset(simulation_update_out, 0, k_simulation_update_size);
		if (!simulation_update_read_from_buffer(simulation_update_out, size, g_update_buffer))
			return false;

		m_current_tick++;
		return true;
	}

	bool c_saved_film::at_end() const
	{
		return m_current_offset >= m_end_of_data_offset;
	}

	void c_saved_film::close()
	{
		if (!m_file)
			return;

		if (m_writing)
			write_finish();

		fclose(m_file);
		m_file = nullptr;
		m_writing = false;
	}

	bool c_saved_film::is_open() const
	{
		return m_file != nullptr;
	}

	bool c_saved_film::is_writing() const
	{
		return m_file && m_writing;
	}

	s_game_options const *c_saved_film::get_game_options() const
	{
		return m_header.empty() ? nullptr : reinterpret_cast<s_game_options const *>(&m_header[k_film_header_game_options_offset]);
	}

	long c_saved_film::get_current_tick() const
	{
		return m_current_tick;
	}

	long c_saved_film::get_length_in_ticks() const
	{
		return m_header.empty() ? 0 : long(read_header_long(k_film_header_length_in_ticks_offset));
	}

	std::string const &c_saved_film::get_path() const
	{
		return m_path;
	}
}
