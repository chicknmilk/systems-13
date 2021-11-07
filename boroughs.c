#include "boroughs.h"

struct pop_entry * create_pop_entry(int year, int population, char boro[15]) {
    struct pop_entry *new_entry = malloc(sizeof(struct pop_entry));
    new_entry->year = year;
    new_entry->population = population;
    strcpy(new_entry->boro, boro);
    return new_entry;
}

void print_pop_entry (struct pop_entry *entry) {
    printf("%d, %d, %s\n", entry->year, entry->population, entry->boro);
}

void read_csv() {
  // open file for reading
  int fp = open("data.csv", O_RDONLY, 0644);
  int f_out = open("boroughs.data", O_WRONLY | O_CREAT, 0644);

  struct stat f_info;
  stat("data.csv", &f_info);

  char file_data[f_info.st_size];
  read(fp, file_data, f_info.st_size);


  // set pointer variables for reading
  char * current_pos = file_data;
  char * boroughs[5];
  char b1[15], b2[15], b3[15], b4[15], b5[15];
  strcpy(b1, "Manhattan");
  strcpy(b2, "Brooklyn");
  strcpy(b3, "Queens");
  strcpy(b4, "Bronx");
  strcpy(b5, "Staten Island");
  boroughs[0] = b1;
  boroughs[1] = b2;
  boroughs[2] = b3;
  boroughs[3] = b4;
  boroughs[4] = b5;

  // advance pointer to second line
  current_pos = strchr(current_pos, '\n') + 1;

  // read until end of file
  while (current_pos + 1 < file_data + f_info.st_size) {
    int data[6];

    sscanf(current_pos, "%u,%u,%u,%u,%u,%u", data, data + 1, data + 2, data + 3, data + 4, data + 5);

    int i;
    for (i = 1; i < 6; i++) {
      struct pop_entry *new_entry = create_pop_entry(data[0], data[i], boroughs[i - 1]);
      write(f_out, new_entry, sizeof(struct pop_entry));
      print_pop_entry(new_entry);
    }

    // advance pointer to next line
    current_pos = strchr(current_pos, '\n') + 1;
    
  }
}

struct pop_entry * read_data() {
  printf("reading data\n");
  int fp = open("boroughs.data", O_RDONLY, 0644);

  struct stat f_info;
  stat("boroughs.data", &f_info);

  struct pop_entry * pop_arr = malloc(f_info.st_size);

  read(fp, pop_arr, f_info.st_size);

  int i;
  for (i = 0; i < f_info.st_size / sizeof(struct pop_entry); i++) {
    print_pop_entry(pop_arr + i);
  }
}

void add_data() {
  printf("adding data\n");
  struct pop_entry new_entry;
  int year, population;
  char borough[15];

  char data[256];

  printf("enter new data entry (year borough population)\n");

  read(STDIN_FILENO, &data, sizeof(data));
  sscanf(data, "%d %s %d", &new_entry.year, new_entry.boro, &new_entry.population);

  int fp = open("boroughs.data", O_WRONLY | O_APPEND | O_CREAT, 0644);
  lseek(fp, 0, SEEK_END);
  write(fp, &new_entry, sizeof(struct pop_entry));

  printf("appended data to file (year: %d\tborough: %s\t population: %d\n", new_entry.year, new_entry.boro, new_entry.population);
}

void update_data() {
  printf("updating data\n");
  struct pop_entry * entries = read_data();
  char data[256];

  printf("enter a data entry to update\n");
  fgets(data, sizeof(data), stdin);
  printf("%d\n", atoi(data));
  struct pop_entry modified_entry = entries[atoi(data) - 1];
  print_pop_entry(&modified_entry);

  printf("enter updated data entry #%d (year borough population)\n", atoi(data));

  char data2[256];


  read(STDIN_FILENO, data2, sizeof(data2));
  printf("%s\n", data2);
  sscanf(data2, "%d %s %d", &modified_entry.year, modified_entry.boro, &modified_entry.population);

  int f_out = open("boroughs.data", O_WRONLY | O_CREAT, 0644);
  // write entries to file
  int i;
  for (i = 0; i < sizeof(entries) / sizeof(struct pop_entry); i++) {
    write(f_out, entries + i, sizeof(struct pop_entry));
  }

}