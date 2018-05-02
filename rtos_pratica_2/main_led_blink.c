/**
 *  \file   main.c
 *
 *  \brief  Example application main file. This application will toggle the led.
 *          The led toggling will be done inside an callback function, which
 *          will be called by Interrupt Service Routine. Interrupts are
 *          triggered manually and no external source is used to trigger
 *          interrupts.
 *
 */

/*
 * Copyright (C) 2014 - 2016 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#ifndef BARE_METAL
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>


/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#endif

#include <stdio.h>

/* TI-RTOS Header files */
#include <ti/drv/gpio/GPIO.h>
#include <ti/drv/gpio/soc/GPIO_soc.h>

#include "GPIO_log.h"
#include "GPIO_board.h"

#include <ti/board/board.h>
#include <ti/sysbios/family/arm/a8/intcps/Hwi.h>

//Biblioteca para o Clock
#include <ti/sysbios/knl/Clock.h>
//Biblioteca para o Semaphoro
#include <ti/sysbios/knl/Semaphore.h>

/**********************************************************************
 ************************** Macros ************************************
 **********************************************************************/
#if defined(SOC_AM574x) || defined(SOC_AM572x) || defined (SOC_AM571x)
#if defined (__TI_ARM_V7M4__)
#define DELAY_VALUE       (0x6FFFFFU) /* Update Delay as it is not sufficent for M4 core */
#else
#define DELAY_VALUE       (0x6FFFFFU)
#endif
#else
#define DELAY_VALUE       (0xFFFFFFU)
#define PROC_UNIT         (0xFFFFU)
#endif

/**********************************************************************
 ************************** Internal functions ************************
 **********************************************************************/

/* Delay function */
void AppDelay(unsigned int delayVal);

/* Callback function */
void AppGpioCallbackFxn(void);

#if defined(idkAM574x) || defined(idkAM572x) || defined(idkAM571x)
/* GPIO clock and pinmux configurations */
extern void AppGPIOInit(void);
#endif

#if defined(idkAM574x) || defined(idkAM572x)
extern void GPIOApp_UpdateBoardInfo(void);
extern void GPIOAppUpdateConfig(uint32_t *gpioBaseAddr, uint32_t *gpioPin);
#endif

/*
 *  ======== Board_initI2C ========
 */
static void Board_initGPIO(void)
{
    Board_initCfg boardCfg;

#if defined(SOC_K2H) || defined(SOC_K2K) || defined(SOC_K2E) || defined(SOC_K2L) || defined(SOC_K2G) || defined(SOC_C6678) || defined(SOC_C6657) || defined(SOC_OMAPL137) || defined(SOC_OMAPL138)
    GPIO_v0_HwAttrs gpio_cfg;

    /* Get the default SPI init configurations */
    GPIO_socGetInitCfg(GPIO_LED0_PORT_NUM, &gpio_cfg);

    /* Modify the default GPIO configurations if necessary */

    /* Set the default GPIO init configurations */
    GPIO_socSetInitCfg(GPIO_LED0_PORT_NUM, &gpio_cfg);

#if defined(SOC_K2G)
    /* Setup GPIO interrupt configurations */
    GPIO_socSetIntMux(GPIO_LED0_PORT_NUM, GPIO_LED0_PIN_NUM, NULL, GPIO_MUX_SEL);
#endif
#if defined(SOC_OMAPL137) || defined(SOC_OMAPL138)
    /* Setup GPIO interrupt configurations */
    GPIO_socSetBankInt(GPIO_LED0_PORT_NUM, GPIO_LED0_PIN_NUM, NULL);
#endif
#endif

#if defined(evmK2E) || defined(evmC6678)
    boardCfg = BOARD_INIT_MODULE_CLOCK |
        BOARD_INIT_UART_STDIO;
#else
    boardCfg = BOARD_INIT_PINMUX_CONFIG |
        BOARD_INIT_MODULE_CLOCK |
        BOARD_INIT_UART_STDIO;
#endif
    Board_init(boardCfg);

#if defined(idkAM572x) || defined(idkAM574x)
    GPIOApp_UpdateBoardInfo();
#endif
}

/**********************************************************************
 ************************** Global Variables **************************
 **********************************************************************/
volatile uint32_t gpio_intr_triggered = 0;
uint32_t gpioBaseAddr = SOC_GPIO_1_REGS;
uint32_t gpioPin;

#ifndef BARE_METAL
#define TOGGLE  (0x01u)

Semaphore_Struct semaphore0, semaphore1, semaphore2, semaphore3;
Semaphore_Params semaphoreParams0, semaphoreParams1, semaphoreParams2, semaphoreParams3;
Error_Block eb;

int toggle = 0;
int gpio = 23;


/*
 * Funções para piscar o led task
 */

void led1(UArg arg0, UArg arg1){
    while(1){
        GPIOPinWrite(GPIO_BASE_ADDR, 21, GPIO_PIN_HIGH);
        AppDelay(DELAY_VALUE);
        GPIOPinWrite(GPIO_BASE_ADDR, 21, GPIO_PIN_LOW);
        AppDelay(DELAY_VALUE);
        Task_sleep(1); // Mandar a task parar para que a outra entre em ação
    }
}

