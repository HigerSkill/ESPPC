#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "lwip/dns.h"
#include "lwip/ip_addr.h"

static const char* TAG_WIFI = "wifi";


void set_dns() {
    ip_addr_t dnsserver;
    IP_ADDR4(&dnsserver, 8, 8, 8, 8);
    dns_setserver(0, &dnsserver);
  }
  
void wifi_init_sta(const char* ssid, const char* pass) {
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    wifi_config_t wifi_config = {};
    strncpy((char*)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid));
    strncpy((char*)wifi_config.sta.password, pass, sizeof(wifi_config.sta.password));

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start();

    set_dns();

    ESP_LOGI(TAG_WIFI, "Connecting to WiFi: %s", ssid);

    esp_wifi_connect();

    wifi_ap_record_t ap_info;
    while (esp_wifi_sta_get_ap_info(&ap_info) != ESP_OK) {
        ESP_LOGI(TAG_WIFI, "Waiting for connection...");
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    ESP_LOGI(TAG_WIFI, "Connected!");
}