#ifndef __WEB_RML_SYSTEMINTERFACE_HPP__
#define __WEB_RML_SYSTEMINTERFACE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <RmlUi/Core/SystemInterface.h>

#include <Windows.h>

#include <string>

/* ---------- definitions */

namespace Web
{
	namespace RmlUi
	{
		class SystemInterface final : public ::Rml::SystemInterface
		{
		public:
			SystemInterface();

			double GetElapsedTime() override;
			bool LogMessage(::Rml::Log::Type type, const ::Rml::String &message) override;
			void JoinPath(::Rml::String &translated_path, const ::Rml::String &document_path, const ::Rml::String &path) override;
			void SetMouseCursor(const ::Rml::String &cursor_name) override;
			void SetClipboardText(const ::Rml::String &text) override;
			void GetClipboardText(::Rml::String &text) override;

			// Re-applies the cursor RmlUi last asked for (the game resets it on WM_SETCURSOR).
			void ReapplyCursor();

			// RmlUi keeps paths with ':' replaced by '|'; this undoes it for "scheme|//".
			static std::string NormalizePath(const std::string &path);
			static bool HasScheme(const std::string &path);

		private:
			long long m_startCounter = 0;
			long long m_frequency = 1;
			HCURSOR m_cursor = nullptr;
		};
	}
}

#endif // __WEB_RML_SYSTEMINTERFACE_HPP__
