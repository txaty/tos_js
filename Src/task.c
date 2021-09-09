#include "task.h"
#include "js.h"
#include "util.h"
#include "gpio.h"
#include "js_apps.h"
#include "tos_at.h"

// mutex
k_mutex_t mutex_js_engine;

// completion
k_completion_t completion_wifi_connted;

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
        tos_completion_post(&completion_wifi_connted);
      }
    }
}


