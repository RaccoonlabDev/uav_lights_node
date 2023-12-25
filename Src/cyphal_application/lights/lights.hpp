/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#ifndef SRC_CYPHAL_APPLICATION_LIGHTS_LIGHTS_HPP_
#define SRC_CYPHAL_APPLICATION_LIGHTS_LIGHTS_HPP_

#include "cyphal_subscribers.hpp"
#include "Udral/rgbled.hpp"
#include "Udral/circuit_status.hpp"

class RgbLights {
public:
    RgbLights(cyphal::Cyphal* driver) : _rgbled_sub(driver), _temp_pub(driver, 0) {};
    int8_t init();
    void update();
private:

    cyphal::HighColorSubscriber _rgbled_sub;
    RaccoonLab::CircuitStatusTemperaturePublisher _temp_pub;
};

#endif  // SRC_CYPHAL_APPLICATION_LIGHTS_LIGHTS_HPP_
