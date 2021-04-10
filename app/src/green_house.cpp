/**@file green_house.c
 *
 * @desrc Main module API's impelemantation
 *
 * @authors
 *      Serhii Bura <serhiibura@gmail.com>
 */

#include "logger_api.h"

#include "green_house_api.h"
#include "green_house_version.hpp"

#include "uart_console.h"

extern "C" {

static bool st_init = false;

static const char* st_green_house_msg =
        "\n\r============Green Hosue============"
        "\n\r=                                 ="
        "\n\r=                                 ="
        "\n\r=       Version %04d.%04d.%04d    ="
        "\n\r===================================";

result_t initModule(board_st_t *board) {
    result_t result = eResultSucces;

    if (nullptr == board) {
        return eResultInvalidParam;
    }

    result = loggerInit(&board->logger_ops);
    if (eResultSucces != result) {
        return result;
    }

    st_init = true;

    return result;
}


result_t startHeatBeatTask() {
    result_t result = eResultSucces;
    ///< TODO: Add heartbeat implementation

    return result;
}

result_t startLoggerTask() {
    result_t result = eResultSucces;

    if (false == st_init) {
        return eResultNotInitialized;
    }

    loggerStart(st_green_house_msg, VERSION_MAJOR, VERSION_MINOR,
                VERSION_BUILD);

    return result;
}

result_t startModuleTask() {
    result_t result = eResultSucces;
    ///< TODO: Add module task implementation
    logInfoMsg("Hello Green House developer!");

    return result;
}

}
