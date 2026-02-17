/*
"type like printing" is a simple library for timed printing
Copyright (C)  2026  AKKAYA Sarp

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License Version 2 as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License Version 2 for more details.

You should have received a copy of the GNU General Public License Version 2
along with this program; if not, write to the Free Software Foundation, Inc., 51
Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <CM/cm_tlp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {
  /* sanity check */
  if (argc < 2) {
    fprintf(stderr, "usage: %s CSV_FILE\n", argv[0]);
    return 1;
  }

  /* array that stores the key and duration values */
  STR_Print_Job *queue = NULL;
  /* key press count */
  size_t queue_length = 0;
  /* duration for sleeping */
  struct timespec duration;

  /* opening the csv file */
  FILE *csv_file = fopen(argv[1], "r");
  if (csv_file == NULL) {
    fprintf(stderr, "couldn't open the csv file! Does %s exists?\n", argv[1]);
    return 1;
  }

  fseek(csv_file, 0, SEEK_END);
  size_t filesize = ftell(csv_file);
  rewind(csv_file);

  char *file_data = malloc(filesize);
  fread(file_data, 1, filesize, csv_file);

  fclose(csv_file);

  queue_length = cmtlp_genQueue(file_data, filesize + 1, &queue);
  free(file_data);

  cmtlp_print(queue, queue_length);

  cmtlp_freeQueue(&queue, queue_length);

  return 0;
}
