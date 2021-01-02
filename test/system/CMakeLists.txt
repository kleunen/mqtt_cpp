# Copyright Takatoshi Kondo 2015
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

CMAKE_MINIMUM_REQUIRED (VERSION 3.8.2)

IF (POLICY CMP0074)
  CMAKE_POLICY(SET CMP0074 NEW)
ENDIF ()

IF (MQTT_TEST_2)
    LIST (APPEND check_PROGRAMS
        st_connect.cpp
        st_underlying_timeout.cpp
        st_as_buffer_sub.cpp
        st_topic_alias_recv.cpp
        st_as_buffer_pubsub.cpp
        st_shared_sub.cpp
    )
ENDIF ()

IF (MQTT_TEST_3)
    LIST (APPEND check_PROGRAMS
        st_pubsub_1.cpp
        st_sub.cpp
        st_pubsub_2.cpp
        st_pubsub_no_strand.cpp
        st_as_buffer_async_pubsub_1.cpp
        st_multi_sub.cpp
        st_as_buffer_async_pubsub_2.cpp
    )
ENDIF ()

IF (MQTT_TEST_4)
    LIST (APPEND check_PROGRAMS
        st_async_pubsub_1.cpp
    )
ENDIF ()

IF (MQTT_TEST_5)
    LIST (APPEND check_PROGRAMS
        st_resend.cpp
        st_retain_1.cpp
        st_resend_new_client.cpp
        st_retain_2.cpp
        st_will.cpp
    )
ENDIF ()

IF (MQTT_TEST_6)
    LIST (APPEND check_PROGRAMS
        st_offline.cpp
        st_manual_publish.cpp
    )
ENDIF ()

IF (MQTT_TEST_7)
    LIST (APPEND check_PROGRAMS
        st_async_pubsub_2.cpp
        st_issue_749.cpp
        st_broker_offline_message.cpp
        st_remaining_length.cpp
        st_utf8string_validate.cpp
        st_resend_serialize.cpp
        st_length_check.cpp
        st_resend_serialize_ptr_size.cpp
    )
ENDIF ()

# Without this setting added, azure pipelines completely fails to find the boost libraries. No idea why.
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF ()

FOREACH (source_file ${check_PROGRAMS})
    GET_FILENAME_COMPONENT (source_file_we ${source_file} NAME_WE)
    ADD_EXECUTABLE (${source_file_we} ${source_file})
    mqttcpp_test_properties(${source_file_we})

    IF (MQTT_USE_PRECOMP)
        TARGET_PRECOMPILE_HEADERS(${source_file_we} REUSE_FROM test_precomp_target)
    ENDIF ()
ENDFOREACH ()

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../certs/mosquitto.org.crt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../certs/server.crt.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../certs/server.key.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../certs/cacert.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
ELSE ()
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../certs/mosquitto.org.crt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../certs/server.crt.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../certs/server.key.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
   FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../certs/cacert.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
ENDIF ()
