#include "driver_saadc.h"

volatile int16_t result_adc = 0;

 void saadc_init(SAADC_Handle_t *pSAADCHandle)
 {
    uint32_t temp = 0;

    temp =  (pSAADCHandle->GAIN << SAADC_CH_CONFIG_GAIN_BIT) |
            (pSAADCHandle->MODE << SAADC_CH_CONFIG_MODE_BIT) |
            (pSAADCHandle->REFSEL << SAADC_CH_CONFIG_REFSEL_BIT) |
            (pSAADCHandle->RESN << SAADC_CH_CONFIG_RESN_BIT) |
            (pSAADCHandle->RESP << SAADC_CH_CONFIG_RESP_BIT) |
            (pSAADCHandle->TACQ << SAADC_CH_CONFIG_TACQ_BIT);

    SAADC->CH[pSAADCHandle->CHANNEL].CONFIG = temp;
    SAADC->CH[pSAADCHandle->CHANNEL].PSELP  = pSAADCHandle->PSELP;
    SAADC->CH[pSAADCHandle->CHANNEL].PSELN  = pSAADCHandle->PSELN;

    SAADC->RESOLUTION = pSAADCHandle->RESOLUTION;

    SAADC->RESULT.MAXCNT = 1;
    SAADC->RESULT.PTR   = (uint32_t)&result_adc;

    SAADC->ENABLER = 1;
    saadc_calibrate();
 }


 void saadc_calibrate(void)
 {
    SAADC->TASKS_CALIBRATEOFFSET = 1;
    while(SAADC->EVENTS_CALIBRATEDONE == 0);
    SAADC->EVENTS_CALIBRATEDONE = 0;
    while(SAADC->STATUS == (1 << 0));
 }

uint16_t saadc_read(void)
{
   SAADC->TASKS_START = 1;
   while (SAADC->EVENTS_STARTED == 0);
   SAADC->EVENTS_STARTED = 0;

   while (SAADC->EVENTS_RESULTDONE == 0);
   SAADC->EVENTS_RESULTDONE = 0;

   // Do a SAADC sample, will put the result in the configured RAM buffer.
   SAADC->TASKS_SAMPLE = 1;
   while (SAADC->EVENTS_END == 0);
   SAADC->EVENTS_END = 0;

   if( result_adc & (1 << 15)) return 0;
   return result_adc;
}