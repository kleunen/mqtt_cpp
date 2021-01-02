# Copyright Takatoshi Kondo 2015
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

CMAKE_MINIMUM_REQUIRED (VERSION 3.8.2)

IF (POLICY CMP0074)
  CMAKE_POLICY(SET CMP0074 NEW)
ENDIF ()

IF (MQTT_TEST_1)
    LIST (APPEND check_PROGRAMS
        ut_utf8string_validate.cpp
        ut_packet_id.cpp
        ut_message.cpp
        ut_property.cpp
        ut_subscription_map.cpp
        ut_retained_topic_map.cpp
        ut_shared_subscriptions.cpp
        ut_subscription_map_broker.cpp
        ut_retained_topic_map_broker.cpp
        ut_value_allocator.cpp
    )
ENDIF ()

FIND_PACKAGE (Boost 1.67.0 REQUIRED COMPONENTS unit_test_framework)

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
