//
// Created by joey on 2024-06-18.
//

#include "timeInterrupt.h"

/* Timer instance. */
const nrf_drv_timer_t timerSelect1 = NRF_DRV_TIMER_INSTANCE(1);

static uint16_t counter50Hz = 0;

void handlerTimer1(nrf_timer_event_t event_type, void* p_context)
{
/* Timer 250Hz */
		scanButton();
/* Timer 50Hz */
		counter50Hz++;
		if(counter50Hz >= 5)
		{	
				counter50Hz = 0;
		}
}

void initTimerInterrupt()
{
    uint32_t time_ms = 1; 																														// Time Setting
    uint32_t time_ticks;
    uint32_t err_code = NRF_SUCCESS;

    nrf_drv_timer_config_t configTimer1 = NRF_DRV_TIMER_DEFAULT_CONFIG;
    err_code = nrf_drv_timer_init(&timerSelect1, &configTimer1, handlerTimer1); 			// Use Timer1
    APP_ERROR_CHECK(err_code);

    time_ticks = nrf_drv_timer_ms_to_ticks(&timerSelect1, time_ms);

    nrf_drv_timer_extended_compare(
             &timerSelect1, NRF_TIMER_CC_CHANNEL1, time_ticks, NRF_TIMER_SHORT_COMPARE1_CLEAR_MASK, true);

    nrf_drv_timer_enable(&timerSelect1);
}
