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
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Duty_Cycle_Motor_PWM C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Duty_Cycle_Motor_PWM Duty_Cycle_Motor_PWM.c )

pico_set_program_name(Duty_Cycle_Motor_PWM "Duty_Cycle_Motor_PWM")
pico_set_program_version(Duty_Cycle_Motor_PWM "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Duty_Cycle_Motor_PWM 0)
pico_enable_stdio_usb(Duty_Cycle_Motor_PWM 1)

# Add the standard library to the build
target_link_libraries(Duty_Cycle_Motor_PWM
        pico_stdlib
        hardware_pwm
        hardware_adc)

# Add the standard include files to the build
target_include_directories(Duty_Cycle_Motor_PWM PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(Duty_Cycle_Motor_PWM 

        
        )

pico_add_extra_outputs(Duty_Cycle_Motor_PWM)

