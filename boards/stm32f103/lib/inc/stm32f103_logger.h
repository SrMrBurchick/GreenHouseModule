#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdarg.h>

#include "uart_console.h"

result_t logger_init();
void logger_send_msg(const char* fmt, uint16_t length);
void logger_start(const char* fmt, va_list args);

#endif /*_LOGGER_H_*/
