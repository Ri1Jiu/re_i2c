#ifndef AHT20_H
#define AHT20_H

#include "i2c.h"
void AHT20_Init();

void AHT20_Read( float *Temperature ,  float *Humidity );

void ATH20_Measure();

void ATH20_Get();

void ATH20_Analysis( float *Temperature ,  float *Humidity );

// #define AHT20_I2C_ADDRESS 0x38

// HAL_StatusTypeDef AHT20_Init(I2C_HandleTypeDef *hi2c);
// HAL_StatusTypeDef AHT20_ReadData(I2C_HandleTypeDef *hi2c, uint8_t *data);
// HAL_StatusTypeDef AHT20_Reset(I2C_HandleTypeDef *hi2c);

#endif // AHT20_H