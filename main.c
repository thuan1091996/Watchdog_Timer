/* --------0.Project information--------------------
 * Watchdog-timer easy example
 * Debug through LEDs
 * Author : TRAN MINH THUAN
---------------------------------------------------*/

/* ------------------------------1.System requirement-------------------------------
1.Initialize watchdog-timer to reset system after 1'30s seconds if don't press the button
  (User Switch 1) (Reload ->2 second) without using watchdog-timer interrupt
2.Initial RED LED off, if press the button -> on LED then when the system reset the LED will be off once again

-----------------------------------------------------------------------------------*/
#include "include.h"


#define SWITCH              GPIO_PIN_4
#define LED                 GPIO_PIN_1
#define SWITCH_PORT         GPIO_PORTF_BASE
#define LED_PORT            GPIO_PORTF_BASE


int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    //Configure Input pins
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOInput(SWITCH_PORT, SWITCH);
    GPIOPadConfigSet(SWITCH_PORT, SWITCH, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);
    //Configure Output pins
    GPIOPinTypeGPIOOutput(LED_PORT, LED);
    GPIOPinWrite(LED_PORT, LED, 0);
    Watchdog_Init(3);
    IntMasterDisable();
    while(1)
    {
        if(GPIOPinRead(SWITCH_PORT,SWITCH)==0)
        {
            GPIOPinWrite(LED_PORT, LED, 2);
            Watchdog_Feed(3);
        }
    }
}


