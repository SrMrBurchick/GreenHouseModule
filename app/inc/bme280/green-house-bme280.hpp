/**@file gree-house-hpp-bme280.hpp
 *
 * @desrc Decalration bme280 API's
 *
 * @authors
 *      Serhii Bura <serhiibura@gmail.com>
 */

#ifndef __GREEN_HOUSE_BME280_API_HPP__
#define __GREEN_HOUSE_BME280_API_HPP__

#include "isensor.hpp"

#include "board_config.h"

#include "green-house-bme280-data.h"

#define GREEN_HOUSE_BME280_COUNT 3

typedef struct bme280_dev bme280_dev_st_t;

class IBme280 : public ISensor {
    public:
        virtual ~IBme280() = default;
        result_t startMeasurements();
    protected:
        explicit IBme280(sensor_type_t type, bme280_dev_st_t *dev)
            :ISensor(type) {
                if(nullptr == dev) {
                    logErrorMsg("Invalid input: %p", dev);

                    return;
                }
                m_id = (bme280_sensor_id_t)
                    ((struct identifier*)(dev->intf_ptr))->dev_addr;
                m_bmeDevice = dev;
            };
    private:
        result_t initDevice();
        uint32_t getTemperature();
        uint32_t getHumidity();
        uint32_t getPressure();


        bme280_dev_st_t   *m_bmeDevice;
        bme280_sensor_id_t m_id;
};

class Bme280Temperature : public IBme280 {
    public:
        virtual ~Bme280Temperature() = default;
        explicit Bme280Temperature(bme280_dev_st_t *dev);
        virtual int getValue() final;
};

class Bme280Humidity : public IBme280 {
    public:
        virtual ~Bme280Humidity() = default;
        explicit Bme280Humidity(bme280_dev_st_t *dev);
        virtual int getValue() final;
};

class Bme280Pressure : public IBme280 {
    public:
        virtual ~Bme280Pressure() = default;
        explicit Bme280Pressure(bme280_dev_st_t *dev);
        virtual int getValue() final;
};

#endif  // __GREEN_HOUSE_BME280_API_HPP__
