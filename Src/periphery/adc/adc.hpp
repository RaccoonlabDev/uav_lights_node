/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2022-2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#ifndef SRC_APPLICATION_PERIPHERY_ADC_ADC_HPP_
#define SRC_APPLICATION_PERIPHERY_ADC_ADC_HPP_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum class AdcChannel : uint8_t {
    ADC_VIN,
    ADC_5V,
    ADC_TEMPERATURE,
    ADC_NUMBER_OF_CNANNELS,
};

class AdcPeriphery {
public:
    static int8_t init();
    static uint16_t get(AdcChannel channel);
private:
    static inline bool _is_adc_already_inited = false;
};

#ifdef __cplusplus
}
#endif

#endif  // SRC_APPLICATION_PERIPHERY_ADC_ADC_HPP_
