#include "usart.h"
#include "uart_console.h"

#define UART_TIMEOUT (1000)

result_t uart_write_char(char ch) {
    if (HAL_OK != HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, UART_TIMEOUT)) {
        return eResultFailed;
    }

    return eResultSucces;
}

result_t uart_write_line(const char *buff, uint16_t len) {
    if (HAL_OK != HAL_UART_Transmit(&huart1, (uint8_t *)buff, len, UART_TIMEOUT)) {
        return eResultFailed;
    }

    return eResultSucces;
}

result_t uart_read_char(char *ch) {
    if (HAL_OK != HAL_UART_Receive(&huart1, (uint8_t *)ch, 1, UART_TIMEOUT)) {
        return eResultFailed;
    }

    return eResultSucces;
}

