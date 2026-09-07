#ifndef __INTERFACE_ERRORDIALOG_HPP__
#define __INTERFACE_ERRORDIALOG_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Web/Ui/ScreenLayer.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

class ErrorDialog;

/* ---------- constants */

/* ---------- definitions */

class ErrorDialog
{
public:
	static void Show(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &title, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &message);
};
static_assert(sizeof(ErrorDialog) == 1, "Invalid ErrorDialog size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __INTERFACE_ERRORDIALOG_HPP__
