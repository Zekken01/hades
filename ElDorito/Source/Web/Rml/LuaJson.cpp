/* ---------- headers */

#include "hades/hades.h"

#include "Web/Rml/LuaJson.hpp"

#include <cmath>
#include <cstring>

/* ---------- private code */

namespace
{
	const char kArrayMetatable[] = "dew.json.array";
	const int kMaxDepth = 64;
	int g_nullSentinel = 0; // the address is the sentinel

	void PushArrayMetatable(lua_State *L)
	{
		if (luaL_newmetatable(L, kArrayMetatable))
		{
			lua_pushstring(L, "array");
			lua_setfield(L, -2, "__jsontype");
		}
	}

	bool IsMarkedArray(lua_State *L, int index)
	{
		if (!lua_getmetatable(L, index))
			return false;
		lua_getfield(L, -1, "__jsontype");
		const char *type = lua_tostring(L, -1);
		const bool isArray = type && std::strcmp(type, "array") == 0;
		lua_pop(L, 2);
		return isArray;
	}

	// A table is written as an array when it is marked, or when its keys are exactly 1..n.
	bool LooksLikeArray(lua_State *L, int index, lua_Integer &lengthOut)
	{
		lengthOut = (lua_Integer)lua_rawlen(L, index);
		if (IsMarkedArray(L, index))
			return true;
		if (lengthOut == 0)
			return false;
		lua_Integer count = 0;
		lua_pushnil(L);
		while (lua_next(L, index) != 0)
		{
			lua_pop(L, 1);
			if (lua_type(L, -1) != LUA_TNUMBER || !lua_isinteger(L, -1))
			{
				lua_pop(L, 1);
				return false;
			}
			const lua_Integer key = lua_tointeger(L, -1);
			if (key < 1 || key > lengthOut)
			{
				lua_pop(L, 1);
				return false;
			}
			count++;
		}
		return count == lengthOut;
	}

	void PushImpl(lua_State *L, const rapidjson::Value &value, int depth)
	{
		luaL_checkstack(L, 4, "json nesting too deep");
		switch (value.GetType())
		{
		case rapidjson::kNullType:
			Web::RmlUi::LuaJson::PushNull(L);
			break;
		case rapidjson::kFalseType:
		case rapidjson::kTrueType:
			lua_pushboolean(L, value.GetBool());
			break;
		case rapidjson::kNumberType:
			if (value.IsInt())
				lua_pushinteger(L, value.GetInt());
			else if (value.IsInt64())
				lua_pushinteger(L, value.GetInt64());
			else if (value.IsUint64() && value.GetUint64() <= (uint64_t)INT64_MAX)
				lua_pushinteger(L, (lua_Integer)value.GetUint64());
			else
				lua_pushnumber(L, value.GetDouble());
			break;
		case rapidjson::kStringType:
			lua_pushlstring(L, value.GetString(), value.GetStringLength());
			break;
		case rapidjson::kArrayType:
			lua_createtable(L, (int)value.Size(), 0);
			if (depth < kMaxDepth)
			{
				lua_Integer i = 1;
				for (auto it = value.Begin(); it != value.End(); ++it, ++i)
				{
					PushImpl(L, *it, depth + 1);
					lua_rawseti(L, -2, i);
				}
			}
			PushArrayMetatable(L);
			lua_setmetatable(L, -2);
			break;
		case rapidjson::kObjectType:
			lua_createtable(L, 0, (int)value.MemberCount());
			if (depth < kMaxDepth)
			{
				for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it)
				{
					lua_pushlstring(L, it->name.GetString(), it->name.GetStringLength());
					PushImpl(L, it->value, depth + 1);
					lua_rawset(L, -3);
				}
			}
			break;
		}
	}

	void WriteImpl(lua_State *L, int index, rapidjson::Writer<rapidjson::StringBuffer> &writer, int depth)
	{
		index = lua_absindex(L, index);
		luaL_checkstack(L, 4, "json nesting too deep");
		switch (lua_type(L, index))
		{
		case LUA_TBOOLEAN:
			writer.Bool(lua_toboolean(L, index) != 0);
			break;
		case LUA_TNUMBER:
			if (lua_isinteger(L, index))
				writer.Int64(lua_tointeger(L, index));
			else
			{
				const double number = lua_tonumber(L, index);
				if (std::isfinite(number))
					writer.Double(number);
				else
					writer.Null();
			}
			break;
		case LUA_TSTRING:
		{
			size_t length = 0;
			const char *str = lua_tolstring(L, index, &length);
			writer.String(str, (rapidjson::SizeType)length);
			break;
		}
		case LUA_TTABLE:
		{
			if (depth >= kMaxDepth)
			{
				writer.Null();
				break;
			}
			lua_Integer length = 0;
			if (LooksLikeArray(L, index, length))
			{
				writer.StartArray();
				for (lua_Integer i = 1; i <= length; i++)
				{
					lua_rawgeti(L, index, i);
					WriteImpl(L, -1, writer, depth + 1);
					lua_pop(L, 1);
				}
				writer.EndArray();
			}
			else
			{
				writer.StartObject();
				lua_pushnil(L);
				while (lua_next(L, index) != 0)
				{
					// key at -2, value at -1; keys are stringified without disturbing numeric keys
					if (lua_type(L, -2) == LUA_TSTRING)
					{
						size_t length = 0;
						const char *key = lua_tolstring(L, -2, &length);
						writer.Key(key, (rapidjson::SizeType)length);
						WriteImpl(L, -1, writer, depth + 1);
					}
					else if (lua_type(L, -2) == LUA_TNUMBER)
					{
						lua_pushvalue(L, -2);
						const char *key = lua_tostring(L, -1);
						writer.Key(key);
						lua_pop(L, 1);
						WriteImpl(L, -1, writer, depth + 1);
					}
					lua_pop(L, 1);
				}
				writer.EndObject();
			}
			break;
		}
		default:
			writer.Null();
			break;
		}
	}

	int LuaEncode(lua_State *L)
	{
		const std::string json = Web::RmlUi::LuaJson::Stringify(L, 1);
		lua_pushlstring(L, json.data(), json.size());
		return 1;
	}

	int LuaDecode(lua_State *L)
	{
		size_t length = 0;
		const char *text = luaL_checklstring(L, 1, &length);
		if (!Web::RmlUi::LuaJson::PushParsed(L, std::string(text, length)))
		{
			lua_pushnil(L);
			lua_pushstring(L, "invalid json");
			return 2;
		}
		return 1;
	}

	int LuaArray(lua_State *L)
	{
		if (lua_isnoneornil(L, 1))
			lua_newtable(L);
		else
		{
			luaL_checktype(L, 1, LUA_TTABLE);
			lua_pushvalue(L, 1);
		}
		Web::RmlUi::LuaJson::MarkArray(L, -1);
		return 1;
	}
}

