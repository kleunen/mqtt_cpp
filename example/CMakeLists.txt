LIST (APPEND exec_PROGRAMS
    no_tls_client.cpp
    no_tls_async_client.cpp
    no_tls_server.cpp
    no_tls_both.cpp
    v5_no_tls_client.cpp
    v5_no_tls_server.cpp
    v5_no_tls_both.cpp
    v5_no_tls_prop.cpp
    redirect.cpp
    broker.cpp
)

IF (MQTT_USE_TLS)
    LIST (APPEND exec_PROGRAMS
        tls_client.cpp
        tls_server.cpp
        tls_both.cpp
    )
ENDIF ()

IF (MQTT_USE_WS)
    LIST (APPEND exec_PROGRAMS
        no_tls_ws_client.cpp
        no_tls_ws_server.cpp
        no_tls_ws_both.cpp
    )
ENDIF ()

IF (MQTT_USE_WS AND MQTT_USE_TLS)
    LIST (APPEND exec_PROGRAMS
        tls_ws_client.cpp
        tls_ws_server.cpp
        tls_ws_both.cpp
    )
ENDIF ()

IF (MQTT_USE_LOG)
    LIST (APPEND exec_PROGRAMS
        logging.cpp
    )
ENDIF ()

# Without this setting added, azure pipelines completely fails to find the boost libraries. No idea why.
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF ()

IF (MQTT_USE_PRECOMP)
    add_library(example_precomp_target SHARED ${PROJECT_SOURCE_DIR}/helper/precomp.cpp)
    target_precompile_headers(example_precomp_target PUBLIC ${PROJECT_SOURCE_DIR}/helper/precomp.hpp)
    TARGET_LINK_LIBRARIES (example_precomp_target mqtt_cpp_iface)

    IF (MQTT_USE_LOG)
        TARGET_COMPILE_DEFINITIONS (example_precomp_target PUBLIC $<IF:$<BOOL:${MQTT_USE_STATIC_BOOST}>,,BOOST_LOG_DYN_LINK>)
        TARGET_LINK_LIBRARIES (example_precomp_target Boost::log)
    ENDIF ()

    TARGET_COMPILE_DEFINITIONS (example_precomp_target PUBLIC $<IF:$<BOOL:${MQTT_USE_STATIC_BOOST}>,,BOOST_PROGRAM_OPTIONS_DYN_LINK>)
    TARGET_LINK_LIBRARIES (example_precomp_target Boost::program_options)
ENDIF ()

FOREACH (source_file ${exec_PROGRAMS})
    GET_FILENAME_COMPONENT (source_file_we ${source_file} NAME_WE)
    ADD_EXECUTABLE (${source_file_we} ${source_file})
    TARGET_LINK_LIBRARIES (${source_file_we} mqtt_cpp_iface)

    IF (MQTT_USE_PRECOMP)
           TARGET_PRECOMPILE_HEADERS(${source_file_we} REUSE_FROM example_precomp_target)
           TARGET_LINK_LIBRARIES (${source_file_we} example_precomp_target)
           IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
               SET_PROPERTY (TARGET ${source_file_we} APPEND_STRING PROPERTY COMPILE_FLAGS " -fPIC")
           ENDIF ()
    ENDIF ()

    IF (MQTT_USE_LOG)
        TARGET_COMPILE_DEFINITIONS (${source_file_we} PUBLIC $<IF:$<BOOL:${MQTT_USE_STATIC_BOOST}>,,BOOST_LOG_DYN_LINK>)
        TARGET_LINK_LIBRARIES (${source_file_we} Boost::log)
    ENDIF ()
    TARGET_COMPILE_DEFINITIONS (${source_file_we} PUBLIC $<IF:$<BOOL:${MQTT_USE_STATIC_BOOST}>,,BOOST_PROGRAM_OPTIONS_DYN_LINK>)
    TARGET_LINK_LIBRARIES (${source_file_we} Boost::program_options)

ENDFOREACH ()

FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../example/broker.conf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../test/certs/server.crt.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../test/certs/server.key.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../test/certs/cacert.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../test/certs/mosquitto.org.crt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../test/certs/server.crt.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../test/certs/server.key.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../test/certs/cacert.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
ELSE ()
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../test/certs/mosquitto.org.crt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../test/certs/server.crt.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../test/certs/server.key.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../test/certs/cacert.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
ENDIF ()
