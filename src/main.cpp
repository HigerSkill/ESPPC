#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_netif.h"
#include "lwip/dns.h"
#include "lwip/ip_addr.h"

#include "weather.h"
#include "wifi.h"

static const char* TAG = "main";

const char* kSSID = "Keenetic-6131";
const char* kPASS = "";

extern "C" void app_main(void) {
    esp_log_level_set("*", ESP_LOG_NONE);
    esp_log_level_set(TAG, ESP_LOG_INFO);
    esp_log_level_set(TAG_WEATHER, ESP_LOG_INFO);

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }

    vTaskDelay(pdMS_TO_TICKS(5000));
    ESP_LOGI(TAG, "ESP32 started! Welcome!");

    wifi_init_sta(kSSID, kPASS);

    vTaskDelay(pdMS_TO_TICKS(3000));
    getWeather();

    while (true) {
        ESP_LOGI(TAG, "Still alive...");
        vTaskDelay(pdMS_TO_TICKS(20000));
    }
}