/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2022-2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#include "led.hpp"
#include "main.h"


void LedPeriphery::reset() {
    HAL_GPIO_WritePin(INTERNAL_LED_GPIO_Port, INTERNAL_LED_Pin, GPIO_PIN_SET);
}

void LedPeriphery::toggle() {
    auto crnt_time_ms = HAL_GetTick();
    GPIO_PinState state = (crnt_time_ms % 1000 > 500) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(INTERNAL_LED_GPIO_Port, INTERNAL_LED_Pin, state);
}
