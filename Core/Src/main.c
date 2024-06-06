/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Serial.h"
#include "OLED.h"
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

SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
struct oled_sd_list ls_oled[10];
int sd_dir_deep = -1;
bool allowButton = false;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void nuevoDirectorioSD(const TCHAR *path);
int getListOfSDfiles(FILINFO *fno_f , const TCHAR *path );
int sdcard_getDirectoryItems(FILINFO *fno_file, const TCHAR *path);
void selectionOfItem(  struct oled_sd_list *ls );
void returnToPreviousPage( struct oled_sd_list *ls );
void riseDirectorySD();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


int sdcard_getDirectoryItems(FILINFO *fno_file, const TCHAR *path)
{
  FRESULT res;
  DIR dir;
  FILINFO fno;

  uint8_t count_filesfolders = 0;
  int err;
  res = f_opendir(&dir, path); /* Open the directory */
  if (res == FR_OK)
  {
    for (;;)
    {
      strcpy( fno.fname  , "\0\0\0\0\0\0\0\0\0\0\0\0"   );
      res = f_readdir(&dir, &fno ); /* Read a directory item */
      if (res != FR_OK || fno.fname[0] == 0)
      {
        err = 2;
        break; 
      }
      fno_file[count_filesfolders].fattrib = fno.fattrib;
      fno_file[count_filesfolders].fdate = fno.fdate;
      strcpy( fno_file[count_filesfolders].fname, "\0\0\0\0\0\0\0\0\0\0\0\0"  );
      strcpy( fno_file[count_filesfolders].fname,fno.fname  );
      //fno_file[count_filesfolders].fname = fno.fname;
      fno_file[count_filesfolders].fsize = fno.fsize;
      fno_file[count_filesfolders].ftime = fno.ftime;
      count_filesfolders += 1;
    }
    f_closedir(&dir);
  }
  else
  {
    err = 1;
  }

  return err;
}

int getListOfSDfiles(FILINFO *fno_f , const TCHAR *path )
{
  int countFiles = 0;
  for ( int i = 0; i < 15; i++ )
  {
    strcpy( fno_f[i].fname , "\0\0\0\0\0\0\0\0\0\0\0" );
  }
  int hh = strlen(path);
  char cgg[hh+2];
  sprintf(cgg, "%s", path);
  serialPrint( &huart2, "folder:/%s", cgg);
  
  int err = sdcard_getDirectoryItems( fno_f, cgg);
  if( err == 0 || err == 2)
  {
    for ( int i = 0; i < 15; i++ )
    {
      FILINFO fno = fno_f[i];
      if ( fno.fattrib ==  AM_DIR ||  fno.fattrib ==  AM_ARC  )
      {
        if ( fno.fname[0] == 0 ){
          break;
        }
        if (fno.fattrib & AM_DIR) {           
        	serialPrint( &huart2 ,"   <DIR>   %s\n", fno.fname);
        } else {                               
        	serialPrint( &huart2 ,"%10u %s\n", fno.fsize, fno.fname);
        }
        countFiles++;
      }
      
    }
    
  }
  else{
    serialPrint( &huart2, "error ocurred reading items on sd card (err:%hu )", err );
  }
  return countFiles;
}

void nuevoDirectorioSD(const TCHAR *path)
{
  char new_path[30];
  strcpy( new_path , "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0" );
  if ( sd_dir_deep > 0 )
  {
    strcpy( new_path , ls_oled[sd_dir_deep].dir  );
    strcat(new_path, "/" );
  }
  
  strcat(new_path, path );
  
  FILINFO fno_f[15];
  uint8_t countFiles = 0;
  countFiles = getListOfSDfiles(  fno_f , new_path  );

  sd_dir_deep += 1;
  oledManagerSDScreen_resetList( &ls_oled[sd_dir_deep] , new_path, countFiles, fno_f);
  oledManagerSDScreen( &ls_oled[sd_dir_deep] );
}

void selectionOfItem(  struct oled_sd_list *ls )
{
  if ( ls->filsf[  ls->actual_item ].fattrib == AM_DIR )
  { 
    char path[13];
    strcpy( path, ls->filsf[  ls->actual_item  ].fname );
    serialPrint(  &huart2,"Folder:/%s\r\n" , path  );
    char ar[13];
    strcpy(ar, ls->filsf[  ls->actual_item ].fname);
    nuevoDirectorioSD( ar );
  }
  else if ( ls->filsf[  ls->actual_item ].fattrib == AM_ARC)
  {
    oledInfoFileScreen( ls);
  }
}


