#ifndef LED_H
#define LED_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize LED module
 *
 * @param gpio_num GPIO pin number where LED is connected
 */
void led_init(int gpio_num);

/**
 * @brief Turn LED on
 */
void led_on(void);

/**
 * @brief Turn LED off
 */
void led_off(void);

/**
 * @brief Toggle LED state (on -> off, off -> on)
 */
void led_toggle(void);

/**
 * @brief Set LED brightness using PWM (0-100%)
 *
 * @param duty_cycle Brightness percentage (0 = off, 100 = fully on)
 */
void led_set_brightness(int duty_cycle);

#ifdef __cplusplus
}
#endif

#endif // LED_H