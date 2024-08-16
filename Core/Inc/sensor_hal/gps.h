/*
 * gps.h
 *
 * Driver by: https://github.com/leech001/gps/
 */

#include <stdio.h>
#include <string.h>
#include "usart.h"

#define GPS_DEBUG	0
#define	GPS_USART	&huart2
#define GPSBUFSIZE  128       // GPS buffer size

typedef struct {
  // calculated values
  float dec_longitude;
  float dec_latitude;
  float altitude_ft;

  // GGA - Global Positioning System Fixed Data
  float nmea_longitude;
  float nmea_latitude;
  float utc_time;
  char ns, ew;
  int lock;
  int satelites;
  float hdop;
  float msl_altitude;
  char msl_units;

  // RMC - Recommended Minimum Specific GNS Data
  char rmc_status;
  float speed_k;
  float course_d;
  int date;

  // GLL
  char gll_status;

  // VTG - Course over ground, ground speed
  float course_t; // ground speed true
  char course_t_unit;
  float course_m; // magnetic
  char course_m_unit;
  char speed_k_unit;
  float speed_km; // speed km/hr
  char speed_km_unit;
} GPS_t;

#if (GPS_DEBUG == 1)
void GPS_print(char *data);
#endif

void GPS_Init();
void GPS_UART_CallBack();
int GPS_validate(char *nmeastr);
void GPS_parse(char *GPSstrParse);
float GPS_nmea_to_dec(float deg_coord, char nsew);
float GPS_meter_to_feet(float height);