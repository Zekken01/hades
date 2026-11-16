#ifndef __WEB_RML_FILEINTERFACE_HPP__
#define __WEB_RML_FILEINTERFACE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <RmlUi/Core/FileInterface.h>

#include <filesystem>
#include <fstream>
#include <string>

/* ---------- definitions */

namespace Web
{
	namespace RmlUi
	{
		// Resolves the UI's URL schemes to files:
		//   dew://<host>/<path>   -> <ui dir>/<host>/<path> (never outside the ui dir)
		//   dew://cache/<path>    -> <cache dir>/<path> (downloaded images)
		//   pak://<sha1|vfsid>/<path> -> a byte window inside a mod package
		//   anything else         -> a plain file path
		class FileInterface final : public ::Rml::FileInterface
		{
		public:
			struct Resolved
			{
				std::string fsPath;
				long long base = 0;
				long long length = -1; // -1: to end of file
			};

			FileInterface(std::filesystem::path uiDirectory, std::filesystem::path cacheDirectory);

			bool Resolve(const std::string &url, Resolved &out) const;
			bool ReadAll(const std::string &url, std::string &out);
			const std::filesystem::path &GetUiDirectory() const { return m_uiDirectory; }
			const std::filesystem::path &GetCacheDirectory() const { return m_cacheDirectory; }

			::Rml::FileHandle Open(const ::Rml::String &path) override;
			void Close(::Rml::FileHandle file) override;
			size_t Read(void *buffer, size_t size, ::Rml::FileHandle file) override;
			bool Seek(::Rml::FileHandle file, long offset, int origin) override;
			size_t Tell(::Rml::FileHandle file) override;
			size_t Length(::Rml::FileHandle file) override;

		private:
			struct Entry
			{
				std::ifstream stream;
				long long base = 0;
				long long length = 0;
				long long position = 0;
			};

			std::filesystem::path m_uiDirectory;
			std::filesystem::path m_cacheDirectory;
		};
	}
}

#endif // __WEB_RML_FILEINTERFACE_HPP__
