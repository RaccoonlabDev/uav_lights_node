/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#include "lights.hpp"
#include <algorithm>
#include "cyphal.hpp"
#include "params.hpp"
#include "main.h"
#include "periphery/adc/adc.hpp"

#define WS2812_LEDS_AMOUNT 32
extern TIM_HandleTypeDef htim2;


int8_t RgbLights::init() {
    int8_t res;

    res = ws2812bInit(WS2812_LEDS_AMOUNT, &htim2, TIM_CHANNEL_3);
    if (res < 0) {
        return res;
    }

    res = _rgbled_sub.init();
    if (res < 0) {
        return res;
    }

    return 0;
};

void RgbLights::update() {
    _process_crct_remperature();

    if (HAL_GetTick() >= _next_light_process_time_ms) {
        _next_light_process_time_ms = HAL_GetTick() + 40;

        if (_init_counter < WS2812_LEDS_AMOUNT) {
            _init_lights();
        } else {
            _process_last_received_command();
        }

        ws2812bSetColors(&_leds);
        ws2812bStartOnce();
    }
}

/**
 * @note
 * The temperture formula is valid only for stm32f103
 * We can measure ADC much faster and a filter can be added here
 */
void RgbLights::_process_crct_remperature() {
    if (HAL_GetTick() < _next_crct_process_time_ms) {
        return;
    }
    _next_crct_process_time_ms = HAL_GetTick() + 250;

    static const uint16_t TEMP_REF = 25;
    static const uint16_t ADC_REF = 1750;   ///< v_ref / 3.3 * 4095
    static const uint16_t AVG_SLOPE = 5;    ///< avg_slope/(3.3/4096)
    _temp_pub.setPortId(paramsGetIntegerValue(PARAM_CRCT_TEMPERATURE_ID));
    if (_temp_pub.isEnabled()) {
        uint16_t adc_measurement = AdcPeriphery::get(AdcChannel::ADC_TEMPERATURE);
        current_temperature = (ADC_REF - adc_measurement) / AVG_SLOPE + TEMP_REF + 273;
        uavcan_si_sample_temperature_Scalar_1_0 msg;
        msg.kelvin = current_temperature;
        _temp_pub.publish(msg);
    }
}

void RgbLights::_init_lights() {
    if (_init_counter < WS2812_LEDS_AMOUNT) {
        _leds.colors[_init_counter].shades.red = 5;
        _leds.colors[_init_counter].shades.green = 5;
        _leds.colors[_init_counter].shades.blue = 5;
    }

    _init_counter++;
}

void RgbLights::_process_last_received_command() {
    float max_brightness;
    if (current_temperature <= CONTROL_MIN) {
        max_brightness = 1.0;
    } else if (current_temperature >= CONTROL_MAX) {
        max_brightness = 0.0;
    } else {
        max_brightness = 1.0f - (current_temperature - CONTROL_MIN) / (CONTROL_MAX - CONTROL_MIN);
    }

    reg_udral_physics_optics_HighColor_0_1 color;
    if (_rgbled_sub.get_last_recv_ts_ms() == 0) {
        color.red = 1;
        color.green = 2;
        color.blue = 1;
    } else {
        color = _rgbled_sub.get();
    }

    uint8_t red = (float)color.red / reg_udral_physics_optics_HighColor_0_1_MAX_RED * 255.0f * max_brightness;
    uint8_t green = (float)color.green / reg_udral_physics_optics_HighColor_0_1_MAX_GREEN * 255.0f * max_brightness;
    uint8_t blue = (float)color.blue / reg_udral_physics_optics_HighColor_0_1_MAX_BLUE * 255.0f * max_brightness;
    for (uint_fast8_t led_idx = 0; led_idx < WS2812_LEDS_AMOUNT; led_idx++) {
        _leds.colors[led_idx].shades.red = red;
        _leds.colors[led_idx].shades.green = green;
        _leds.colors[led_idx].shades.blue = blue;
    }
}
