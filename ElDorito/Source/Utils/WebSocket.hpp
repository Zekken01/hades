#ifndef __UTILS_WEBSOCKET_HPP__
#define __UTILS_WEBSOCKET_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <websocketpp/config/core.hpp>
#include <websocketpp/transport/asio/endpoint.hpp>

/* ---------- constants */

/* ---------- definitions */


// Hand-written (Docs/Manual/Utils/WebSocket.hpp), spliced into the generated
// header by generate_source.py on every run.
//
// The PDB records no definition for this struct - only what websocketpp
// instantiated from it survives - so it is written from those instantiations:
// `websocketpp::connection<Utils::WebSocket::Config>` records its concurrency,
// request, response, message, message-manager and rng types, which are
// `websocketpp::config::core`'s defaults (the rng in particular is core's
// `random::none`, not asio's random device); its log types are ED's own
// `Logger<websocketpp::concurrency::basic, ...>`; and
// `websocketpp::transport::asio::endpoint<Utils::WebSocket::Config::transport_config>`
// records the transport as asio over a plain socket, logging through the same
// two loggers. That is websocketpp's documented custom-config pattern, and the
// names below are its.
namespace Utils
{
	namespace WebSocket
	{
		struct Config : public websocketpp::config::core
		{
			typedef Config type;
			typedef websocketpp::config::core base;

			typedef base::concurrency_type concurrency_type;
			typedef base::request_type request_type;
			typedef base::response_type response_type;
			typedef base::message_type message_type;
			typedef base::con_msg_manager_type con_msg_manager_type;
			typedef base::endpoint_msg_manager_type endpoint_msg_manager_type;

			typedef Logger<concurrency_type, websocketpp::log::elevel> elog_type;
			typedef Logger<concurrency_type, websocketpp::log::alevel> alog_type;

			typedef base::rng_type rng_type;

			struct transport_config : public base::transport_config
			{
				typedef type::concurrency_type concurrency_type;
				typedef type::alog_type alog_type;
				typedef type::elog_type elog_type;
				typedef type::request_type request_type;
				typedef type::response_type response_type;
				typedef websocketpp::transport::asio::basic_socket::endpoint socket_type;
			};

			typedef websocketpp::transport::asio::endpoint<transport_config> transport_type;
		};
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __UTILS_WEBSOCKET_HPP__
