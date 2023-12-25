/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2022-2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#include "application.hpp"
#include "cyphal.hpp"
#include "cyphal_registers.hpp"
#include "main.h"
#include "string_params.hpp"
#include "params.hpp"
#include "lights/lights.hpp"
#include "periphery/led/led.hpp"


void init_persistent_storage() {
    paramsInit(static_cast<uint8_t>(IntParamsIndexes::INTEGER_PARAMS_AMOUNT), NUM_OF_STR_PARAMS);
    paramsLoadFromFlash();

    auto node_name_param_idx = static_cast<ParamIndex_t>(IntParamsIndexes::INTEGER_PARAMS_AMOUNT);
    paramsSetStringValue(node_name_param_idx, 21, (const uint8_t*)"co.raccoonlab.lights");
}

void application_entry_point() {
    LedPeriphery::reset();
    init_persistent_storage();
    cyphal::NodeGetInfoSubscriber::setHardwareVersion(2, 1);

    cyphal::Cyphal cyphal;
    int init_res = cyphal.init();

    RgbLights lights(&cyphal);
    init_res |= lights.init();

    while (true) {
        LedPeriphery::toggle();

        cyphal.process();
        lights.update();
    }
}
