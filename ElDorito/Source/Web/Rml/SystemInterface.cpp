/* ---------- headers */

#include "hades/hades.h"

#include "Web/Rml/SystemInterface.hpp"

#include "Console/Console.hpp"
#include "Utils/Logger.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Utils/Uri.hpp"

#include <RmlUi/Core/Log.h>

#include <Windows.h>

#include <cctype>
#include <vector>

/* ---------- public code */

namespace Web
{
	namespace RmlUi
	{
		SystemInterface::SystemInterface()
		{
			LARGE_INTEGER frequency, counter;
			QueryPerformanceFrequency(&frequency);
			QueryPerformanceCounter(&counter);
			m_frequency = frequency.QuadPart ? frequency.QuadPart : 1;
			m_startCounter = counter.QuadPart;
		}

		double SystemInterface::GetElapsedTime()
		{
			LARGE_INTEGER counter;
			QueryPerformanceCounter(&counter);
			return double(counter.QuadPart - m_startCounter) / double(m_frequency);
		}

		bool SystemInterface::LogMessage(::Rml::Log::Type type, const ::Rml::String &message)
		{
			Utils::LogLevel level = Utils::LogLevel::Info;
			const char *prefix = "[RmlUi] ";
			switch (type)
			{
			case ::Rml::Log::LT_ERROR:
			case ::Rml::Log::LT_ASSERT:
				level = Utils::LogLevel::Error;
				prefix = "[RmlUi error] ";
				break;
			case ::Rml::Log::LT_WARNING:
				level = Utils::LogLevel::Warning;
				prefix = "[RmlUi warning] ";
				break;
			case ::Rml::Log::LT_DEBUG:
				level = Utils::LogLevel::Trace;
				break;
			default:
				break;
			}
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, level, prefix + message);
			if (type <= ::Rml::Log::LT_WARNING)
				Console::WriteLine(prefix + message);
			return true;
		}

		void SystemInterface::JoinPath(::Rml::String &translated_path, const ::Rml::String &document_path, const ::Rml::String &path)
		{
			// RmlUi's default treats ':' specially (it stores paths with ':' as '|'), which breaks
			// dew:// and pak:// bases, so URLs are resolved here.
			const std::string target = NormalizePath(path);
			const std::string base = NormalizePath(document_path);
			if (HasScheme(target))
			{
				translated_path = target;
				return;
			}
			const size_t schemeEnd = base.find("://");
			if (schemeEnd == std::string::npos)
			{
				::Rml::SystemInterface::JoinPath(translated_path, document_path, path);
				return;
			}
			const size_t authorityEnd = base.find('/', schemeEnd + 3);
			const std::string origin = base.substr(0, authorityEnd == std::string::npos ? base.size() : authorityEnd);
			std::string joined;
			if (!target.empty() && target[0] == '/')
				joined = origin + target;
			else
			{
				const size_t lastSlash = base.rfind('/');
				const std::string directory = (authorityEnd == std::string::npos || lastSlash < authorityEnd) ? origin + "/" : base.substr(0, lastSlash + 1);
				joined = directory + target;
			}
			// collapse "." and ".." in the path part
			const size_t pathStart = joined.find('/', schemeEnd + 3);
			if (pathStart != std::string::npos)
			{
				std::vector<std::string> segments;
				size_t position = pathStart + 1;
				std::string rest = joined.substr(position);
				size_t queryStart = rest.find_first_of("?#");
				std::string suffix = queryStart == std::string::npos ? "" : rest.substr(queryStart);
				rest = rest.substr(0, queryStart);
				size_t begin = 0;
				while (begin <= rest.size())
				{
					size_t slash = rest.find('/', begin);
					std::string segment = rest.substr(begin, slash == std::string::npos ? std::string::npos : slash - begin);
					if (segment == "..")
					{
						if (!segments.empty())
							segments.pop_back();
					}
					else if (segment != ".")
						segments.push_back(segment);
					if (slash == std::string::npos)
						break;
					begin = slash + 1;
				}
				std::string normalized = joined.substr(0, pathStart);
				for (auto &segment : segments)
					normalized += "/" + segment;
				joined = normalized + suffix;
			}
			translated_path = joined;
		}

		std::string SystemInterface::NormalizePath(const std::string &path)
		{
			// "dew|//x" -> "dew://x"
			std::string out = path;
			const size_t bar = out.find("|//");
			if (bar != std::string::npos && bar > 1)
				out[bar] = ':';
			return out;
		}

		bool SystemInterface::HasScheme(const std::string &path)
		{
			const size_t colon = path.find("://");
			if (colon == std::string::npos || colon < 2)
				return false;
			for (size_t i = 0; i < colon; i++)
				if (!std::isalnum((unsigned char)path[i]) && path[i] != '+' && path[i] != '-' && path[i] != '.')
					return false;
			return true;
		}

		void SystemInterface::SetMouseCursor(const ::Rml::String &cursor_name)
		{
			LPCSTR id = IDC_ARROW;
			if (cursor_name == "move")
				id = IDC_SIZEALL;
			else if (cursor_name == "pointer")
				id = IDC_HAND;
			else if (cursor_name == "resize")
				id = IDC_SIZENWSE;
			else if (cursor_name == "cross")
				id = IDC_CROSS;
			else if (cursor_name == "text")
				id = IDC_IBEAM;
			else if (cursor_name == "unavailable")
				id = IDC_NO;
			else if (cursor_name.rfind("rmlui-scroll", 0) == 0)
				id = IDC_SIZEALL;
			m_cursor = LoadCursorA(nullptr, id);
			::SetCursor(m_cursor);
		}

		void SystemInterface::ReapplyCursor()
		{
			if (m_cursor)
				::SetCursor(m_cursor);
		}

		void SystemInterface::SetClipboardText(const ::Rml::String &text)
		{
			if (!OpenClipboard(nullptr))
				return;
			EmptyClipboard();
			const std::wstring wide = Utils::String::WidenString(text);
			const size_t bytes = (wide.size() + 1) * sizeof(wchar_t);
			if (HGLOBAL mem = GlobalAlloc(GMEM_MOVEABLE, bytes))
			{
				if (void *dst = GlobalLock(mem))
				{
					memcpy(dst, wide.c_str(), bytes);
					GlobalUnlock(mem);
					SetClipboardData(CF_UNICODETEXT, mem);
				}
			}
			CloseClipboard();
		}

		void SystemInterface::GetClipboardText(::Rml::String &text)
		{
			text.clear();
			if (!OpenClipboard(nullptr))
				return;
			if (HANDLE data = GetClipboardData(CF_UNICODETEXT))
			{
				if (const wchar_t *wide = static_cast<const wchar_t *>(GlobalLock(data)))
				{
					text = Utils::String::ThinString(wide);
					GlobalUnlock(data);
				}
			}
			CloseClipboard();
		}
	}
}
