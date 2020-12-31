#include "precomp.hpp"

namespace MQTT_NS {

template struct callable_overlay<async_client<tcp_endpoint<as::ip::tcp::socket, as::io_context::strand>>>;
template struct callable_overlay<async_client<tcp_endpoint<as::ip::tcp::socket, null_strand>>>;

template class server<as::io_context::strand, std::mutex, std::lock_guard, 2>;

#if defined(MQTT_USE_WS)
template struct callable_overlay<async_client<ws_endpoint<as::ip::tcp::socket, as::io_context::strand>>>;
template struct callable_overlay<async_client<ws_endpoint<as::ip::tcp::socket, null_strand>>>;

template class server_ws<as::io_context::strand, std::mutex, std::lock_guard, 2>;
#endif // defined(MQTT_USE_WS)

#if defined(MQTT_USE_TLS)
template struct callable_overlay<async_client<tcp_endpoint<tls::stream<as::ip::tcp::socket>, as::io_context::strand>>>;
template struct callable_overlay<async_client<tcp_endpoint<tls::stream<as::ip::tcp::socket>, null_strand>>>;

template class server_tls<as::io_context::strand, std::mutex, std::lock_guard, 2>;

#if defined(MQTT_USE_WS)
template struct callable_overlay<async_client<ws_endpoint<tls::stream<as::ip::tcp::socket>, as::io_context::strand>>>;
template struct callable_overlay<async_client<ws_endpoint<tls::stream<as::ip::tcp::socket>, null_strand>>>;

template class server_tls_ws<as::io_context::strand, std::mutex, std::lock_guard, 2>;

#endif // defined(MQTT_USE_WS)

#endif // defined(MQTT_USE_TLS)


}
