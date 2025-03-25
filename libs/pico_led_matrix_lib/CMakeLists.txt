cmake_minimum_required(VERSION 3.13)

project(pico_led_matrix_lib)

add_library(pico_led_matrix_lib pico_led_matrix_lib.c)

target_include_directories(pico_led_matrix_lib PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(pico_led_matrix_lib
    pico_stdlib
    hardware_timer
    hardware_pio
    hardware_clocks
    hardware_pwm
)