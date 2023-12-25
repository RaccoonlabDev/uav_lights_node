/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2022-2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#ifndef SRC_APPLICATION_PERIPHERY_LED_LED_HPP_
#define SRC_APPLICATION_PERIPHERY_LED_LED_HPP_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

class LedPeriphery {
public:
    static void reset();
    static void toggle();
};

#ifdef __cplusplus
}
#endif

#endif  // SRC_APPLICATION_PERIPHERY_LED_LED_HPP_