/* ---------- public code */

namespace Web
{
	namespace RmlUi
	{
		namespace LuaJson
		{
			void Push(lua_State *L, const rapidjson::Value &value)
			{
				PushImpl(L, value, 0);
			}

			bool PushParsed(lua_State *L, const std::string &json)
			{
				rapidjson::Document document;
				document.Parse(json.c_str(), json.size());
				if (document.HasParseError())
				{
					lua_pushnil(L);
					return false;
				}
				PushImpl(L, document, 0);
				return true;
			}

			void Write(lua_State *L, int index, rapidjson::Writer<rapidjson::StringBuffer> &writer)
			{
				WriteImpl(L, index, writer, 0);
			}

			std::string Stringify(lua_State *L, int index)
			{
				rapidjson::StringBuffer buffer;
				rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
				WriteImpl(L, index, writer, 0);
				return std::string(buffer.GetString(), buffer.GetSize());
			}

			void ToDocument(lua_State *L, int index, rapidjson::Document &document)
			{
				const std::string json = Stringify(L, index);
				document.Parse(json.c_str(), json.size());
			}

			bool IsNull(lua_State *L, int index)
			{
				return lua_type(L, index) == LUA_TLIGHTUSERDATA && lua_touserdata(L, index) == &g_nullSentinel;
			}

			void PushNull(lua_State *L)
			{
				lua_pushlightuserdata(L, &g_nullSentinel);
			}

			void MarkArray(lua_State *L, int index)
			{
				index = lua_absindex(L, index);
				PushArrayMetatable(L);
				lua_setmetatable(L, index);
			}

			void Register(lua_State *L)
			{
				lua_newtable(L);
				lua_pushcfunction(L, LuaEncode);
				lua_setfield(L, -2, "encode");
				lua_pushcfunction(L, LuaDecode);
				lua_setfield(L, -2, "decode");
				lua_pushcfunction(L, LuaArray);
				lua_setfield(L, -2, "array");
				PushNull(L);
				lua_setfield(L, -2, "null");
				lua_setglobal(L, "dew_json");
			}
		}
	}
}
