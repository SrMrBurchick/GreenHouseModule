/**@file stm32f103_bme280.c
 *
 * @desrc Decalration stm32f103 SPI API for bme280 sensor
 *
 * @authors
 *      Serhii Bura <serhiibura@gmail.com>
 */

#include <string.h>

#include "main.h"
#include "spi.h"
#include "cmsis_os.h"

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

#include "logger_api.h"

#include "stm32f103_bme280.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SPI_TIMEOUT_500_MS 500

#define SPI_CHIP_SELECT_LOCK   1
#define SPI_CHIP_SELECT_UNLOCK 0

static
HAL_StatusTypeDef st_setChipSelect(bme280_sensor_id_t sensor, uint8_t state)
{
    HAL_StatusTypeDef status = HAL_OK;
    int *gpio_port = NULL;
    int gpio_pin = -1;
    uint8_t pin_state = GPIO_PIN_SET;

    switch (sensor) {
    case BME280_SENSOR_0:
        gpio_port = SPI_BOSCH_CS_0_GPIO_Port;
        gpio_pin = SPI_BOSCH_CS_0_Pin;
        break;
    case BME280_SENSOR_1:
        gpio_port = SPI_BOSCH_CS_1_GPIO_Port;
        gpio_pin = SPI_BOSCH_CS_1_Pin;
        break;
    case BME280_SENSOR_2:
        gpio_port = SPI_BOSCH_CS_2_GPIO_Port;
        gpio_pin = SPI_BOSCH_CS_2_Pin;
        break;

    default:
        logErrorMsg("Invalid bme 280 sensor %d", sensor);

        return HAL_ERROR;
    }

    pin_state = SPI_CHIP_SELECT_LOCK == state ? GPIO_PIN_RESET : GPIO_PIN_SET;

    HAL_GPIO_WritePin(gpio_port, gpio_pin, pin_state);

    return status;
}

void stm32f103_bme280_init(bme280_sensor_id_t sensor)
{
    st_setChipSelect(sensor, SPI_CHIP_SELECT_UNLOCK);
}

void stm32f103_bme280_delay_ms(uint32_t period, void *intf_ptr) {
    osDelay(period);
}

int8_t stm32f103_bme280_spi_read(uint8_t reg_addr, uint8_t *reg_data,
    uint32_t len, void *intf_ptr)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    HAL_StatusTypeDef status = HAL_OK;
    uint8_t* data = NULL;
    uint8_t* write_buffer = NULL;
    struct identifier id;

    id = *((struct identifier *)intf_ptr);

    data = (uint8_t *)pvPortMalloc(len + 1);
    if (NULL == data) {
        logErrorMsg("Failed to allocate meory!");

        return -1;
    }

    write_buffer = (uint8_t *)pvPortMalloc(len + 1);
    if (NULL == write_buffer) {
        logErrorMsg("Failed to allocate meory!");
        rslt = -1;

        goto exit;
    }

    status = st_setChipSelect((bme280_sensor_id_t)id.dev_addr,
                              SPI_CHIP_SELECT_LOCK);
    if (HAL_OK != status) {
        logErrorMsg("Failed to lock chip select for device %d. Error code: %d",
                    id.dev_addr, status);
        rslt = -1;

        goto exit;
    }

    write_buffer[0] = reg_addr;

    status = HAL_SPI_TransmitReceive(&hspi2, write_buffer, data, len + 1,
                                     SPI_TIMEOUT_500_MS);
    if (HAL_OK != status) {
        logErrorMsg("Failed to read spi. Error code: %d", status);
        rslt = -1;

        goto exit;
    }

    memcpy(reg_data, data + 1, len);

exit:

    status = st_setChipSelect((bme280_sensor_id_t)id.dev_addr,
                              SPI_CHIP_SELECT_UNLOCK);
    if (HAL_OK != status) {
        logErrorMsg("Failed to lock chip select for device %d. Error code: %d",
                    id.dev_addr, status);
    }

    vPortFree(data);
    vPortFree(write_buffer);

    logDebugMsg("Register[%x] readed value", reg_addr);

    for (uint8_t i = 0; i < len; i++) {
        logDebugMsg("reg_data[%d]: %x", i, reg_data[i]);
    }

    return rslt;
}

int8_t stm32f103_bme280_spi_write(uint8_t reg_addr, uint8_t *reg_data,
    uint32_t len, void *intf_ptr)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    HAL_StatusTypeDef status = HAL_OK;
    uint8_t* data = NULL;
    struct identifier id;

    id = *((struct identifier *)intf_ptr);

    data = (uint8_t *)pvPortMalloc(len + 1);
    if (NULL == data) {
        logErrorMsg("Failed to allocate meory!");

        return -1;
    }

    status = st_setChipSelect((bme280_sensor_id_t)id.dev_addr,
                              SPI_CHIP_SELECT_LOCK);
    if (HAL_OK != status) {
        logErrorMsg("Failed to lock chip select for device %d. Error code: %d",
                    id.dev_addr, status);

        return -1;
    }

    data[0] = reg_addr;
    memcpy(data + 1, reg_data, len);

    status = HAL_SPI_Transmit(&hspi2, data, len + 1, SPI_TIMEOUT_500_MS);
    if (HAL_OK != status) {
        logErrorMsg("Failed to write spi. Error code: %d", status);
        rslt = -1;

        goto exit;
    }

exit:

    status = st_setChipSelect((bme280_sensor_id_t)id.dev_addr,
                              SPI_CHIP_SELECT_UNLOCK);
    if (HAL_OK != status) {
        logErrorMsg("Failed to lock chip select for device %d. Error code: %d",
                    id.dev_addr, status);
    }

    vPortFree(data);

    return rslt;
}

#ifdef __cplusplus
}
#endif
