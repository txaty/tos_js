#pragma once
#include <stdio.h>
#include "tos_k.h"

extern k_mutex_t mutex_js_engine;

#define TASK_SIZE_JS_EXEC 1536u
extern uint8_t stk_js_exec[TASK_SIZE_JS_EXEC];
extern k_task_t k_js_exec;
void task_js_exec(void *pdata);

#define TASK_SIZE_TOGGLE_LED 256u
extern uint8_t stk_toggle_led[TASK_SIZE_TOGGLE_LED];
extern k_task_t k_toggle_led;
void task_toggle_led(void *pdata);
