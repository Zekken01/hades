#ifndef __WEB_RML_LUAJSON_HPP__
#define __WEB_RML_LUAJSON_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"

#include <RmlUi/Lua/IncludeLua.h>

#include <string>

/* ---------- prototypes */

namespace Web
{
	namespace RmlUi
	{
		// JSON <-> Lua tables.  Objects become tables with string keys; arrays become
		// 1-based sequences tagged with the array metatable so empty arrays round-trip;
		// JSON null becomes the `dew.json.null` light userdata so it survives in tables.
		namespace LuaJson
		{
			// Pushes the Lua value for `value`.
			void Push(lua_State *L, const rapidjson::Value &value);
			// Parses `json` and pushes the result; pushes nil and returns false on a parse error.
			bool PushParsed(lua_State *L, const std::string &json);
			// Writes the Lua value at `index`.
			void Write(lua_State *L, int index, rapidjson::Writer<rapidjson::StringBuffer> &writer);
			// Serialises the Lua value at `index`.
			std::string Stringify(lua_State *L, int index);
			// Builds a rapidjson document from the Lua value at `index`.
			void ToDocument(lua_State *L, int index, rapidjson::Document &document);

			bool IsNull(lua_State *L, int index);
			void PushNull(lua_State *L);
			void MarkArray(lua_State *L, int index);

			// Registers `dew_json` { encode, decode, null, array }.
			void Register(lua_State *L);
		}
	}
}

#endif // __WEB_RML_LUAJSON_HPP__
