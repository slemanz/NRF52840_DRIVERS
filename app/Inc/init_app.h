#ifndef INIT_APP_H_
#define INIT_APP_H_

#include <stdint.h>

#define CPU_FREQ        (64000000)
#define SYSTICK_FREQ    (1000) // in hz (1000hz == every 1 ms)

#define LED_BLUE_PIN        GPIO_PIN_NO_6
#define LED_GREEN_PIN       GPIO_PIN_NO_16
#define LED_RED_PIN         GPIO_PIN_NO_24
#define LED_BUILT_IN        GPIO_PIN_NO_13
#define LED1_EXT_PIN        GPIO_PIN_NO_5

#define BUTTON1_PORT           GPIOP1
#define BUTTON1_PIN            GPIO_PIN_NO_2

// SPI
#define SPI_PORT            GPIOP1
#define SPI_PIN_MISO        GPIO_PIN_NO_2
#define SPI_PIN_MOSI        GPIO_PIN_NO_8
#define SPI_PIN_SCK         GPIO_PIN_NO_1
#define CS_PORT             GPIOP0
#define CS_PIN              GPIO_PIN_NO_27

void system_init(void);

uint64_t system_get_ticks(void);

#endif /* INIT_APP_H_*/