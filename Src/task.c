#include "task.h"
#include "js.h"
#include "util.h"
#include "gpio.h"
#include "js_apps.h"
#include "tos_at.h"
#include "esp8266.h"
#include "sal_module_wrapper.h"

// mutex
k_mutex_t mutex_js_engine;

// task
// k_task_t k_js_exec;
// uint8_t stk_js_exec[TASK_SIZE_JS_EXEC];
// void task_js_exec(void *pdata)
// {
//     printf("js_exec\n");
//     HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//     k_err_t err = tos_mutex_pend(&mutex_js_engine);
//     if (err == K_ERR_NONE)
//     {
//         JS *js = js_create_static();
//         js_driver_init(js);
//         js_eval(js, js_app_led_control, ~0);
//         tos_mutex_post(&mutex_js_engine);
//     }
//     tos_sleep_ms(500);
// }

k_task_t k_toggle_led;
uint8_t stk_toggle_led[TASK_SIZE_TOGGLE_LED];
void task_toggle_led(void *pdata)
{
  while (1)
  {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    tos_sleep_ms(500);
  }
}

// Wifi initialization and connection to AP
k_task_t *k_wifi_connect;
char *wifi_ssid = "iPhone8";
char *wifi_pwd = "qwertyuiop";
void task_wifi_connect(void *pdata)
{
  if (esp8266_sal_init(HAL_UART_PORT_0) == 0)
  {
    if (esp8266_join_ap(wifi_ssid, wifi_pwd) != 0)
    {
      printf("AP joining failed\n");
    }
    else
    {
      printf("AP joning success\n");
      tos_task_create_dyn(&k_js_server, "js_server", task_js_server, NULL,
                          4, TASK_JS_SERVER_SIZE, 0);
      tos_task_destroy(NULL);
    }
  }
}

// JS server
k_task_t *k_js_server;
char *server_ip = "167.179.70.248";
char *server_port = "4000";
int tcp_socket_id = -1;
void task_js_server(void *pdata)
{
  printf("start tcp connection test\n");
  tcp_socket_id = tos_sal_module_connect(server_ip, server_port, TOS_SAL_PROTO_TCP);
  if (tcp_socket_id == -1)
  {
    printf("TCP0 connect failed\r\n");
  }
  else
  {
    printf("TCP0 connect success! fd: %d\n", tcp_socket_id);
    tos_sal_module_send(tcp_socket_id, (const void *)"This is TCP Test!\r\n", strlen("This is TCP Test!\r\n"));
  }
  tos_sleep_ms(1000);
  tcp_socket_id = tos_sal_module_close(tcp_socket_id);
  if (tcp_socket_id != -1)
  {
    printf("Close connection success!");
  }
}