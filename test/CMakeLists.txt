# Copyright Takatoshi Kondo 2020
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

OPTION(MQTT_TEST_1 "Build test part1" ON)
OPTION(MQTT_TEST_2 "Build test part2" ON)
OPTION(MQTT_TEST_3 "Build test part3" ON)
OPTION(MQTT_TEST_4 "Build test part4" ON)
OPTION(MQTT_TEST_5 "Build test part5" ON)
OPTION(MQTT_TEST_6 "Build test part6" ON)
OPTION(MQTT_TEST_7 "Build test part7" ON)

IF (MQTT_USE_PRECOMP)
    add_library(test_precomp_target ${PROJECT_SOURCE_DIR}/helper/precomp.cpp)
    target_precompile_headers(test_precomp_target PUBLIC ${PROJECT_SOURCE_DIR}/helper/precomp.hpp)
    TARGET_LINK_LIBRARIES (test_precomp_target mqtt_cpp_iface)

    TARGET_COMPILE_DEFINITIONS (test_precomp_target PUBLIC $<IF:$<BOOL:${MQTT_USE_STATIC_BOOST}>,,BOOST_TEST_DYN_LINK>)

    IF (MQTT_USE_LOG)
        TARGET_COMPILE_DEFINITIONS (test_precomp_target PUBLIC $<IF:$<BOOL:${MQTT_USE_STATIC_BOOST}>,,BOOST_LOG_DYN_LINK>)
    ENDIF ()
ENDIF ()

ADD_SUBDIRECTORY (system)
ADD_SUBDIRECTORY (unit)
