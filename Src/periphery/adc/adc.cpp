/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2022-2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#include "adc.hpp"
#include "main.h"

extern ADC_HandleTypeDef hadc1;

int8_t AdcPeriphery::init() {
    HAL_ADCEx_Calibration_Start(&hadc1);
    _is_adc_already_inited = true;
    return 0;
}

uint16_t AdcPeriphery::get(AdcChannel channel) {
    if (!_is_adc_already_inited || channel >= AdcChannel::ADC_NUMBER_OF_CNANNELS) {
        return 0;
    }

    HAL_ADC_Start(&hadc1);
    uint8_t channels_amount = static_cast<uint8_t>(AdcChannel::ADC_NUMBER_OF_CNANNELS);
    uint16_t _adc_raw[static_cast<uint8_t>(AdcChannel::ADC_NUMBER_OF_CNANNELS)];
    for (size_t ch_idx = 0; ch_idx < channels_amount; ch_idx++) {
        _adc_raw[ch_idx] = (uint16_t)HAL_ADC_GetValue(&hadc1);
    }
    return _adc_raw[static_cast<uint8_t>(channel)];
}
