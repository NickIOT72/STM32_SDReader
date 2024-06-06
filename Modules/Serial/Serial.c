#include "Serial.h"

void serialPrint(UART_HandleTypeDef *huart ,const char *fmt, ...)
{
  static char buffer[256];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);
  int len = strlen(buffer);
  HAL_UART_Transmit(huart, (uint8_t*)buffer, len, -1);
}