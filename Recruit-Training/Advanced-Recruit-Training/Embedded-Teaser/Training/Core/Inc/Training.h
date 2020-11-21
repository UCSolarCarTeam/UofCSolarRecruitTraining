#pragma once
#include <stdint.h>

uint8_t outputArray[3];
uint8_t validData; // Set bits 0, 1, 2 if the input array elements were valid

void trainingTask(uint8_t* data); // data should be 3 elements wide (size of 3)

uint8_t getbit(uint8_t data,int number);

int getvelocity(uint8_t data);

void checkmotors(uint8_t *validity, uint8_t motor1, uint8_t motor2);

void checklights(uint8_t *validity, uint8_t lights);