void led2(UArg arg0, UArg arg1){
    while(1){
        GPIOPinWrite(GPIO_BASE_ADDR, 22, GPIO_PIN_HIGH);
        AppDelay(DELAY_VALUE);
        GPIOPinWrite(GPIO_BASE_ADDR, 22, GPIO_PIN_LOW);
        AppDelay(DELAY_VALUE);
        Task_sleep(1);
    }
}
void led3(UArg arg0, UArg arg1){
    while(1){
        GPIOPinWrite(GPIO_BASE_ADDR, 23, GPIO_PIN_HIGH);
        AppDelay(DELAY_VALUE);
        GPIOPinWrite(GPIO_BASE_ADDR, 23, GPIO_PIN_LOW);
        AppDelay(DELAY_VALUE);
        Task_sleep(1);
    }
}

void led4(UArg arg0, UArg arg1){
    while(1){
        GPIOPinWrite(GPIO_BASE_ADDR, 24, GPIO_PIN_HIGH);
        AppDelay(DELAY_VALUE);
        GPIOPinWrite(GPIO_BASE_ADDR, 24, GPIO_PIN_LOW);
        AppDelay(DELAY_VALUE);
        Task_sleep(1);
    }
}

/*
 * Funções para piscar o led Semaphoro
 */

void ledSem1(){
    while(1){
        GPIOPinWrite(GPIO_BASE_ADDR, 21, GPIO_PIN_HIGH);
        AppDelay(PROC_UNIT);
        GPIOPinWrite(GPIO_BASE_ADDR, 21, GPIO_PIN_LOW);

        Semaphore_pend(Semaphore_handle(&semaphore0), BIOS_WAIT_FOREVER); // Avisar que a função esta pronta para executar
    }
}
void ledSem2(){
    while(1){
        Semaphore_pend(Semaphore_handle(&semaphore1), BIOS_WAIT_FOREVER);
        GPIOPinWrite(GPIO_BASE_ADDR, 22, GPIO_PIN_HIGH);
        AppDelay(2*PROC_UNIT);
        GPIOPinWrite(GPIO_BASE_ADDR, 22, GPIO_PIN_LOW);
    }
}
void ledSem3(){
    while(1){
        Semaphore_pend(Semaphore_handle(&semaphore2), BIOS_WAIT_FOREVER);
        GPIOPinWrite(GPIO_BASE_ADDR, 23, GPIO_PIN_HIGH);
        AppDelay(50*PROC_UNIT);
        GPIOPinWrite(GPIO_BASE_ADDR, 23, GPIO_PIN_LOW);
    }
}
void ledSem4(){
    while(1){
        Semaphore_pend(Semaphore_handle(&semaphore3), BIOS_WAIT_FOREVER);
        GPIOPinWrite(GPIO_BASE_ADDR, 24, GPIO_PIN_HIGH);
        AppDelay(1000*PROC_UNIT);
        GPIOPinWrite(GPIO_BASE_ADDR, 24, GPIO_PIN_LOW);
    }
}


void taskInt(){
        //Inicializando os pinos como saída
        GPIODirModeSet(gpioBaseAddr, 21, 0);
        GPIODirModeSet(gpioBaseAddr, 22, 0);
        GPIODirModeSet(gpioBaseAddr, 23, 0);
        GPIODirModeSet(gpioBaseAddr, 24, 0);

        Task_Params taskParams;
        gpioBaseAddr = GPIO_BASE_ADDR;
        Task_Params_init(&taskParams);
        taskParams.priority = 1;
        taskParams.stackSize = 0x1400;

        Task_create(led1, &taskParams, NULL);
        Task_create(led2, &taskParams, NULL);
        Task_create(led3, &taskParams, NULL);
        Task_create(led4, &taskParams, NULL);
}


void ledToggle(){
    toggle ^= 1;
    if(toggle){
        /* Driving a logic HIGH on the GPIO pin. */
        GPIOPinWrite(gpioBaseAddr, gpio, 1);
    }else{
         /* Driving a logic LOW on the GPIO pin. */
        GPIOPinWrite(gpioBaseAddr, gpio, 0);
    }
    GPIOPinIntClear(gpioBaseAddr,GPIO_INT_LINE_1, 16);
}


void HwInt(){
        Hwi_Params hwi_params;
        Hwi_Handle myHwi;

        Hwi_Params_init(&hwi_params);
        hwi_params.enableInt = FALSE;

        myHwi = Hwi_create(98, ledToggle, &hwi_params, NULL);


        if (myHwi == NULL) {
            System_abort("Hwi create failed");
        }

        Hwi_enableInterrupt(98);
        GPIODirModeSet(gpioBaseAddr, 16, GPIO_CFG_INPUT);
        GPIOIntTypeSet(gpioBaseAddr, 16, GPIO_INT_TYPE_RISE_EDGE);
        GPIOPinIntEnable(gpioBaseAddr, GPIO_INT_LINE_1, 16);

}

