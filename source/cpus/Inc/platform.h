/**
 ******************************************************************************
 * @file    platform.h 
 * @author  MMY Application Team
 * @brief   Platform header file. Defining platform independent functionality. 
 *  
 *  This should contain all platform and hardware specifics such as 
 *  GPIO assignment, system resources, locks, IRQs, etc
 *  
 *  Each distinct platform/system/board must provide this definitions 
 *  for all SW layers to use
 ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#ifdef STM32G070xx
//#include "stm32G0xx_ll.h"
#else 
#include "stm32f4xx_hal.h"
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "st_errno.h"
#include "timer.h"
#include "main.h"
#include "logger.h"
#include "demo_app.h"


/** @addtogroup X-CUBE-NFC6_Applications
 *  @{
 */

/** @addtogroup PollingTagDetect
 *  @{
 */

/** @defgroup PTD_Platform
 *  @brief Demo functions containing the example code
 * @{
 */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup PTD_Platform_Exported_Constants
 *  @{
 */
#define ST25R_SS_PIN             ST25R_SPI_SS_Pin    /*!< GPIO pin used for ST25R SPI SS                */
#define ST25R_SS_PORT            ST25R_SPI_SS_GPIO_Port   /*!< GPIO port used for ST25R SPI SS port          */

#ifndef RFAL_USE_I2C
#define ST25R_INT_PIN            ST25R_SPI_INT_Pin    /*!< GPIO pin used for ST25R IRQ                   */
#define ST25R_INT_PORT           ST25R_SPI_INT_GPIO_Port   /*!< GPIO port used for ST25R IRQ port             */
#else
#define ST25R_INT_PIN            BUS_I2C1_IRQ_GPIO_PIN    /*!< GPIO pin used for ST25R IRQ                   */
#define ST25R_INT_PORT           BUS_I2C1_IRQ_GPIO_PORT   /*!< GPIO port used for ST25R IRQ port             */
#endif /* RFAL_USE_I2C */
#define IRQ_ST25R_EXTI_IRQn      ST25R_SPI_INT_EXTI_IRQn

#ifdef LED_FIELD_Pin
#ifdef ST25R3916
#define PLATFORM_LED_FIELD_PIN       NFC06A1_LED6_PIN         /*!< GPIO pin used as field LED                        */
#endif /* ST25R3916 */
#ifdef ST25R3916B
#define PLATFORM_LED_FIELD_PIN       NFC08A1_LED6_PIN         /*!< GPIO pin used as field LED                        */
#endif /* ST25R3916B */
#endif

#ifdef LED_FIELD_GPIO_Port
#ifdef ST25R3916
#define PLATFORM_LED_FIELD_PORT      NFC06A1_LED6_PIN_PORT    /*!< GPIO port used as field LED                       */
#endif /* ST25R3916 */
#ifdef ST25R3916B
#define PLATFORM_LED_FIELD_PORT      NFC08A1_LED6_PIN_PORT    /*!< GPIO port used as field LED                       */
#endif /* ST25R3916B */
#endif

#ifdef ST25R3916
#define PLATFORM_LED_A_PIN           NFC06A1_LED3_PIN         /*!< GPIO pin used for LED A    */
#define PLATFORM_LED_A_PORT          NFC06A1_LED3_PIN_PORT    /*!< GPIO port used for LED A   */
#define PLATFORM_LED_B_PIN           NFC06A1_LED2_PIN         /*!< GPIO pin used for LED B    */
#define PLATFORM_LED_B_PORT          NFC06A1_LED2_PIN_PORT    /*!< GPIO port used for LED B   */
#define PLATFORM_LED_F_PIN           NFC06A1_LED1_PIN         /*!< GPIO pin used for LED F    */
#define PLATFORM_LED_F_PORT          NFC06A1_LED1_PIN_PORT    /*!< GPIO port used for LED F   */
#define PLATFORM_LED_V_PIN           NFC06A1_LED4_PIN         /*!< GPIO pin used for LED V    */
#define PLATFORM_LED_V_PORT          NFC06A1_LED4_PIN_PORT    /*!< GPIO port used for LED V   */
#define PLATFORM_LED_AP2P_PIN        NFC06A1_LED5_PIN         /*!< GPIO pin used for LED AP2P */
#define PLATFORM_LED_AP2P_PORT       NFC06A1_LED5_PIN_PORT    /*!< GPIO port used for LED AP2P*/
#endif /* ST25R3916 */
#ifdef ST25R3916B
#define PLATFORM_LED_A_PIN           NFC08A1_LED3_PIN         /*!< GPIO pin used for LED A    */
#define PLATFORM_LED_A_PORT          NFC08A1_LED3_PIN_PORT    /*!< GPIO port used for LED A   */
#define PLATFORM_LED_B_PIN           NFC08A1_LED2_PIN         /*!< GPIO pin used for LED B    */
#define PLATFORM_LED_B_PORT          NFC08A1_LED2_PIN_PORT    /*!< GPIO port used for LED B   */
#define PLATFORM_LED_F_PIN           NFC08A1_LED1_PIN         /*!< GPIO pin used for LED F    */
#define PLATFORM_LED_F_PORT          NFC08A1_LED1_PIN_PORT    /*!< GPIO port used for LED F   */
#define PLATFORM_LED_V_PIN           NFC08A1_LED4_PIN         /*!< GPIO pin used for LED V    */
#define PLATFORM_LED_V_PORT          NFC08A1_LED4_PIN_PORT    /*!< GPIO port used for LED V   */
#define PLATFORM_LED_AP2P_PIN        NFC08A1_LED5_PIN         /*!< GPIO pin used for LED AP2P */
#define PLATFORM_LED_AP2P_PORT       NFC08A1_LED5_PIN_PORT    /*!< GPIO port used for LED AP2P*/
#endif /* ST25R3916B */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PTD_Platform_Exported_Macro
 *  @{
 */
#define platformProtectST25RComm()                do{ globalCommProtectCnt++;                  \
                                                          __DSB();NVIC_DisableIRQ(IRQ_ST25R_EXTI_IRQn); \
                                                          __DSB();                             \
                                                          __ISB();                             \
                                                        }while(0)                                   /*!< Protect unique access to ST25R communication channel - IRQ disable on single thread environment (MCU) ; Mutex lock on a multi thread environment      */
#define platformUnprotectST25RComm()              do{ globalCommProtectCnt--;             \
                                                          if (globalCommProtectCnt == 0U) \
                                                          {                               \
                                                            NVIC_EnableIRQ(IRQ_ST25R_EXTI_IRQn);   \
                                                          }                               \
                                                        }while(0)                                   /*!< Unprotect unique access to ST25R communication channel - IRQ enable on a single thread environment (MCU) ; Mutex unlock on a multi thread environment */

