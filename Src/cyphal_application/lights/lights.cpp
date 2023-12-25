/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#include "lights.hpp"
#include <algorithm>
#include "cyphal.hpp"
#include "params.hpp"
#include "main.h"
#include "periphery/ws2812/ws2812.h"
#include "periphery/adc/adc.hpp"

extern TIM_HandleTypeDef htim2;

static constexpr uint8_t RED_SCALE = 256 / (reg_udral_physics_optics_HighColor_0_1_MAX_RED + 1);
static constexpr uint8_t GREEN_SCALE = 256 / (reg_udral_physics_optics_HighColor_0_1_MAX_GREEN + 1);
static constexpr uint8_t BLUE_SCALE = 256 / (reg_udral_physics_optics_HighColor_0_1_MAX_BLUE + 1);


int8_t RgbLights::init() {
    int8_t res;

    res = ws2812bInit(32, &htim2, TIM_CHANNEL_3);
    if (res < 0) {
        return res;
    }

    res = _rgbled_sub.init();
    if (res < 0) {
        return res;
    }

    res = AdcPeriphery::init();
    if (res < 0) {
        return res;
    }

    return 0;
};

void RgbLights::update() {
    static uint32_t next_time_ms = 0;
    if (HAL_GetTick() < next_time_ms) {
        return;
    }
    next_time_ms = HAL_GetTick() + 10;

    // Temperature
    static const uint16_t TEMP_REF = 25;
    static const uint16_t ADC_REF = 1750;   ///< v_ref / 3.3 * 4095
    static const uint16_t AVG_SLOPE = 5;    ///< avg_slope/(3.3/4096)
    _temp_pub.setPortId(paramsGetIntegerValue(PARAM_CRCT_TEMPERATURE_ID));
    if (_temp_pub.isEnabled()) {
        uint16_t adc_measurement = AdcPeriphery::get(AdcChannel::ADC_TEMPERATURE);
        uavcan_si_sample_temperature_Scalar_1_0 msg;
        msg.kelvin = (ADC_REF - adc_measurement) / AVG_SLOPE + TEMP_REF + 273;
        _temp_pub.publish(msg);
    }

    // Lights
    auto color = _rgbled_sub.get();
    static Leds_Color_t leds;

    for (uint_fast8_t led_idx = 0; led_idx < 32; led_idx++) {
        leds.colors[led_idx].shades.red = color.red * RED_SCALE;
        leds.colors[led_idx].shades.green = color.green * GREEN_SCALE;
        leds.colors[led_idx].shades.blue = color.blue * BLUE_SCALE;
    }
    ws2812bSetColors(&leds);
    ws2812bStartOnce();
}