//Interup SoftWare
/*void SoftWInt(){
    Swi_Handle swi0;
    Swi_Params swiParams;
    Error_Block eb;
    Error_init(&eb);
    Swi_Params_init(&swiParams);
    swi0 = Swi_create(swiFunc, &swiParams, &eb);
    if (swi0 == NULL) {
    System_abort("Swi create failed");
    }
}*/


void funClock(){
    GPIO_log("Aqui! \n");
        GPIOPinWrite(GPIO_BASE_ADDR, 24, GPIO_PIN_HIGH);
        AppDelay(DELAY_VALUE);
        GPIOPinWrite(GPIO_BASE_ADDR, 24, GPIO_PIN_LOW);
        AppDelay(DELAY_VALUE);

}

void ClockInt(){
    //Criando interrupçao de clock
    Clock_Params clockParams;
    Clock_Handle myClock;
    Error_Block eb;
    Error_init(&eb);
    Clock_Params_init(&clockParams);
    clockParams.period = 5;
    clockParams.startFlag = TRUE;
    clockParams.arg = (UArg)0x5555;
    myClock = Clock_create(funClock, 5, &clockParams, &eb);
    if (myClock == NULL) {
    System_abort("Clock create failed");
    }
}


void freqClock(){
    // Compara o tempo do clock e chama os semaphoros
    if(Clock_getTicks()%50 == 0){
        Semaphore_post(Semaphore_handle(&semaphore0));
    }
    if(Clock_getTicks()%100 == 0){
        Semaphore_post(Semaphore_handle(&semaphore1));
    }
    if(Clock_getTicks()%200 == 0){
        Semaphore_post(Semaphore_handle(&semaphore2));
    }
    if(Clock_getTicks()%1000 == 0){
        Semaphore_post(Semaphore_handle(&semaphore3));
    }
}

void taskSemaph(){
        Task_Params task1, task2, task3, task4;
        gpioBaseAddr = GPIO_BASE_ADDR;

        //-----------------------------------
        Task_Params_init(&task1);
        task1.priority = 4;
        task1.stackSize = 0x1400;
        //-----------------------------------
        Task_Params_init(&task2);
        task2.priority = 3;
        task2.stackSize = 0x1400;
        //-----------------------------------
        Task_Params_init(&task3);
        task3.priority = 2;
        task3.stackSize = 0x1400;
        //-----------------------------------
        Task_Params_init(&task4);
        task4.priority = 1;
        task4.stackSize = 0x1400;
        //-----------------------------------
        Task_create(ledSem1, &task1, NULL);
        Task_create(ledSem2, &task2, NULL);
        Task_create(ledSem3, &task3, NULL);
        Task_create(ledSem4, &task4, NULL);

        // Semaphore 0
        Semaphore_Params_init(&semaphoreParams0);
        Semaphore_construct(&semaphore0, 0, &semaphoreParams0);
        // Semaphore 1
        Semaphore_Params_init(&semaphoreParams1);
        Semaphore_construct(&semaphore1, 0, &semaphoreParams1);
        // Semaphore 2
        Semaphore_Params_init(&semaphoreParams2);
        Semaphore_construct(&semaphore2, 0, &semaphoreParams2);
        // Semaphore 3
        Semaphore_Params_init(&semaphoreParams3);
        Semaphore_construct(&semaphore3, 0, &semaphoreParams3);

        //Criando interrupçao de clock
        Clock_Params clockParams;
        Clock_Handle myClock;
        Error_Block eb;
        Error_init(&eb);
        Clock_Params_init(&clockParams);
        clockParams.period = 5;
        clockParams.startFlag = TRUE;
        clockParams.arg = (UArg)0x5555;
        myClock = Clock_create(freqClock, 5, &clockParams, &eb);
        if (myClock == NULL) {
        System_abort("Clock create failed");
        }
}


/*
 *  ======== main ========
 */
int main(void)
{
    /* Call board init functions */

    //GPIO_init();
    Board_initGPIO();
    GPIODirModeSet(gpioBaseAddr, gpio, 0);

    //Inicializando os pinos como saída
    GPIODirModeSet(gpioBaseAddr, 21, 0);
    GPIODirModeSet(gpioBaseAddr, 22, 0);
    GPIODirModeSet(gpioBaseAddr, 23, 0);
    GPIODirModeSet(gpioBaseAddr, 24, 0);

    //taskInt();
    //HwInt();
    //ClockInt();
    taskSemaph();


#if defined(idkAM574x) || defined(idkAM572x) || defined(idkAM571x)
    AppGPIOInit();
#endif

    /* Start BIOS */
    BIOS_start();


    while(1);

    return (0);
}
#endif

/*
 *  ======== AppDelay ========
 */
void AppDelay(unsigned int delayVal)
{
    while(delayVal)
    {
        delayVal--;
    }
}

/*
 *  ======== Callback function ========
 */
void AppGpioCallbackFxn(void)
{
    /* Toggle LED1 */
    GPIO_toggle(USER_LED0);
    AppDelay(DELAY_VALUE);
    gpio_intr_triggered = 1;
}