#define platformProtectST25RIrqStatus()           platformProtectST25RComm()                /*!< Protect unique access to IRQ status var - IRQ disable on single thread environment (MCU) ; Mutex lock on a multi thread environment */
#define platformUnprotectST25RIrqStatus()         platformUnprotectST25RComm()              /*!< Unprotect the IRQ status var - IRQ enable on a single thread environment (MCU) ; Mutex unlock on a multi thread environment         */

#define platformProtectWorker()                                                                     /* Protect RFAL Worker/Task/Process from concurrent execution on multi thread platforms   */
#define platformUnprotectWorker()                                                                   /* Unprotect RFAL Worker/Task/Process from concurrent execution on multi thread platforms */

#define platformIrqST25RSetCallback( cb )
#define platformIrqST25RPinInitialize()

#define platformLedsInitialize()                                                                    /*!< Initializes the pins used as LEDs to outputs*/

#define platformLedOff( port, pin )                   platformGpioClear(port, pin)                  /*!< Turns the given LED Off                     */
#define platformLedOn( port, pin )                    platformGpioSet(port, pin)                    /*!< Turns the given LED On                      */
#define platformLedToogle( port, pin )                platformGpioToogle(port, pin)                 /*!< Toogle the given LED                        */

#define platformGpioSet( port, pin )                  LL_GPIO_SetOutputPin(port, pin)               /*!< Turns the given GPIO High                   */
#define platformGpioClear( port, pin )                LL_GPIO_ResetOutputPin(port, pin)             /*!< Turns the given GPIO Low                    */
#define platformGpioToogle( port, pin )               LL_GPIO_TogglePin(port, pin)                  /*!< Toogles the given GPIO                      */
#define platformGpioIsHigh( port, pin )               (LL_GPIO_IsInputPinSet(port, pin))            /*!< Checks if the given LED is High             */
#define platformGpioIsLow( port, pin )                (!LL_GPIO_IsInputPinSet(port, pin))           /*!< Checks if the given LED is Low              */

#define platformTimerCreate( t )                      timerCalculateTimer(t)                        /*!< Create a timer with the given time (ms)     */
#define platformTimerIsExpired( timer )               timerIsExpired(timer)                         /*!< Checks if the given timer is expired        */
#define platformTimerDestroy( timer )                                                               /*!< Stop and release the given timer            */
#define platformDelay( t )                            SystemDelay_ms( t )                                /*!< Performs a delay for the given time (ms)    */

#define platformGetSysTick()                          GetSystemTime_ms()                                 /*!< Get System Tick ( 1 tick = 1 ms)            */

#define platformErrorHandle()                         Error_Handler()             /*!< Global error handler or trap                */

#define platformSpiSelect()                           platformGpioClear(ST25R_SS_PORT, ST25R_SS_PIN)/*!< SPI SS\CS: Chip|Slave Select                */
#define platformSpiDeselect()                         platformGpioSet(ST25R_SS_PORT, ST25R_SS_PIN)  /*!< SPI SS\CS: Chip|Slave Deselect              */
#define platformSpiTxRx( txBuf, rxBuf, len )          BSP_SPI1_SendRecv_LL(txBuf, rxBuf, len)          /*!< SPI transceive                              */


