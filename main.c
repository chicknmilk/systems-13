#include "boroughs.h"

int main(int argc, char *argv[]) {

  char command[50];
  if (argc == 2) {
    strncpy(command, argv[1], 50);
  } 
  else {
    printf("Usage: ./boroughs <command>\n");
    return 0;
  }

  if (strcmp(command, "-read_csv") == 0) {
    read_csv();
    printf("segfault after entire thing???\n");
  } 
  else if (strcmp(command, "-read_data") == 0) {
    read_data();
  } 
  else if (strcmp(command, "-add_data") == 0) {
    add_data();
  } 
  else if (strcmp(command, "-update_data") == 0) {
    update_data();
  } 
  else {
    printf("Invalid command.\n");
  }


  return 0;
}