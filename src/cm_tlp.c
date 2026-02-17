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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

size_t cmtlp_genQueue(const char *csv_data, size_t size, STR_Print_Job **out) {
  /* pre-defined format of the csv file */
  const char *csv_format = "Key,Duration(ms)";

  char *csv_copy = malloc(size + 1);
  if (csv_copy == NULL)
    return 0;

  memcpy(csv_copy, csv_data, size);
  csv_copy[size] = 0;
  size++;

  char *line = csv_copy;
  size_t second_line_start = 0;

  /* checking if the first line of the file is the correct format */
  for (size_t n = 0; n < size; n++) {
    /* finding the next line */
    if (csv_copy[n] != '\n' && csv_copy[n] != 0)
      continue;

    csv_copy[n] = 0;

    /* working on said line */
    if (strcmp(line, csv_format) != 0) {
      free(csv_copy);
      return 0;
    }

    /* getting ready for the next line after giving enough affection to the
     * previous line */
    line = csv_copy + (n + 1);
    second_line_start = n + 1;
    break;
  }

  size_t queue_length = 0;

  /* parsing the rest of the file */
  for (size_t n = second_line_start; n < size; n++) {
    /* finding the next line */
    if (csv_copy[n] != '\n' && csv_copy[n] != 0)
      continue;

    /* making sure the line will be 0 terminated */
    csv_copy[n] = 0;

    /* working on said line */
    size_t str_len = 0;
    for (int i = 0; line[i] != 0; i++) {
      if (line[i] == ',') {
        str_len = i;
        break;
      }
    }

    if (str_len == 0) {
      /* we ignore problematic kids */
    } else {
      queue_length++;
      (*out) = realloc((*out), sizeof(STR_Print_Job) * queue_length);

      line[str_len] = 0;
      if (strcmp(line, "Enter") == 0) {
        (*out)[queue_length - 1].str = malloc(2);
        (*out)[queue_length - 1].str[0] = '\n';
        (*out)[queue_length - 1].str[1] = 0;
      } else {
        (*out)[queue_length - 1].str = malloc(str_len + 1);
        memcpy((*out)[queue_length - 1].str, line, str_len + 1);
      }

      (*out)[queue_length - 1].duration =
          strtol(&line[str_len + 1], NULL, 10) * 1000000;
    }

    /* getting ready for the next line after giving enough affection to the
     * previous line */
    line = csv_copy + (n + 1);
  }

  free(csv_copy);
  return queue_length;
}

void cmtlp_freeQueue(STR_Print_Job **queue, size_t queue_length) {
  for (size_t i = 0; i < queue_length; i++) {
    free((*queue)[i].str);
  }

  free(*queue);
  (*queue) = NULL;
}

void cmtlp_print(STR_Print_Job *queue, size_t queue_length) {
  struct timespec duration;

  for (size_t i = 0; i < queue_length; i++) {
    duration.tv_sec = queue[i].duration / 1000000000;
    duration.tv_nsec = queue[i].duration % 1000000000;
    printf("%s", queue[i].str);
    nanosleep(&duration, NULL);
    fflush(stdout);
  }
}

void cmtlp_fprint(FILE *ostream, STR_Print_Job *queue, size_t queue_length) {
  struct timespec duration;

  for (size_t i = 0; i < queue_length; i++) {
    duration.tv_sec = queue[i].duration / 1000000000;
    duration.tv_nsec = queue[i].duration % 1000000000;
    fprintf(ostream, "%s", queue[i].str);
    fflush(ostream);
    nanosleep(&duration, NULL);
  }
}
