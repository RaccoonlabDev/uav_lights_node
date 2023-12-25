set(applicationSourceCode
    Src/periphery/adc/adc.cpp
    Src/periphery/led/led.cpp
    Src/periphery/ws2812/ws2812.c

    Src/cyphal_application/lights/lights.cpp
    Src/cyphal_application/application.cpp

    Libs/Cyphal/Udral/rgbled.cpp
    Libs/Cyphal/Udral/circuit_status.cpp
)
set(applicationHeaders
    Src
    Src/cyphal_application
    Libs/Cyphal
)

list(APPEND cyphalRegisters
    ${CMAKE_CURRENT_LIST_DIR}/params.yaml
    ${CMAKE_CURRENT_LIST_DIR}/lights/params.yaml
)
