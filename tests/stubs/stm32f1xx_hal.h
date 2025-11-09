#pragma once
#include <stdint.h>
#include <stddef.h>

// Minimal STM32 HAL stubs so host builds succeed.
typedef struct {} GPIO_TypeDef;
typedef struct {} TIM_HandleTypeDef;
typedef struct {} I2C_HandleTypeDef;
typedef struct {} UART_HandleTypeDef;
typedef struct {} ADC_HandleTypeDef;

static inline uint32_t HAL_GetTick(void){ return 0; }
static inline void HAL_Delay(uint32_t ms){ (void)ms; }

// GPIO mock bits
#ifndef __IO
#define __IO volatile
#endif
#define GPIO_PIN_0  ((uint16_t)0x0001)
#define GPIO_PIN_1  ((uint16_t)0x0002)
#define GPIO_PIN_2  ((uint16_t)0x0004)
#define GPIO_PIN_3  ((uint16_t)0x0008)
#define GPIO_PIN_4  ((uint16_t)0x0010)
#define GPIO_PIN_5  ((uint16_t)0x0020)
#define GPIO_PIN_6  ((uint16_t)0x0040)
#define GPIO_PIN_7  ((uint16_t)0x0080)
#define GPIO_PIN_8  ((uint16_t)0x0100)
#define GPIO_PIN_9  ((uint16_t)0x0200)
#define GPIO_PIN_10 ((uint16_t)0x0400)
#define GPIO_PIN_11 ((uint16_t)0x0800)
#define GPIO_PIN_12 ((uint16_t)0x1000)
#define GPIO_PIN_13 ((uint16_t)0x2000)
#define GPIO_PIN_14 ((uint16_t)0x4000)
#define GPIO_PIN_15 ((uint16_t)0x8000)

static GPIO_TypeDef _gpioA, _gpioB, _gpioC, _gpioD;
#define GPIOA (&_gpioA)
#define GPIOB (&_gpioB)
#define GPIOC (&_gpioC)
#define GPIOD (&_gpioD)

static inline int HAL_GPIO_ReadPin(GPIO_TypeDef* port, uint16_t pin){
    (void)port; (void)pin; return 0;
}
static inline void HAL_GPIO_WritePin(GPIO_TypeDef* port, uint16_t pin, uint32_t val){
    (void)port; (void)pin; (void)val;
}

// UART mock
static inline void HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout){
    (void)huart; (void)pData; (void)Size; (void)Timeout;
}

