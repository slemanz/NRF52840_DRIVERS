#include "driver_gpio.h"

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0;

    temp |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPd << 2) | (pGPIOHandle->GPIO_PinConfig.GPIO_InpBuf << 1) |
            (pGPIOHandle->GPIO_PinConfig.GPIO_PinDir << 0); 

    pGPIOHandle->pGPIOx->PIN_CNF[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber] = temp;

    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinDir == GPIO_DIR_OUT)
    {
        GPIO_WriteToOutputPin(pGPIOHandle->pGPIOx, pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber, pGPIOHandle->GPIO_PinConfig.GPIO_PinState);
    }
}

uint8_t  GPIO_ReadFromInputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    if(pGPIOx->IN & (1 << PinNumber))
    {
        return GPIO_PIN_SET;
    }
    return GPIO_PIN_RESET;
}

void GPIO_WriteToOutputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value)
{
    if(value == GPIO_PIN_SET)
    {
        pGPIOx->OUT |= (1 << PinNumber);
    }else
    {
        pGPIOx->OUT &= ~(1 << PinNumber);
    }
}

void GPIO_ToggleOutputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber)
{
        pGPIOx->OUT ^= (1 << PinNumber);
}