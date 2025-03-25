cmake_minimum_required(VERSION 3.13)

project(pico_buzzer_lib)

add_library(pico_buzzer_lib pico_buzzer_lib.c)

target_include_directories(pico_buzzer_lib PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(pico_buzzer_lib
    pico_stdlib
    hardware_timer
    hardware_pwm
)