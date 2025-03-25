cmake_minimum_required(VERSION 3.13)

project(pico_button_lib)

add_library(pico_button_lib pico_button_lib.c)

target_include_directories(pico_button_lib PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(pico_button_lib
    pico_stdlib
    hardware_adc
    hardware_timer
)