#pragma once
#include <stdio.h>
#include "tos_k.h"

// mutex
extern k_mutex_t mutex_js_engine;

// #define TASK_SIZE_JS_EXEC 1536u
// extern uint8_t stk_js_exec[TASK_SIZE_JS_EXEC];
// extern k_task_t k_js_exec;
// void task_js_exec(void *pdata);

// task 
// toggle LED
#define TASK_SIZE_TOGGLE_LED 256u
extern uint8_t stk_toggle_led[TASK_SIZE_TOGGLE_LED];
extern k_task_t k_toggle_led;
void task_toggle_led(void *pdata);

// Wifi connection
#define TASK_SIZE_WIFI_CONNECT 4096
extern k_task_t *k_wifi_connect;
extern char *wifi_ssid;
extern char *wifi_pwd;
void task_wifi_connect(void *pdata);

// JS server
#define TASK_SIZE_JS_SERVER 4096
extern k_task_t *k_js_server;
extern char *server_ip;
extern char *server_port;
extern int tcp_socket_id;
void task_js_server(void *pdata);