void riseDirectorySD()
{
  for (int j = 0; j < 50; j++  )
  {
    ls_oled[sd_dir_deep].dir[j] = 0;
  }
  ls_oled[sd_dir_deep].actual_item = 0;
  strcpy(ls_oled[sd_dir_deep].dir ,  ""); 
  ls_oled[sd_dir_deep].limitUp = 3;
  ls_oled[sd_dir_deep].limitDown = 0;
  uint8_t nosdfile = 0;
  for ( int i = 0; i < ls_oled[sd_dir_deep].totalFiles; i++ )
  {
    ls_oled[sd_dir_deep].filsf[i - nosdfile ].fattrib = 0;
    ls_oled[sd_dir_deep].filsf[i - nosdfile ].fdate = 0;
    strcpy( ls_oled[sd_dir_deep].filsf[i - nosdfile ].fname, "" );
    ls_oled[sd_dir_deep].filsf[i - nosdfile ].fsize = 0;
    ls_oled[sd_dir_deep].filsf[i - nosdfile ].ftime = 0;
  }
  ls_oled[sd_dir_deep].totalFiles = 0;

  sd_dir_deep -= 1;
  
  oledManagerSDScreen( &ls_oled[sd_dir_deep] );

}

void returnToPreviousPage( struct oled_sd_list *ls )
{
  if ( ls->filsf[  ls->actual_item ].fattrib == AM_ARC && ls->modeScr == MODE_FILE )
  {
    oledManagerSDScreen( ls );
  }
  else if ( ls->modeScr == MODE_DIR && sd_dir_deep > 0 )
  {
    riseDirectorySD( );
  }
}

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
  MX_SPI2_Init();
  MX_USART2_UART_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */

  oledInit();
  HAL_Delay(250);
  oledIntroScreen();
  HAL_Delay(2000);
  
  FATFS FatFs;

  //some variables for FatFs
  FRESULT fres; //Result after operations
  //Open the file system
  fres = f_mount(&FatFs, "", 1); //1=mount now

  if (  fres != FR_OK )
  {
    oledErrorSDScreen();
    while ( fres != FR_OK  ){
      fres = f_mount(&FatFs, "", 1); //1=mount now
    }
    oledIntroScreen();
    HAL_Delay(1000);
  }
  
  char ar[2] = {""}; 
  nuevoDirectorioSD(ar);
  allowButton = true;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    fres = f_mount(&FatFs, "", 1);
    if (  fres != FR_OK  )
    {
      //__disable_irq();
      allowButton = false;
      oledErrorSDScreen();
      
      while ( fres != FR_OK ){
        HAL_Delay(500);
        fres = f_mount(&FatFs, "", 1);
      }
      for ( int j = sd_dir_deep; j >= 0 ; j-- )
      {
        ls_oled[j].actual_item = 0;
        ls_oled[j].limitDown = 0;
        ls_oled[j].limitUp = 3;
        ls_oled[j].modeScr = 0;
        ls_oled[j].totalFiles = 0;
        for ( int i = 1; i < 15; i++ )
        {
          ls_oled[j].filsf[i ].fattrib = 0;
          ls_oled[j].filsf[i ].fdate =0;
          strcpy( ls_oled[j].filsf[i ].fname, "" );
          //fno_file[count_filesfolders].fname = fno.fname;
          ls_oled[j].filsf[i ].fsize = 0;
          ls_oled[j].filsf[i ].ftime =0;
        }
      }
      sd_dir_deep = -1;
      char ar[2] = {""}; 
      nuevoDirectorioSD(ar);
      allowButton = true;
      //__enable_irq();
    }
    HAL_Delay(50);
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

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
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : UP_BTN_Pin DOWN_BTN_Pin LEFT_BTN_Pin RIGHT_BTN_Pin */
  GPIO_InitStruct.Pin = UP_BTN_Pin|DOWN_BTN_Pin|LEFT_BTN_Pin|RIGHT_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : SD_CS_Pin */
  GPIO_InitStruct.Pin = SD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SD_CS_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if( !allowButton ) return;
  if( GPIO_Pin == UP_BTN_Pin)
  {
    if ( oledGetActualScreen() == 4 ) return;
    allowButton = false;
    oledManagerSDScreen_changeItem( &ls_oled[sd_dir_deep], UP_ROW );
    serialPrint(&huart2 , "opt:%s\r\n", ls_oled[sd_dir_deep].filsf[ ls_oled[sd_dir_deep].actual_item  ].fname );
    allowButton = true;
  }
  else if( GPIO_Pin == DOWN_BTN_Pin)
  {
    if ( oledGetActualScreen() == 4 ) return;
    allowButton = false;
    oledManagerSDScreen_changeItem( &ls_oled[sd_dir_deep], DOWN_ROW );
    serialPrint(&huart2 , "opt:%s\r\n", ls_oled[sd_dir_deep].filsf[ ls_oled[sd_dir_deep].actual_item  ].fname );
    allowButton = true;
  }
  else if( GPIO_Pin == LEFT_BTN_Pin)
  {
    allowButton = false;
    returnToPreviousPage( &ls_oled[sd_dir_deep] );
    allowButton = true;
  }
  else if( GPIO_Pin == RIGHT_BTN_Pin)
  {
    allowButton = false;
    selectionOfItem( &ls_oled[sd_dir_deep]);
    allowButton = true;
  }/**/
  
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
