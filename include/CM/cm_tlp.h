#ifndef CM_TLPRINT_HEADER
#define CM_TLPRINT_HEADER

#include <stddef.h>
#include <stdio.h>

/**
 * internal type to store a string output
 */
typedef struct STR_Print_Job {
  /* duration in nanoseconds to wait after this string is printed */
  int duration;

  /* utf-8 encoded string to print */
  char *str;
} STR_Print_Job;

/**
 * takes in csv data to generate a STR_Print_Job array, size should be the size
 * of csv data in bytes csv files should have a format row and the format should
 * be "Key,Duration(ms)"
 * the out is a pointer to a pointer that should initially be NULL
 * returns 0 on error
 */
size_t cmtlp_genQueue(const char *csv_data, size_t size, STR_Print_Job **out);

/**
 * frees the STR_Print_Job array allocated by genQueue
 */
void cmtlp_freeQueue(STR_Print_Job **queue, size_t queue_length);

/**
 * print the queue, respecting str timings, to stdout
 */
void cmtlp_print(STR_Print_Job *queue, size_t queue_length);

/**
 * print the queue, respecting str timings, to given stream
 */
void cmtlp_fprint(FILE *ostream, STR_Print_Job *queue, size_t queue_length);

#endif
