//
// Created by joey on 2024-06-18.
//

#include "pinChangeInterrupt.h"

/****************************/
/****** ready pin flag ******/
/****************************/

volatile bool flagWhatHzSensor = false;

void enableSensorReadyPinWhatHz()
{
		flagWhatHzSensor = true;
}

void disableSensorReadyPinWhatHz()
{
		flagWhatHzSensor = false;
}

bool isSensorReadyPinWhatHz()
{
		return flagWhatHzSensor;
}

/****************************/
/********* handler **********/
/****************************/

void handlerSensor(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
}

void initRDYPinSensor()
{
		ret_code_t err_code;
		
		nrf_drv_gpiote_in_config_t configSensor = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
    configSensor.pull = NRF_GPIO_PIN_PULLUP;

    err_code = nrf_drv_gpiote_in_init(P12, &configSensor, handlerSensor);
    APP_ERROR_CHECK(err_code);
		
    nrf_drv_gpiote_in_event_enable(P12, true);
}


void initPinChangeInterrupt()
{
    ret_code_t err_code;
	
    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);
		
//		initRDYPinSensor();
}