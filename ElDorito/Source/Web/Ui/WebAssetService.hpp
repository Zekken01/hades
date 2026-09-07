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
			static std::basic_string<char,std::char_traits<char>,std::allocator<char> > FindAssetInModVfs(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &modIdentifier, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path, std::vector<std::basic_string_view<char,std::char_traits<char> >,std::allocator<std::basic_string_view<char,std::char_traits<char> > > > const &fileTypes);
			static std::basic_string<char,std::char_traits<char>,std::allocator<char> > FindAssetInBaseDir(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path, std::vector<std::basic_string_view<char,std::char_traits<char> >,std::allocator<std::basic_string_view<char,std::char_traits<char> > > > const &fileTypes);
		};
		static_assert(sizeof(Web::Ui::AssetService) == 1, "Invalid Web::Ui::AssetService size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __WEB_UI_WEBASSETSERVICE_HPP__
