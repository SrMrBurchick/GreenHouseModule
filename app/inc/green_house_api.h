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

#ifdef __cplusplus
extern "C" {
#endif

result_t initModule(board_st_t *);

result_t startLoggerTask();
result_t startHeatBeatTask();
result_t startModuleTask();

#ifdef __cplusplus
}
#endif

#endif  //__GREEN_HOUSE_API__
