#ifndef __WEB_UI_WEBASSETSERVICE_HPP__
#define __WEB_UI_WEBASSETSERVICE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"

#include <memory>
#include <string>
#include <string_view>
#include <vector>

/* ---------- forward declarations */

namespace Web
{
	namespace Ui
	{
		struct AssetService;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Ui
	{
		struct AssetService
		{
			static std::string FindAssetInModVfs(std::string const &modIdentifier, std::string const &path, std::vector<std::string_view> const &fileTypes);
			static std::string FindAssetInBaseDir(std::string const &path, std::vector<std::string_view> const &fileTypes);
		};
		static_assert(sizeof(Web::Ui::AssetService) == 1, "Invalid Web::Ui::AssetService size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __WEB_UI_WEBASSETSERVICE_HPP__
