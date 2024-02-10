/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sht40x_driver_basic.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
void serial_print(const char *pString, uint8_t u8Length);
uint8_t i2c_write(uint8_t addr, uint8_t *buf, uint8_t len);
uint8_t i2c_read(uint8_t addr, uint8_t *buf, uint8_t len);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
sht40x_info_t sht40xInfo;
sht40x_data_t dataRead;

int err;
uint32_t UID;
uint8_t variant;
uint8_t deviceAdd;
uint8_t NumberSamples = 10;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
  HAL_Delay(500);

	sht40x_basic_initialize(SHT40_AD1B_VARIANT);        /**< initialize device variant */
	sht40x_info(&sht40xInfo);

	sht40x_interface_debug_print("Chip Name: \t%s\r\n", sht40xInfo.chip_name);
	sht40x_interface_debug_print("Manufacturer: \t%s\r\n",sht40xInfo.manufacturer_name);
	sht40x_interface_debug_print("Interface Protocol: \t%s\r\n", sht40xInfo.interface);
	sht40x_interface_debug_print("Supply Volt Max: \t%.1f V\r\n",sht40xInfo.supply_voltage_max_v);
	sht40x_interface_debug_print("Supply Volt Min: \t%.1f V\r\n",sht40xInfo.supply_voltage_min_v);
	sht40x_interface_debug_print("Maximum Current: \t%.1f uA\r\n",sht40xInfo.max_current_ma);
	sht40x_interface_debug_print("Max Temperature: \t%.1f C\r\n",sht40xInfo.temperature_max);
	sht40x_interface_debug_print("Diver Version: \t\tV%.1f.%.2d\r\n",(sht40xInfo.driver_version /1000), (uint8_t)(sht40xInfo.driver_version - (uint8_t)(sht40xInfo.driver_version / 100)*100));
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);
		sht40x_interface_delay_ms(3000);

		err =  sht40x_basic_get_temp_rh(SHT40X_PRECISION_HIGH, &dataRead);                               /**< Take temperature and humidity measurement */
		sht40x_interface_debug_print("\nTemp C: %.2f\n", dataRead.temperature_C);
		sht40x_interface_debug_print("Temp F: %.2f\n", dataRead.temperature_F);
		sht40x_interface_debug_print("Humidity: %.2f\n", dataRead.humidity);

		for(int index = 0; index < RESPONSE_LENGTH; index++){
			sht40x_interface_debug_print("raw data: 0x%.2x\n", dataRead.rawData[index]);
		}

		err = sht40x_basic_get_serial_number( (uint32_t*)&UID );                                         /**< Read sensor unique ID (Serial number) */
		sht40x_interface_debug_print("\nserial number : %lu\n", UID);


//        err = sht40x_basic_get_temp_humidity_nSample(SHT40X_PRECISION_HIGH, &dataRead, NumberSamples); /**< Measure Temp and humidity with n number of samples */
//        sht40x_interface_debug_print("\nTemp C sampled: %.2f\n", dataRead.temperature_C);
//        sht40x_interface_debug_print("Humidity sampled: %.2f\n", dataRead.humidity);
//
//        err = sht40x_basic_activate_heater(SHT40X_HEATER_POWER_200mW_100mS, &dataRead);                 /**< Activate heater and measure temperature */
//        sht40x_interface_debug_print("\nHeater Temp C: %.2f\n", dataRead.temperature_C);
//        sht40x_interface_debug_print("Heater Temp F: %.2f\n", dataRead.temperature_F);
//        sht40x_interface_debug_print("Heater Humidity: %.2f\n", dataRead.humidity);
//
//        sht40x_basic_get_variant((uint8_t *) & variant);
//        sht40x_interface_debug_print("\nDevice variant: %d\n", variant);
//        sht40x_basic_get_addr((uint8_t *) & deviceAdd);
//        sht40x_interface_debug_print("\nDevice Address: %x\n", deviceAdd);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00303D5B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : RED_LED_Pin */
  GPIO_InitStruct.Pin = RED_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RED_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BLUE_LED_Pin */
  GPIO_InitStruct.Pin = BLUE_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BLUE_LED_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/**
 * @brief transmit serial data via usb com port
 * @param[in] pTxBuffer point to data to sent
 * @param[in] length is the data size
 * @return
 * @note		none
 * */
void serial_print(const char *pString, uint8_t u8Length)
{
	HAL_UART_Transmit(&huart2, (const uint8_t *) pString, u8Length, HAL_MAX_DELAY);
}

/**
 * @brief i2c data transmit
 * @param[in] addr is the slave address
 * @param[in] reg the register to write
 * @param[in] buf the data to be writen
 * @param[in] len size of data
 * @returb  status code
 * 			- 0 sucess
 * 			- 1 failed to write
 * @note	none
 * */
uint8_t i2c_write(uint8_t addr, uint8_t *buf, uint8_t len)
{
	return HAL_I2C_Master_Transmit(&hi2c1, (addr << 1), (uint8_t *)buf, len, 1000);
}

/**
 * @brief i2c data Read
 * @param[in] addr is the slave address
 * @param[in] reg the register to read
 * @param[out] buf point to data to read
 * @param[in] len size of data
 * @returb  status code
 * 			- 0 sucess
 * 			- 1 failed to read
 * @note	none
 * */

uint8_t i2c_read(uint8_t addr, uint8_t *buf, uint8_t len)
{
    return HAL_I2C_Master_Receive(&hi2c1, (addr << 1), (uint8_t *)buf, len, 1000);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
