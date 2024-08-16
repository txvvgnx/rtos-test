#ifndef __LSM6DSO_H
#define __LSM6DSO_H

#include <string.h>
#include <stdio.h>
#include "spi.h"
#include "main.h"
#include "utils.h"
#include "lsm6dsox_reg.h"

void lsm6dsox_read_data_drdy_handler(void);
void lsm6dsox_read_data_drdy_init(void);

#endif