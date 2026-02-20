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

  /* duration for sleeping */
  struct timespec duration;

  /* usage 1, creating a queue seperately and using it */
  CMTLP_Queue queue = cmtlp_fgenQueueCSV(argv[1]);
  /* you can also read the file yourself and call another function to create the
   * queue from the file's data */
  /* STR_Print_Queue queue =
   * cmtlp_sgenQueue(file_data, file_data_size_in_bytes); */

  if (queue.queue == NULL) {
    fprintf(stderr,
            "problem with csv file or data! Does %s exists and is it valid?\n",
            argv[1]);
    return 1;
  }

  printf("usage 1 result:\n");
  cmtlp_print(queue);
  /* or cmtlp_fprint((FILE*) file, queue); can also be used to specify the
   * output stream */

  /* don't forget to free the generated queue */
  cmtlp_freeQueue(queue);

  printf("usage 2 result:\n");
  /* usage 2, generating the queue and using it immediately */
  cmtlp_printfree(cmtlp_fgenQueueCSV(argv[1]));

  /* no need to call free function for the second usage if you use the correct
   * funtion (cmtlp_printFree or cmtlp_fprintfree for specifying the stream) */

  return 0;
}
