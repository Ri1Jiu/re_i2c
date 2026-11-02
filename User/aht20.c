#include "aht20.h"
#define AHT20_ADDRESS 0x70

uint8_t readBuffer[6] = {0 };


void AHT20_Init()       //初始化
{
    uint8_t readBuffer;
    HAL_Delay(40);
    HAL_I2C_Master_Receive(&hi2c1, AHT20_ADDRESS ,&readBuffer,1,100);
    if( (readBuffer & 0x08) == 0x00 )
    {
        uint8_t sendBuffer[3] = { 0xBE, 0x08 , 0x00 };
        HAL_I2C_Master_Transmit(&hi2c1, AHT20_ADDRESS,&sendBuffer,3 , 100);
    }
}


void AHT20_Read( float *Temperature ,  float *Humidity )
{   uint8_t sendBuffer[3] = { 0xAC , 0x33, 0x00 };
    uint8_t readBuffer[6] = {0 };
    HAL_I2C_Master_Transmit_IT(&hi2c1, AHT20_ADDRESS , sendBuffer , 3);

    HAL_Delay(75);

    HAL_I2C_Master_Receive_IT(&hi2c1, AHT20_ADDRESS , readBuffer , 6);
    if((0x80 & readBuffer[0]) == 0x00)
    {
        uint32_t data1 = 0;
        data1 = ((uint32_t)readBuffer[3] >> 4 ,(uint32_t)readBuffer[2] << 4,(uint32_t)readBuffer[1] << 12);
        *Temperature = data1 * 100.0f / (1 << 20);
        uint32_t data2 = 0;
        data2 = ((uint32_t)readBuffer[5],(uint32_t)readBuffer[4] << 8,((uint32_t)readBuffer[3] & 0x0F)<< 16);
        *Humidity = data2*200.0f / (1 << 20) - 50;
     }
}


void ATH20_Measure()
{   static uint8_t sendBuffer[3] = { 0xAC , 0x33, 0x00 };
    HAL_I2C_Master_Transmit_IT(&hi2c1, AHT20_ADDRESS , sendBuffer , 3);

}


void ATH20_Get()
{
   HAL_I2C_Master_Receive_IT(&hi2c1, AHT20_ADDRESS , readBuffer , 6); 
}

void ATH20_Analysis( float *Temperature ,  float *Humidity )
{
    if((0x80 & readBuffer[0]) == 0x00)
    {
        uint32_t data1 = 0;
        data1 = ((uint32_t)readBuffer[3] >> 4 ,(uint32_t)readBuffer[2] << 4,(uint32_t)readBuffer[1] << 12);
        *Temperature = data1 * 100.0f / (1 << 20);
        uint32_t data2 = 0;
        data2 = ((uint32_t)readBuffer[5],(uint32_t)readBuffer[4] << 8,((uint32_t)readBuffer[3] & 0x0F)<< 16);
        *Humidity = data2*200.0f / (1 << 20) - 50;
     }
     
}