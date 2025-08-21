#include "led.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"

static int s_led_gpio = -1;
static bool s_led_state = false;

// ใช้ช่อง PWM และ Timer หนึ่งช่องสำหรับ LED
#define LEDC_MODE           LEDC_HIGH_SPEED_MODE
#define LEDC_CHANNEL        LEDC_CHANNEL_0
#define LEDC_TIMER          LEDC_TIMER_0
#define LEDC_FREQUENCY      5000        // 5 kHz
#define LEDC_RESOLUTION     LEDC_TIMER_8_BIT // 0–255 duty

void led_init(int gpio_num)
{
    s_led_gpio = gpio_num;

    // ตั้งค่า LEDC Timer
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_RESOLUTION,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // ตั้งค่า LEDC Channel
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = s_led_gpio,
        .duty           = 0, // เริ่มต้นปิด
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);

    s_led_state = false;
}

void led_on(void)
{
    if (s_led_gpio < 0) return;
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 255); // duty max
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
    s_led_state = true;
}

void led_off(void)
{
    if (s_led_gpio < 0) return;
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
    s_led_state = false;
}

void led_toggle(void)
{
    if (s_led_state) {
        led_off();
    } else {
        led_on();
    }
}

void led_set_brightness(int duty_cycle)
{
    if (s_led_gpio < 0) return;
    if (duty_cycle < 0) duty_cycle = 0;
    if (duty_cycle > 100) duty_cycle = 100;

    int duty = (255 * duty_cycle) / 100; // map 0–100% → 0–255
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

    s_led_state = (duty > 0);
}