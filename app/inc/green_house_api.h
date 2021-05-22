/**@file green_house_api.h
 *
 * @desrc Decalration main module API's
 *
 * @authors
 *      Serhii Bura <serhiibura@gmail.com>
 */

#ifndef __GREEN_HOUSE_API__
#define __GREEN_HOUSE_API__

#include "board_config.h"

#include "bme280.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GREEN_HOUSE_BME280_COUNT 3

typedef struct green_house_config{
    board_st_t        base_config;
    struct bme280_dev bme280_devices[GREEN_HOUSE_BME280_COUNT];
} green_house_config_st_t;

result_t initModule(green_house_config_st_t *);

result_t startLoggerTask();
result_t startHeatBeatTask();
result_t startModuleTask();

#ifdef __cplusplus
}
#endif

#endif  //__GREEN_HOUSE_API__
