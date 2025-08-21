#include "sensor.h"
#include "display.h"
#include "led.h"

void app_main(void) {
    sensor_init(/* pins */);
    display_init(/* i2c, sda, scl */);
    led_init(/* gpio */);

    while (1) {
        float v = sensor_read();
        display_print(0, "Value:");
        display_print(1, /* แปลงเป็นสตริงของ v */);
        if (v > 100.0f) led_on(); else led_off();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}