#define platformI2CTx( txBuf, len, last, txOnly )     BSP_I2C1_SequencialSend((uint16_t)0xA0, (uint8_t *)(txBuf), (len), last, txOnly ) /*!< I2C Transmit                                */
#define platformI2CRx( txBuf, len )                   BSP_I2C1_SequencialRecv((uint16_t)0xA0, rxBuf, len )           /*!< I2C Receive                                 */
#define platformI2CStart()                                                                          /*!< I2C Start condition                         */
#define platformI2CStop()                                                                           /*!< I2C Stop condition                          */
#define platformI2CRepeatStart()                                                                    /*!< I2C Repeat Start                            */
#define platformI2CSlaveAddrWR(add)                                                                 /*!< I2C Slave address for Write operation       */
#define platformI2CSlaveAddrRD(add)                                                                 /*!< I2C Slave address for Read operation        */

#define platformLog(...)                              logUsart(__VA_ARGS__)                         /*!< Log  method                                 */


/**
  * @}
  */

/*
******************************************************************************
* GLOBAL VARIABLES
******************************************************************************
*/
extern uint8_t globalCommProtectCnt;                      /* Global Protection Counter provided per platform - instantiated in main.c    */

/*
******************************************************************************
* RFAL FEATURES CONFIGURATION
******************************************************************************
*/

#define RFAL_FEATURE_LISTEN_MODE               false       /*!< Enable/Disable RFAL support for Listen Mode                               */
#define RFAL_FEATURE_WAKEUP_MODE               false       /*!< Enable/Disable RFAL support for the Wake-Up mode                          */
#define RFAL_FEATURE_LOWPOWER_MODE             false      /*!< Enable/Disable RFAL support for the Low Power mode                        */
#define RFAL_FEATURE_NFCA                      true       /*!< Enable/Disable RFAL support for NFC-A (ISO14443A)                         */
#define RFAL_FEATURE_NFCB                      false       /*!< Enable/Disable RFAL support for NFC-B (ISO14443B)                         */
#define RFAL_FEATURE_NFCF                      false       /*!< Enable/Disable RFAL support for NFC-F (FeliCa)                            */
#define RFAL_FEATURE_NFCV                      true       /*!< Enable/Disable RFAL support for NFC-V (ISO15693)                          */
#define RFAL_FEATURE_T1T                       false       /*!< Enable/Disable RFAL support for T1T (Topaz)                               */
#define RFAL_FEATURE_T2T                       false       /*!< Enable/Disable RFAL support for T2T                                       */
#define RFAL_FEATURE_T4T                       false       /*!< Enable/Disable RFAL support for T4T                                       */
#define RFAL_FEATURE_ST25TB                    false       /*!< Enable/Disable RFAL support for ST25TB                                    */
#define RFAL_FEATURE_ST25xV                    false       /*!< Enable/Disable RFAL support for  ST25TV/ST25DV                            */
#define RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG     false      /*!< Enable/Disable Analog Configs to be dynamically updated (RAM)             */
#define RFAL_FEATURE_DPO                       false      /*!< Enable/Disable RFAL Dynamic Power Output support                          */
#define RFAL_FEATURE_ISO_DEP                   false       /*!< Enable/Disable RFAL support for ISO-DEP (ISO14443-4)                      */
#define RFAL_FEATURE_ISO_DEP_POLL              false       /*!< Enable/Disable RFAL support for Poller mode (PCD) ISO-DEP (ISO14443-4)    */
#define RFAL_FEATURE_ISO_DEP_LISTEN            false       /*!< Enable/Disable RFAL support for Listen mode (PICC) ISO-DEP (ISO14443-4)   */
#define RFAL_FEATURE_NFC_DEP                   false       /*!< Enable/Disable RFAL support for NFC-DEP (NFCIP1/P2P)                      */

#define RFAL_FEATURE_ISO_DEP_IBLOCK_MAX_LEN    256U       /*!< ISO-DEP I-Block max length. Please use values as defined by rfalIsoDepFSx */
#define RFAL_FEATURE_NFC_DEP_BLOCK_MAX_LEN     254U       /*!< NFC-DEP Block/Payload length. Allowed values: 64, 128, 192, 254           */
#define RFAL_FEATURE_NFC_RF_BUF_LEN            258U       /*!< RF buffer length used by RFAL NFC layer                                   */

#define RFAL_FEATURE_ISO_DEP_APDU_MAX_LEN      512U       /*!< ISO-DEP APDU max length. Please use multiples of I-Block max length       */
#define RFAL_FEATURE_NFC_DEP_PDU_MAX_LEN       512U       /*!< NFC-DEP PDU max length.                                                   */

/*
******************************************************************************
* RFAL CUSTOM SETTINGS
******************************************************************************
  Custom analog configs are used to cope with Automatic Antenna Tuning (AAT)
  that are optimized differently for each board.
*/
#define RFAL_ANALOG_CONFIG_CUSTOM                         /*!< Use Custom Analog Configs when defined                                    */

/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_H */

