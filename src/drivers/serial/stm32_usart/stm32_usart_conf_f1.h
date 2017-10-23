/**
 * @file
 *
 * @data 03.12.2015
 * @author: Anton Bondarev
 * @author: Maxim Anisimov
 */

#ifndef SRC_DRIVERS_SERIAL_STM32_USART_STM32_USART_CONF_F1_H_
#define SRC_DRIVERS_SERIAL_STM32_USART_STM32_USART_CONF_F1_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor USARTx/UARTx instance used and associated
   resources */
/* Definition for USARTx clock resources */

#include <framework/mod/options.h>
#define MODOPS_USARTX OPTION_GET(NUMBER, usartx)

#if MODOPS_USARTX == 1

#define USARTx                           USART1
#define USARTx_CLK_ENABLE()              __USART1_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __USART1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_9
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_RX_PIN                    GPIO_PIN_10
#define USARTx_RX_GPIO_PORT              GPIOA

/* Definition for USARTx's NVIC */
/* In Embox we assume that the lower external irq number is 0,
 * but in the cortexm3 it is -15 */
#define USARTx_IRQn                      USART1_IRQn + 16
#define USARTx_IRQHandler                USART1_IRQHandler

#elif MODOPS_USARTX == 2

#define USARTx                           USART2
#define USARTx_CLK_ENABLE()              __USART2_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __USART2_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_2
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_RX_PIN                    GPIO_PIN_3
#define USARTx_RX_GPIO_PORT              GPIOA

/* Definition for USARTx's NVIC */
/* In Embox we assume that the lower external irq number is 0,
 * but in the cortexm3 it is -15 */
#define USARTx_IRQn                      USART2_IRQn + 16
#define USARTx_IRQHandler                USART2_IRQHandler

#endif

#define STM32_USART_FLAGS(uart)   uart->SR
#define STM32_USART_RXDATA(uart)  uart->DR
#define STM32_USART_TXDATA(uart)  uart->DR

#endif /* SRC_DRIVERS_SERIAL_STM32_USART_STM32_USART_CONF_F1_H_ */
