#ifndef __OLED_H__
#define __OLED_H__

// includes
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h> //for va_list var arg functions

#include "ssd1306.h"
#include "ssd1306_tests.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

#include "fatfs.h"



// Choose a microcontroller family
//#define STM32F0
//#define STM32F1
#define STM32F4
//#define STM32L0
//#define STM32L1
//#define STM32L4
//#define STM32F3
//#define STM32H7
//#define STM32F7
//#define STM32G0


#if defined(STM32WB)
#include "stm32wbxx_hal.h"
#elif defined(STM32F0)
#include "stm32f0xx_hal.h"
#elif defined(STM32F1)
#include "stm32f1xx_hal.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#elif defined(STM32L0)
#include "stm32l0xx_hal.h"
#elif defined(STM32L1)
#include "stm32l1xx_hal.h"
#elif defined(STM32L4)
#include "stm32l4xx_hal.h"
#elif defined(STM32L5)
#include "stm32l5xx_hal.h"
#elif defined(STM32F3)
#include "stm32f3xx_hal.h"
#elif defined(STM32H7)
#include "stm32h7xx_hal.h"
#elif defined(STM32F7)
#include "stm32f7xx_hal.h"
#elif defined(STM32G0)
#include "stm32g0xx_hal.h"
#elif defined(STM32G4)
#include "stm32g4xx_hal.h"
#else
#error "Board not recognized"
#endif

#define UP_ROW 0
#define DOWN_ROW 1

#define MODE_DIR 0
#define MODE_FILE 1

struct oled_data {
  uint8_t number_screens;
  uint8_t actual_screen;
};

struct oled_sd_list {
  char dir[50];
  FILINFO filsf[15];
  uint8_t actual_item;
  uint8_t limitUp;
  uint8_t limitDown;
  uint8_t totalFiles;
  uint8_t modeScr;
};

void oledTestAll();
void oledInit();
void oledChangeScreen( struct oled_data *oled_sc, struct oled_sd_list *ls );
/************* Screens of the system *********/
void oledIntroScreen();

void oledErrorSDScreen();

void oledManagerSDScreen(struct oled_sd_list *ls);
void oledManagerSDScreen_resetList( struct oled_sd_list *ls ,  const char *path, uint8_t countFiles, FILINFO *fno_f);
void oledManagerSDScreen_changeItem( struct oled_sd_list *ls, uint8_t row );

void oledInfoFileScreen(struct oled_sd_list *ls );

int oledGetActualScreen();

#endif