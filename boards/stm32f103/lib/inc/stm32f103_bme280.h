/**@file stm32f103_bme280.h
 *
 * @desrc Decalration stm32f103 SPI API for bme280 sensor
 *
 * @authors
 *      Serhii Bura <serhiibura@gmail.com>
 */

#ifndef __STM32F103_BME280_H__
#define __STM32F103_BME280_H__

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "bme280/green-house-bme280-data.h"

void stm32f103_bme280_init(bme280_sensor_id_t sensor);
void stm32f103_bme280_delay_ms(uint32_t period, void *intf_ptr);
int8_t stm32f103_bme280_spi_read(uint8_t reg_addr, uint8_t *reg_data,
    uint32_t len, void *intf_ptr);
int8_t stm32f103_bme280_spi_write(uint8_t reg_addr, uint8_t *reg_data,
    uint32_t len, void *intf_ptr);

#ifdef __cplusplus
}
#endif

#endif  //__STM32F103_BME280_H__
