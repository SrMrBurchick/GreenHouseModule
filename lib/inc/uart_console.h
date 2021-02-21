#ifndef _UART_CONSOLE_H_
#define _UART_CONSOLE_H_

#include <stdint.h>
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

result_t uart_write_char(char ch);
result_t uart_write_line(const char *buff, uint16_t len);
result_t uart_read_char(char *ch);

#ifdef __cplusplus
}
#endif

#endif /*_UART_CONSOLE_H_*/
