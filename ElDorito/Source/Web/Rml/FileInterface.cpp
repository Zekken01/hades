/* ---------- headers */

#include "hades/hades.h"

#include "Web/Rml/FileInterface.hpp"
#include "Web/Rml/SystemInterface.hpp"

#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/FileSystem/ModPackageFileSystemViewManager.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/Uri.hpp"

#include <algorithm>
#include <cctype>

/* ---------- private code */

namespace
{
	std::string PercentDecode(std::string_view in)
	{
		std::string out;
		out.reserve(in.size());
		for (size_t i = 0; i < in.size(); i++)
		{
			if (in[i] == '%' && i + 2 < in.size() && std::isxdigit((unsigned char)in[i + 1]) && std::isxdigit((unsigned char)in[i + 2]))
			{
				out.push_back((char)std::stoi(std::string(in.substr(i + 1, 2)), nullptr, 16));
				i += 2;
			}
			else
				out.push_back(in[i]);
		}
		return out;
	}

	std::string TrimSlashes(std::string path)
	{
		while (!path.empty() && (path.front() == '/' || path.front() == '\\'))
			path.erase(path.begin());
		return path;
	}
}

namespace Web
{
	namespace RmlUi
	{
		FileInterface::FileInterface(std::filesystem::path uiDirectory, std::filesystem::path cacheDirectory)
			: m_uiDirectory(std::move(uiDirectory)), m_cacheDirectory(std::move(cacheDirectory))
		{
		}

		bool FileInterface::Resolve(const std::string &rawUrl, Resolved &out) const
		{
			const std::string url = SystemInterface::NormalizePath(rawUrl);
			Utils::Uri::UriComponents components;
			// A one-letter "scheme" is a Windows drive letter, not a URL.
			if (!Utils::Uri::ParseUriComponents(url, components) || components.scheme.size() <= 1)
			{
				out.fsPath = url;
				out.base = 0;
				out.length = -1;
				return true;
			}
			const std::string scheme(components.scheme);
			const std::string host(components.authority);
			std::string path = PercentDecode(components.path);
			const bool wantsIndex = path.empty() || path.back() == '/';
			path = TrimSlashes(path);
			if (wantsIndex)
				path += path.empty() ? "index.rml" : "/index.rml";

			if (scheme == "dew")
			{
				std::error_code ec;
				std::filesystem::path root = host == "cache" ? m_cacheDirectory : m_uiDirectory / host;
				std::filesystem::path base = std::filesystem::weakly_canonical(host == "cache" ? m_cacheDirectory : m_uiDirectory, ec);
				if (ec)
					return false;
				std::filesystem::path full = std::filesystem::weakly_canonical(root / path, ec);
				if (ec)
					return false;
				// Refuse anything that escapes the ui/cache directory.
				auto [it, _] = std::mismatch(base.begin(), base.end(), full.begin(), full.end());
				if (it != base.end())
					return false;
				out.fsPath = full.string();
				out.base = 0;
				out.length = -1;
				return std::filesystem::exists(full, ec);
			}
			if (scheme == "pak")
			{
				auto view = Utils::Singleton<CModPackageFileSystemViewManager>::Instance().GetView(host);
				CModPackageFileSystemView::SFileEntry entry = {};
				if (!view || !view->GetFileEntry(path, &entry))
					return false;
				out.fsPath = view->GetFilePath();
				out.base = view->GetBaseOffset() + entry.offset;
				out.length = entry.size;
				return true;
			}
			if (scheme == "file")
			{
				out.fsPath = host + path;
				out.base = 0;
				out.length = -1;
				return true;
			}
			return false;
		}

		bool FileInterface::ReadAll(const std::string &url, std::string &out)
		{
			::Rml::FileHandle handle = Open(url);
			if (!handle)
				return false;
			const size_t length = Length(handle);
			out.resize(length);
			const size_t read = length ? Read(out.data(), length, handle) : 0;
			Close(handle);
			out.resize(read);
			return true;
		}

		::Rml::FileHandle FileInterface::Open(const ::Rml::String &path)
		{
			Resolved resolved;
			if (!Resolve(path, resolved))
				return 0;
			auto entry = std::make_unique<Entry>();
			entry->stream.open(resolved.fsPath, std::ios::binary);
			if (!entry->stream.is_open())
				return 0;
			entry->base = resolved.base;
			if (resolved.length < 0)
			{
				entry->stream.seekg(0, std::ios::end);
				entry->length = (long long)entry->stream.tellg() - entry->base;
			}
			else
				entry->length = resolved.length;
			entry->position = 0;
			entry->stream.seekg(entry->base, std::ios::beg);
			return reinterpret_cast<::Rml::FileHandle>(entry.release());
		}

		void FileInterface::Close(::Rml::FileHandle file)
		{
			delete reinterpret_cast<Entry *>(file);
		}

		size_t FileInterface::Read(void *buffer, size_t size, ::Rml::FileHandle file)
		{
			auto *entry = reinterpret_cast<Entry *>(file);
			if (!entry)
				return 0;
			long long remaining = entry->length - entry->position;
			if (remaining <= 0)
				return 0;
			long long count = std::min<long long>((long long)size, remaining);
			entry->stream.seekg(entry->base + entry->position, std::ios::beg);
			entry->stream.read(static_cast<char *>(buffer), count);
			long long got = entry->stream.gcount();
			entry->position += got;
			return (size_t)got;
		}

		bool FileInterface::Seek(::Rml::FileHandle file, long offset, int origin)
		{
			auto *entry = reinterpret_cast<Entry *>(file);
			if (!entry)
				return false;
			long long target;
			switch (origin)
			{
			case SEEK_SET: target = offset; break;
			case SEEK_CUR: target = entry->position + offset; break;
			case SEEK_END: target = entry->length + offset; break;
			default: return false;
			}
			if (target < 0 || target > entry->length)
				return false;
			entry->position = target;
			entry->stream.clear();
			entry->stream.seekg(entry->base + entry->position, std::ios::beg);
			return true;
		}

		size_t FileInterface::Tell(::Rml::FileHandle file)
		{
			auto *entry = reinterpret_cast<Entry *>(file);
			return entry ? (size_t)entry->position : 0;
		}

		size_t FileInterface::Length(::Rml::FileHandle file)
		{
			auto *entry = reinterpret_cast<Entry *>(file);
			return entry ? (size_t)entry->length : 0;
		}
	}
}
