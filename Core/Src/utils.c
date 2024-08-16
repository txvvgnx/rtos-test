#include "utils.h"

void print_console(const char *fmt, ...) {
  static char buffer[256];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  int len = strlen(buffer);
  CDC_Transmit_FS((uint8_t*)buffer, len);
}