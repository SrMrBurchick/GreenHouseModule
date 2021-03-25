/**@file green_house_api.h
 *
 * @desrc Decalration main module API's
 *
 * @authors
 *      Serhii Bura <serhiibura@gmail.com>
 */

#ifndef __GREEN_HOUSE_API__
#define __GREEN_HOUSE_API__

#include "common.h"

result_t startLoggerTask();
result_t startHeatBeatTask();
result_t startModuleTask();

#endif  //__GREEN_HOUSE_API__