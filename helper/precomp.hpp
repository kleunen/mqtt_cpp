// Copyright Takatoshi Kondo 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(MQTT_PRECOMP_HPP)
#define MQTT_PRECOMP_HPP

#include <mqtt_client_cpp.hpp>
#include <mqtt_server_cpp.hpp>

namespace MQTT_NS {

extern template callable_overlay<async_client<tcp_endpoint<as::ip::tcp::socket, as::io_context::strand>>>;
extern template callable_overlay<async_client<tcp_endpoint<as::ip::tcp::socket, null_strand>>>;

extern template server<as::io_context::strand, std::mutex, std::lock_guard, 2>;

#if defined(MQTT_USE_WS)
extern template callable_overlay<async_client<ws_endpoint<as::ip::tcp::socket, as::io_context::strand>>>;
extern template callable_overlay<async_client<ws_endpoint<as::ip::tcp::socket, null_strand>>>;

extern template server_ws<as::io_context::strand, std::mutex, std::lock_guard, 2>;

#endif // defined(MQTT_USE_WS)

#if defined(MQTT_USE_TLS)
extern template callable_overlay<async_client<tcp_endpoint<tls::stream<as::ip::tcp::socket>, as::io_context::strand>>>;
extern template callable_overlay<async_client<tcp_endpoint<tls::stream<as::ip::tcp::socket>, null_strand>>>;

extern template server_tls<as::io_context::strand, std::mutex, std::lock_guard, 2>;

#if defined(MQTT_USE_WS)
extern template callable_overlay<async_client<ws_endpoint<tls::stream<as::ip::tcp::socket>, as::io_context::strand>>>;
extern template callable_overlay<async_client<ws_endpoint<tls::stream<as::ip::tcp::socket>, null_strand>>>;

extern template server_tls_ws<as::io_context::strand, std::mutex, std::lock_guard, 2>;

#endif // defined(MQTT_USE_WS)

#endif // defined(MQTT_USE_TLS)

}

#endif // !defined(MQTT_PRECOMP_HPP)
