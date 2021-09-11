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
                          4, TASK_SIZE_JS_SERVER, 0);
      tos_task_destroy(NULL);
    }
  }
}

// JS server
k_task_t *k_js_server;
char *server_ip = "167.179.70.248";
char *server_port = "4001";
int tcp_socket_id = -1;
char *js_prefix = "js_content:";
char recv_buf[512];
char js_script[512];
void task_js_server(void *pdata)
{
  JS *js = js_create_static();
  js_driver_init(js);
  printf("start tcp connection test\n");
  tcp_socket_id = tos_sal_module_connect(server_ip, server_port, TOS_SAL_PROTO_TCP);
  if (tcp_socket_id == -1)
  {
    printf("TCP0 connect failed\r\n");
  }
  else
  {
    printf("TCP0 connect success! fd: %d\n", tcp_socket_id);
    while (K_TRUE)
    {
      int recv_len = tos_sal_module_recv(tcp_socket_id, recv_buf, sizeof(recv_buf));
      if (recv_len == 0)
      {
        continue;
      }
      if (strncmp(js_prefix, recv_buf, strlen(js_prefix)) != 0)
      {
        continue;
      }
      sprintf(js_script, "%.*s", recv_len - strlen(js_prefix) + 1, recv_buf + strlen(js_prefix));
      printf("js_script: %s\n", js_script);
      JS *js = js_create_static();
      js_driver_init(js);
      js_eval(js, js_script, ~0);
    }
  }
}