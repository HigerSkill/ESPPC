#ifndef WEATHER_H
#define WEATHER_H

#include <esp_http_client.h>
#include "esp_log.h"
#include "lwip/netdb.h"

static const char* TAG_WEATHER = "weather";

const char* WEATHER_URL = "http://api.openweathermap.org/data/2.5/weather?lat=55.68&lon=37.58&lang=ru&appid=";


void getWeather() {
    esp_http_client_config_t config = {
        .url = WEATHER_URL,
        .method = HTTP_METHOD_GET,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_open(client, 0);
    int content_length = esp_http_client_fetch_headers(client);

    if (content_length <= 0 || content_length > 2048) {
        ESP_LOGW(TAG_WEATHER, "Unexpected content length");
        esp_http_client_close(client);
        esp_http_client_cleanup(client);
        return;
    }

    char* buffer = new char[content_length + 1]();
    int total_read = esp_http_client_read(client, buffer, content_length);
    buffer[total_read] = '\0';

    if (total_read > 0) {
        ESP_LOGI(TAG_WEATHER, "WEATHER: %s", buffer);
    } else {
        ESP_LOGW(TAG_WEATHER, "No data read from server.");
    }

    delete[] buffer;
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
}


#endif