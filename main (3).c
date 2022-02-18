#include  <stdio.h>
#include  <string.h>
#include  <stdlib.h>
#include  "freertos/FreeRTOS.h"
#include  "freertos/task.h"
#include  "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_spi_flash.h"


#define WIFI_SSID "Sovannmunny"
#define WIFI_PASSWORD "dithsovannmunny"


static EventGroupHandle_t wifi_event_group_handler;

static void wifi_init_sta(void);

void app_main(void)
{
	 esp_err_t ret = nvs_flash_init();
	 if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	 {
	   ESP_ERROR_CHECK(nvs_flash_erase());
	   ret = nvs_flash_init();
	 }
	 ESP_ERROR_CHECK(ret);

	 printf("ESP_WIFI_MODE_STA \n");
	 wifi_init_sta();
}

void wifi_init_sta(void)
{
  wifi_event_group_handler = xEventGroupCreate();

  ESP_ERROR_CHECK( esp_netif_init());
  ESP_ERROR_CHECK( esp_event_loop_create_default());

  esp_netif_create_default_wifi_sta();

  wifi_init_config_t ctg = WIFI_INIT_CONFIG_DEFAULT();

  ESP_ERROR_CHECK( esp_wifi_init(&ctg));

  wifi_config_t sta_config =
      {
          .sta =
          {
              .ssid = WIFI_SSID,
              .password = WIFI_PASSWORD

          }
      };
  ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK( esp_wifi_start() );
  ESP_ERROR_CHECK( esp_wifi_connect() );

  printf("wifi_init_sta finished. \n");

  while (true)
    {
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}

