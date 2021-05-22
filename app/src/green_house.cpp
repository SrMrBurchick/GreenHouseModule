/**@file green_house.c
 *
 * @desrc Main module API's impelemantation
 *
 * @authors
 *      Serhii Bura <serhiibura@gmail.com>
 */

#include "logger_api.h"

#include "green_house_api.h"
#include "green_house_version.hpp"

#include "bme280.h"

extern "C" {

result_t stream_sensor_data_forced_mode(struct bme280_dev *dev, uint8_t id);

static bool st_init = false;

static
green_house_config_st_t *st_moduleCfg_p = NULL;

static const char* st_green_house_msg =
        "\n\r============Green Hosue============"
        "\n\r=                                 ="
        "\n\r=                                 ="
        "\n\r=       Version %04d.%04d.%04d    ="
        "\n\r===================================";

result_t initModule(green_house_config_st_t *config) {
    result_t result = eResultSucces;

    if (nullptr == config) {
        return eResultInvalidParam;
    }

    result = loggerInit(&config->base_config.logger_ops);
    if (eResultSucces != result) {
        return result;
    }

    loggerSetLogLevel(eLogLevelInfo);

    st_moduleCfg_p = config;
    st_init = true;

    return result;
}


result_t startHeatBeatTask() {
    result_t result = eResultSucces;
    ///< TODO: Add heartbeat implementation

    return result;
}

result_t startLoggerTask() {
    result_t result = eResultSucces;

    if (false == st_init) {
        return eResultNotInitialized;
    }

    loggerStart(st_green_house_msg, VERSION_MAJOR, VERSION_MINOR,
                VERSION_BUILD);

    return result;
}

result_t startModuleTask() {
    result_t result = eResultSucces;
    int bme280_result = BME280_OK;

    if (false == st_init) {
        return eResultNotInitialized;
    }

    logInfoMsg("Hello Green House developer!");

    for (uint8_t i = 0; i < GREEN_HOUSE_BME280_COUNT; i++) {
       logInfoMsg("Init %d bme sensor", i);
       bme280_result = bme280_init(st_moduleCfg_p->bme280_devices + i);
       if(BME280_OK != bme280_result) {
            logErrorMsg("Failed to init bme280 %u sensor. Error code: %u", i,
                        bme280_result);

            return eResultFailed;
       }
    }

    while(1) {
        for (uint8_t i = 0; i < GREEN_HOUSE_BME280_COUNT; i++) {
            result = stream_sensor_data_forced_mode(
                st_moduleCfg_p->bme280_devices + i, i);
            if (eResultSucces != result) {
                logErrorMsg("Failed to read %u sensor data. Error code: %u", i,
                            result);
            }

            st_moduleCfg_p->bme280_devices[i].delay_us(1000, NULL);
        }

    };

    return result;
}

/*!
 * @brief This API used to print the sensor temperature, pressure and humidity data.
 */
void print_sensor_data(struct bme280_data *comp_data, uint8_t id)
{
    int32_t temp, press, hum;

    temp = (int64_t)(comp_data->temperature * 1000);
    press = (int64_t)(comp_data->pressure * 1000);
    hum = (int64_t)(comp_data->humidity * 1000);
    logInfoMsg("SENSOR[%d] :%d deg C, %d hPa, %d", id, temp, press, hum);
}

}
