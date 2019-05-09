/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TSB8_Pin GPIO_PIN_2
#define TSB8_GPIO_Port GPIOE
#define MOTOR_LR_A_Pin GPIO_PIN_3
#define MOTOR_LR_A_GPIO_Port GPIOE
#define MOTOR_LR_A_EXTI_IRQn EXTI3_IRQn
#define MOTOR_LR_B_Pin GPIO_PIN_4
#define MOTOR_LR_B_GPIO_Port GPIOE
#define MOTOR_LR_B_EXTI_IRQn EXTI4_IRQn
#define MOTOR_RR_A_Pin GPIO_PIN_5
#define MOTOR_RR_A_GPIO_Port GPIOE
#define MOTOR_RR_A_EXTI_IRQn EXTI9_5_IRQn
#define MOTOR_RR_B_Pin GPIO_PIN_6
#define MOTOR_RR_B_GPIO_Port GPIOE
#define MOTOR_RR_B_EXTI_IRQn EXTI9_5_IRQn
#define MOTOR_LF_A_Pin GPIO_PIN_13
#define MOTOR_LF_A_GPIO_Port GPIOC
#define MOTOR_LF_A_EXTI_IRQn EXTI15_10_IRQn
#define MOTOR_LF_B_Pin GPIO_PIN_14
#define MOTOR_LF_B_GPIO_Port GPIOC
#define MOTOR_LF_B_EXTI_IRQn EXTI15_10_IRQn
#define TSC1_Pin GPIO_PIN_0
#define TSC1_GPIO_Port GPIOF
#define TSD1_Pin GPIO_PIN_1
#define TSD1_GPIO_Port GPIOF
#define TSC2_Pin GPIO_PIN_2
#define TSC2_GPIO_Port GPIOF
#define TSD2_Pin GPIO_PIN_3
#define TSD2_GPIO_Port GPIOF
#define TSC3_Pin GPIO_PIN_4
#define TSC3_GPIO_Port GPIOF
#define TSD3_Pin GPIO_PIN_5
#define TSD3_GPIO_Port GPIOF
#define TSC4_Pin GPIO_PIN_6
#define TSC4_GPIO_Port GPIOF
#define TSD4_Pin GPIO_PIN_7
#define TSD4_GPIO_Port GPIOF
#define LCD_DISA_Pin GPIO_PIN_8
#define LCD_DISA_GPIO_Port GPIOF
#define LCD_DISB_Pin GPIO_PIN_9
#define LCD_DISB_GPIO_Port GPIOF
#define LCD_DISC_Pin GPIO_PIN_10
#define LCD_DISC_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOC
#define LCD_DIS22_Pin GPIO_PIN_2
#define LCD_DIS22_GPIO_Port GPIOC
#define LCD_DISD_Pin GPIO_PIN_3
#define LCD_DISD_GPIO_Port GPIOC
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOA
#define MOTOR_LF2_Pin GPIO_PIN_1
#define MOTOR_LF2_GPIO_Port GPIOA
#define MOTOR_RF1_Pin GPIO_PIN_2
#define MOTOR_RF1_GPIO_Port GPIOA
#define MOTOR_RF2_Pin GPIO_PIN_3
#define MOTOR_RF2_GPIO_Port GPIOA
#define MOTOR_LF1_Pin GPIO_PIN_5
#define MOTOR_LF1_GPIO_Port GPIOA
#define MOTOR_LR1_Pin GPIO_PIN_6
#define MOTOR_LR1_GPIO_Port GPIOA
#define MOTOR_LR2_Pin GPIO_PIN_7
#define MOTOR_LR2_GPIO_Port GPIOA
#define LCD_DIS5_Pin GPIO_PIN_5
#define LCD_DIS5_GPIO_Port GPIOC
#define LCD_DIS23_Pin GPIO_PIN_0
#define LCD_DIS23_GPIO_Port GPIOB
#define LCD_DISF_Pin GPIO_PIN_1
#define LCD_DISF_GPIO_Port GPIOB
#define LCD_DISE_Pin GPIO_PIN_2
#define LCD_DISE_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_11
#define KEY2_GPIO_Port GPIOF
#define LCD_DIS2_Pin GPIO_PIN_0
#define LCD_DIS2_GPIO_Port GPIOG
#define LCD_DIS10_Pin GPIO_PIN_7
#define LCD_DIS10_GPIO_Port GPIOE
#define LCD_DIS11_Pin GPIO_PIN_8
#define LCD_DIS11_GPIO_Port GPIOE
#define LCD_DIS12_Pin GPIO_PIN_9
#define LCD_DIS12_GPIO_Port GPIOE
#define LCD_DIS13_Pin GPIO_PIN_10
#define LCD_DIS13_GPIO_Port GPIOE
#define LCD_DIS14_Pin GPIO_PIN_11
#define LCD_DIS14_GPIO_Port GPIOE
#define LCD_DIS15_Pin GPIO_PIN_12
#define LCD_DIS15_GPIO_Port GPIOE
#define LCD_DIS16_Pin GPIO_PIN_13
#define LCD_DIS16_GPIO_Port GPIOE
#define LCD_DIS17_Pin GPIO_PIN_14
#define LCD_DIS17_GPIO_Port GPIOE
#define LCD_DIS18_Pin GPIO_PIN_15
#define LCD_DIS18_GPIO_Port GPIOE
#define LCD_DIS19_Pin GPIO_PIN_8
#define LCD_DIS19_GPIO_Port GPIOD
#define LCD_DIS20_Pin GPIO_PIN_9
#define LCD_DIS20_GPIO_Port GPIOD
#define LCD_DIS21_Pin GPIO_PIN_10
#define LCD_DIS21_GPIO_Port GPIOD
#define TSA1_Pin GPIO_PIN_12
#define TSA1_GPIO_Port GPIOD
#define TSA2_Pin GPIO_PIN_13
#define TSA2_GPIO_Port GPIOD
#define LCD_DIS6_Pin GPIO_PIN_14
#define LCD_DIS6_GPIO_Port GPIOD
#define LCD_DIS7_Pin GPIO_PIN_15
#define LCD_DIS7_GPIO_Port GPIOD
#define TSA3_Pin GPIO_PIN_2
#define TSA3_GPIO_Port GPIOG
#define TSA4_Pin GPIO_PIN_3
#define TSA4_GPIO_Port GPIOG
#define TSA5_Pin GPIO_PIN_4
#define TSA5_GPIO_Port GPIOG
#define TSA6_Pin GPIO_PIN_5
#define TSA6_GPIO_Port GPIOG
#define TSA7_Pin GPIO_PIN_6
#define TSA7_GPIO_Port GPIOG
#define TSA8_Pin GPIO_PIN_7
#define TSA8_GPIO_Port GPIOG
#define MOTOR_RR1_Pin GPIO_PIN_8
#define MOTOR_RR1_GPIO_Port GPIOC
#define MOTOR_RR2_Pin GPIO_PIN_9
#define MOTOR_RR2_GPIO_Port GPIOC
#define TSE1_Pin GPIO_PIN_8
#define TSE1_GPIO_Port GPIOA
#define TSE2_Pin GPIO_PIN_11
#define TSE2_GPIO_Port GPIOA
#define TSE3_Pin GPIO_PIN_12
#define TSE3_GPIO_Port GPIOA
#define TSE4_Pin GPIO_PIN_13
#define TSE4_GPIO_Port GPIOA
#define MOTOR_RF_A_Pin GPIO_PIN_10
#define MOTOR_RF_A_GPIO_Port GPIOC
#define MOTOR_RF_A_EXTI_IRQn EXTI15_10_IRQn
#define MOTOR_RF_B_Pin GPIO_PIN_11
#define MOTOR_RF_B_GPIO_Port GPIOC
#define MOTOR_RF_B_EXTI_IRQn EXTI15_10_IRQn
#define LCD_DIS8_Pin GPIO_PIN_0
#define LCD_DIS8_GPIO_Port GPIOD
#define LCD_DIS9_Pin GPIO_PIN_1
#define LCD_DIS9_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_3
#define LED2_GPIO_Port GPIOD
#define LCD_DIS4_Pin GPIO_PIN_4
#define LCD_DIS4_GPIO_Port GPIOD
#define LCD_DIS3_Pin GPIO_PIN_5
#define LCD_DIS3_GPIO_Port GPIOD
#define TSB1_Pin GPIO_PIN_6
#define TSB1_GPIO_Port GPIOD
#define TSB2_Pin GPIO_PIN_7
#define TSB2_GPIO_Port GPIOD
#define TSE7_Pin GPIO_PIN_9
#define TSE7_GPIO_Port GPIOG
#define TSE8_Pin GPIO_PIN_10
#define TSE8_GPIO_Port GPIOG
#define LCD_DIS1_Pin GPIO_PIN_12
#define LCD_DIS1_GPIO_Port GPIOG
#define TSB3_Pin GPIO_PIN_3
#define TSB3_GPIO_Port GPIOB
#define TSB4_Pin GPIO_PIN_4
#define TSB4_GPIO_Port GPIOB
#define TSB5_Pin GPIO_PIN_5
#define TSB5_GPIO_Port GPIOB
#define TSE5_Pin GPIO_PIN_6
#define TSE5_GPIO_Port GPIOB
#define TSE6_Pin GPIO_PIN_7
#define TSE6_GPIO_Port GPIOB
#define IIC_SCL_Pin GPIO_PIN_8
#define IIC_SCL_GPIO_Port GPIOB
#define IIC_SDA_Pin GPIO_PIN_9
#define IIC_SDA_GPIO_Port GPIOB
#define TSB6_Pin GPIO_PIN_0
#define TSB6_GPIO_Port GPIOE
#define TSB7_Pin GPIO_PIN_1
#define TSB7_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
