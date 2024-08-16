#ifndef __UTILS_H
#define __UTILS_H

#include "usb_device.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

extern uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);

void print_console(const char *fmt, ...);

#endif