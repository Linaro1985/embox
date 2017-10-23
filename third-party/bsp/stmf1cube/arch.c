/**
 * @file
 * @brief
 *
 * @author  Maxim Anisimov
 * @date    20.10.2017
 */

#include <assert.h>
#include <stdint.h>

#include <hal/arch.h>
#include <hal/clock.h>

#include <system_stm32f1xx.h>
#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_cortex.h>

#include <framework/mod/options.h>
#include <module/embox/arch/system.h>

static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
    {
        printf(">>> SystemClock_Config failed\n");
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
            |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2)!= HAL_OK)
    {
        printf(">>> SystemClock_Config failed\n");
    }

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        printf(">>> RTC and ADC clocks failed\n");
    }
}

extern void nvic_table_fill_stubs(void);

void arch_init(void) {
    static_assert(OPTION_MODULE_GET(embox__arch__system, NUMBER, core_freq) == 72000000);
    
    SystemInit();
    HAL_Init();
    
    nvic_table_fill_stubs();
    
    SystemClock_Config();
}

void arch_idle(void) {

}

void arch_shutdown(arch_shutdown_mode_t mode) {
    switch (mode) {
    case ARCH_SHUTDOWN_MODE_HALT:
    case ARCH_SHUTDOWN_MODE_REBOOT:
    case ARCH_SHUTDOWN_MODE_ABORT:
    default:
        HAL_NVIC_SystemReset();
        break;
    }

    /* NOTREACHED */
    while(1) {

    }
}


HAL_StatusTypeDef HAL_InitTick (uint32_t TickPriority) {
    return HAL_OK;
}

uint32_t HAL_GetTick(void) {
    return clock_sys_ticks();
}

