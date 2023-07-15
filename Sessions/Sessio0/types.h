#define _TYPES_H_
//#ifndef _TYPES_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct {
  int id;
  char date[9];
} Header;

typedef struct {
  int tipo;
  int gravedad;
  char *mensaje;
  char *proceso;
  char time[8];
} Log;
