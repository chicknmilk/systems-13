#include "boroughs.h"

struct pop_entry * create_pop_entry(int year, int population, char boro[15]) {
    struct pop_entry *new_entry = malloc(sizeof(struct pop_entry));
    new_entry->year = year;
    new_entry->population = population;
    strcpy(new_entry->boro, boro);
    return new_entry;
}

void print_pop_entry (struct pop_entry *entry) {
    printf("year: %d    boro: %s    pop: %d\n", entry->year, entry->boro, entry->population);
}

void read_csv() {
  printf("reading data.csv\n");
  
  // open file for reading
  int fp = open("data.csv", O_RDONLY, 0644);
  int f_out = open("boroughs.data", O_CREAT | O_WRONLY | O_TRUNC, 0644);

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

  int num_entries = 0;

  // read until end of file
  while (current_pos + 1 < file_data + f_info.st_size) {
    int data[6];

    sscanf(current_pos, "%u,%u,%u,%u,%u,%u", data, data + 1, data + 2, data + 3, data + 4, data + 5);

    int i;
    for (i = 1; i < 6; i++) {
      struct pop_entry *new_entry = create_pop_entry(data[0], data[i], boroughs[i - 1]);
      num_entries++;
      write(f_out, new_entry, sizeof(struct pop_entry));
    }

    // advance pointer to next line
    current_pos = strchr(current_pos, '\n') + 1;
    
  }

  printf("Wrote %ld bytes to boroughs.data\n", num_entries * sizeof(struct pop_entry));

  close(fp);
  close(f_out);
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
    printf("[%d] ", i + 1);
    print_pop_entry(pop_arr + i);
  }

  close(fp);
  return pop_arr;
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
  
  close(fp);
}

void update_data() {
  printf("updating data\n");
  struct pop_entry * entries = read_data();

  char data[256];

  printf("enter a data entry to update\n");
  fgets(data, sizeof(data), stdin);

  struct pop_entry new_entry;
  int year, population;
  char borough[15];

  char data2[256];

  printf("enter updated data entry (year borough population)\n");

  read(STDIN_FILENO, &data2, sizeof(data2));
  sscanf(data2, "%d %s %d", &new_entry.year, new_entry.boro, &new_entry.population);

  entries[atoi(data) - 1] = new_entry;

  int f_out = open("boroughs.data", O_WRONLY | O_CREAT, 0644);
  lseek(f_out, 0, SEEK_SET);

  // write entries to file

  struct stat f_info2;
  stat("boroughs.data", &f_info2);


  int i;
  for (i = 0; i < f_info2.st_size / sizeof(struct pop_entry); i++) {
    write(f_out, entries + i, sizeof(struct pop_entry));
  }

  close(f_out);
}