cmake_minimum_required(VERSION 3.13)

project(joystick_lib)

add_library(joystick_lib joystick_lib.c direcoes.c)

target_include_directories(joystick_lib PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(joystick_lib
    pico_stdlib
    hardware_timer
    hardware_pio
    hardware_clocks
    hardware_pwm
    hardware_adc
)