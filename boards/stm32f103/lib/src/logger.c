#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "logger.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

#define QUEUE_LENGTH (128)
#define ITEM_SIZE (sizeof(uint8_t*))
#define MSG_SIZE (285)
#define LOGGER_QUEUE_TIMEOUT (1000)
#define NEXT_LINE "\n\r"

static StaticQueue_t xStaticQueue;
static xQueueHandle st_loggerQueue_p;
static uint8_t st_loggerQueueBuffer[QUEUE_LENGTH * ITEM_SIZE];
static xSemaphoreHandle st_semaphore_p = NULL;
static StaticSemaphore_t st_semaphoreBuffer;
static const uint32_t st_loggerTaskTimeoutMs = 100;

result_t logger_init() {

    st_semaphore_p = xSemaphoreCreateBinaryStatic(&st_semaphoreBuffer);

    if (NULL == st_semaphore_p) {
        return eResultFailed;
    }

    st_loggerQueue_p = xQueueCreateStatic(QUEUE_LENGTH, ITEM_SIZE, st_loggerQueueBuffer, &xStaticQueue);

    if (NULL == st_loggerQueue_p) {
        return eResultFailed;
    }
    return eResultSucces;
}

void logger_send_msg(const char* fmt, uint16_t length) {
    uint8_t* msg_p = pvPortMalloc(length);

    if(NULL == msg_p) {
        return;
    }
    
    memcpy(msg_p, fmt, length);

    if (pdPASS != xQueueSend(st_loggerQueue_p, (void*)&msg_p, LOGGER_QUEUE_TIMEOUT)) {
        vPortFree(msg_p);
        return;
    }
}

void logger_start() {
    uint8_t* msg_p = NULL;
    while (1) {
        if (NULL != msg_p) {
            vPortFree(msg_p);
            msg_p = NULL;
        }
        if (pdPASS == xQueueReceive(st_loggerQueue_p, &msg_p, LOGGER_QUEUE_TIMEOUT)) {
            uart_write_line((char *)msg_p, strlen((char *)msg_p));
            uart_write_line(NEXT_LINE, strlen(NEXT_LINE));
        }
        vTaskDelay(st_loggerTaskTimeoutMs);
    }
}
