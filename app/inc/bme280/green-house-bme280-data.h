/**@file bme280.h
 *
 * @desrc Decalration bme280 constants
 *
 * @authors
 *      Serhii Bura <serhiibura@gmail.com>
 */

#ifndef __BME280_DATA_H__
#define __BME280_DATA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "bme280.h"

#define GREEN_HOUSE_BME280_COUNT 3

typedef enum {
    BME280_SENSOR_0 = 0,
    BME280_SENSOR_1,
    BME280_SENSOR_2,
} bme280_sensor_id_t;

#ifdef __cplusplus
}
#endif

#endif  //__BME280_DATA_H__
