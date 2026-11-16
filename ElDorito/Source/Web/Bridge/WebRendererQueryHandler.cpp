/* ---------- headers */

#include "Web/Bridge/WebRendererQueryHandler.hpp"
#include "hades/hades.h"

#include "ThirdParty/rapidjson/document.h"
#include "Web/Ui/Screen.hpp"

#include <string>

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			WebRendererQueryHandler::WebRendererQueryHandler()
			{
			}

			void WebRendererQueryHandler::AddMethod(std::string const &name, Method const &method)
			{
				m_Methods[name] = method;
			}

			bool WebRendererQueryHandler::HasMethod(std::string const &name) const
			{
				return m_Methods.find(name) != m_Methods.end();
			}

			QueryError WebRendererQueryHandler::Invoke(std::string const &name, rapidjson::Value const &args, std::string *result)
			{
				auto it = m_Methods.find(name);
				if (it == m_Methods.end())
				{
					if (result)
						*result = "Unsupported method: \"" + name + "\"";
					return QueryError_UnsupportedMethod;
				}
				if (!args.IsObject())
				{
					if (result)
						*result = "Bad query: \"args\" must be an object";
					return QueryError_BadQuery;
				}
				std::string output;
				QueryError error = it->second(args, &output);
				if (result)
					*result = std::move(output);
				return error;
			}

			QueryError WebRendererQueryHandler::InvokeRequest(std::string const &request, std::string *result)
			{
				rapidjson::Document json;
				json.Parse(request.c_str(), request.size());
				if (json.HasParseError() || !json.IsObject())
				{
					if (result)
						*result = "Bad query: Failed to parse JSON";
					return QueryError_BadQuery;
				}
				auto method = json.FindMember("method");
				if (method == json.MemberEnd() || !method->value.IsString())
				{
					if (result)
						*result = "Bad query: A \"method\" string is required";
					return QueryError_BadQuery;
				}
				auto args = json.FindMember("args");
				if (args == json.MemberEnd())
				{
					if (result)
						*result = "Bad query: An \"args\" value is required";
					return QueryError_BadQuery;
				}
				return Invoke(method->value.GetString(), args->value, result);
			}

			void WebRendererQueryHandler::Update()
			{
			}
		}
	}
}
