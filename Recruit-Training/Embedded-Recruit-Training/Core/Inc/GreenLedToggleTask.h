#pragma once

#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_can.h"
#include "cmsis_os.h"
#include "main.h"

extern CAN_HandleTypeDef hcan2;
extern CAN_TxHeaderTypeDef canTxHdr;
extern uint8_t greenLedToggleFlag;
extern osMutexId_t canMutex;

void greenLedToggleTask(void const* arg);
