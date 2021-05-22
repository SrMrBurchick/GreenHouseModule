/**@file leds_api.h
*
* @desrc Leds controll API
*
* @authors
*      Serhii Bura <serhiibura@gmail.com>
*/

#ifndef __LEDS_API_H__
#define __LEDS_API_H__

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
        LED_HEARTBEAT = 0
} led_type_t;

result_t startModuleTask();

#ifdef __cplusplus
}
#endif

#endif  //__LEDS_API_H__
