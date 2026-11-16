#pragma once

#include <map>
#include <string>
#include <vector>

namespace Harness
{
	extern int g_errors;
	extern int g_warnings;
	extern bool g_verbose;
	// cvar values answered by CommandMap::GetVariableString and by `command <Var>`
	extern std::map<std::string, std::string> g_variables;
	// canned bridge results: "<method>" or "command:<full command>"
	extern std::map<std::string, std::string> g_methodResults;
	// every bridge call, "<method> <args json>"
	extern std::vector<std::string> g_calls;
}
