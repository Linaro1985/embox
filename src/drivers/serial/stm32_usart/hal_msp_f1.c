/**
 * @file
 *
 * @author: Anton Bondarev
 *              Initial implementation
 * @author: Denis Deryugin <deryugin.denis@gmail.com>
 *              Support multiple UART
 * @author: Maxim Anisimov
 * 		Initial implementation for stm32f103
 * 
 */

#include <assert.h>

#include <drivers/serial/stm_usart.h>

void USART_TX_GPIO_CLK_ENABLE(void *usart_base) {
	if (usart_base == USART1 || usart_base == USART2)
		__HAL_RCC_GPIOA_CLK_ENABLE();
	else 
		/* Not supported */
		assert(0);
}

void USART_RX_GPIO_CLK_ENABLE(void *usart_base) {
	if (usart_base == USART1 || usart_base == USART2)
		__HAL_RCC_GPIOA_CLK_ENABLE();
	else 
		/* Not supported */
		assert(0);
}

void USART_CLK_ENABLE(void *usart_base) {
	if (usart_base == USART1)
		__HAL_RCC_USART1_CLK_ENABLE();
	else if (usart_base == USART2)
		__HAL_RCC_USART2_CLK_ENABLE();
	else
		/* Not supported */
		assert(0);
}

uint16_t USART_RX_PIN(void *usart_base) {
	if (usart_base == USART1)
		return GPIO_PIN_10;
	if (usart_base == USART2)
		return GPIO_PIN_3;
	/* Not supported */
	assert(0);
	return 0;
}

uint16_t USART_TX_PIN(void *usart_base) {
	if (usart_base == USART1)
		return GPIO_PIN_9;
	if (usart_base == USART2)
		return GPIO_PIN_2;
	/* Not supported */
	assert(0);
	return 0;
}

GPIO_TypeDef *USART_RX_GPIO_PORT(void *usart_base) {
	if (usart_base == USART1 || usart_base == USART2)
		return GPIOA;
	/* Not supported */
	assert(0);
	return 0;
}

GPIO_TypeDef *USART_TX_GPIO_PORT(void *usart_base) {
	if (usart_base ==  USART1 || usart_base ==  USART2)
		return GPIOA;
	/* Not supported */
	assert(0);
	return 0;
}


void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
	GPIO_InitTypeDef GPIO_InitStruct;
	void *uart_base = huart->Instance;

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */
	USART_TX_GPIO_CLK_ENABLE(uart_base);
	USART_RX_GPIO_CLK_ENABLE(uart_base);

	/* Enable USARTx clock */
	USART_CLK_ENABLE(uart_base);

	/*##-2- Configure peripheral GPIO ##########################################*/
	/* UART TX GPIO pin configuration  */
	GPIO_InitStruct.Pin = USART_TX_PIN(uart_base);
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(USART_TX_GPIO_PORT(uart_base), &GPIO_InitStruct);

	/* UART RX GPIO pin configuration  */
	GPIO_InitStruct.Pin = USART_RX_PIN(uart_base);

	HAL_GPIO_Init(USART_RX_GPIO_PORT(uart_base), &GPIO_InitStruct);

	/*##-3- Configure the NVIC for UART ########################################*/
	/* NVIC for USART */
}
