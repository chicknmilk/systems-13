#ifndef BOROUGHS_H
#define BOROUGHS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

struct pop_entry {
  int year;
  int population;
  char boro[15];
};

void read_csv();
void read_data();
void add_data();
void update_data();


#endif