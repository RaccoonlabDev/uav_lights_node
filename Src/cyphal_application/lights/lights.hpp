/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#ifndef SRC_CYPHAL_APPLICATION_LIGHTS_LIGHTS_HPP_
#define SRC_CYPHAL_APPLICATION_LIGHTS_LIGHTS_HPP_

#include "cyphal_subscribers.hpp"
#include "Udral/rgbled.hpp"
#include "Udral/circuit_status.hpp"
#include "periphery/ws2812/ws2812.h"


class RgbLights {
public:
    RgbLights(cyphal::Cyphal* driver) :  _temp_pub(driver, 0), _rgbled_sub(driver) {};
    int8_t init();

    /**
    * @note 25 Hz blinking is considered to be enough.
    */
    void update();
private:
    /**
     * @brief When the node is enabled, the LEDs blink one after one with white color.
     * This initialization sequence allows a user to verify that all LEDs are working properly.
     */
    void _init_lights();
    uint8_t _init_counter{0};

    /**
     * @brief Measure onboard temperature and publish to Cyphal/CAN network
     * The temperature is used in the brightness controller
     */
    void _process_crct_remperature();
    RaccoonLab::CircuitStatusTemperaturePublisher _temp_pub;
    float current_temperature;
    uint32_t _next_crct_process_time_ms{0};

    /**
     * @brief Brightness Controller
     * If the temperature goes above 60 °C, the controller will decrease the maximum brightness.
     * If the temperature goes above 80 °C, the controller will turn off the lights.
     */
    static constexpr const float CONTROL_MIN = 273.15 + 60;
    static constexpr const float CONTROL_MAX = 273.15 + 80;

    /**
     * @brief Just repeat the latest received command with respect to the brightness.
     * By default, all LEDs should be slightly enabled with white color
     * to be sure they are working properly.
     */
    void _process_last_received_command();
    cyphal::HighColorSubscriber _rgbled_sub;
    Leds_Color_t _leds{};
    uint32_t _next_light_process_time_ms{0};
};

#endif  // SRC_CYPHAL_APPLICATION_LIGHTS_LIGHTS_HPP_
