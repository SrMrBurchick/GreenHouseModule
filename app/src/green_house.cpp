/**@file green_house.c
 *
 * @desrc Main module API's impelemantation
 *
 * @authors
 *      Serhii Bura <serhiibura@gmail.com>
 */

#include "green_house_api.h"

extern "C" {

result_t startHeatBeatTask() {
    result_t result = eResultSucces;
    ///< TODO: Add heartbeat implementation

    return result;
}

result_t startLoggerTask() {
    result_t result = eResultSucces;
    ///< TODO: Add logger implementation

    return result;
}

result_t startModuleTask() {
    result_t result = eResultSucces;
    ///< TODO: Add module task implementation
 
    return result;
}

}
