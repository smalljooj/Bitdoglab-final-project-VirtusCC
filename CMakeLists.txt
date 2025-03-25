# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(bitdoglab_final_project_virtuscc C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(bitdoglab_final_project_virtuscc bitdoglab_final_project_virtuscc.c )

pico_set_program_name(bitdoglab_final_project_virtuscc "bitdoglab_final_project_virtuscc")
pico_set_program_version(bitdoglab_final_project_virtuscc "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(bitdoglab_final_project_virtuscc 1)
pico_enable_stdio_usb(bitdoglab_final_project_virtuscc 1)

# Add the standard library to the build
target_link_libraries(bitdoglab_final_project_virtuscc
        pico_stdlib
        pico_button_lib
        pico_buzzer_lib
        pico_led_matrix_lib
        joystick_lib
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libs/pico_button_lib)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libs/pico_buzzer_lib)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libs/pico_led_matrix_lib)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libs/joystick_lib)

# Add the standard include files to the build
target_include_directories(bitdoglab_final_project_virtuscc PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/libs/pico_button_lib/inc/
        ${CMAKE_CURRENT_LIST_DIR}/libs/pico_buzzer_lib/inc/
        ${CMAKE_CURRENT_LIST_DIR}/libs/pico_led_matrix_lib/inc/
        ${CMAKE_CURRENT_LIST_DIR}/libs/joystick_lib/inc/
)

# Add any user requested libraries
target_link_libraries(bitdoglab_final_project_virtuscc)

pico_add_extra_outputs(bitdoglab_final_project_virtuscc)

