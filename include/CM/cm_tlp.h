#ifndef CM_TLPRINT_HEADER
#define CM_TLPRINT_HEADER

#include <stddef.h>
#include <stdio.h>

/**
 * internal type to store a string output
 */
typedef struct CMTLP_Job {
  /* duration in nanoseconds to wait after this string is printed */
  int duration;

  /* utf-8 encoded string to print */
  char *str;
} CMTLP_Job;

typedef struct CMTLP_Queue {
  /* element count of the array */
  size_t length;

  /* the array */
  CMTLP_Job *queue;
} CMTLP_Queue;

/**
 * takes in csv data to generate a STR_Print_Job array, size should be the size
 * of csv data in bytes csv files should have a format row and the format should
 * be "Key,Duration(ms)"
 * the out is a pointer to a pointer that should initially be NULL
 * returns 0 on error
 */
CMTLP_Queue cmtlp_sgenQueue(const char *csv_data, size_t size);

/**
 * takes in a csv file path to generate a STR_Print_Job array, size should be
 * the size of csv data in bytes csv files should have a format row and the
 * format should be "Key,Duration(ms)" the out is a pointer to a pointer that
 * should initially be NULL returns 0 on error
 */
CMTLP_Queue cmtlp_fgenQueue(const char *csv_path);

/**
 * frees the STR_Print_Job array allocated by genQueue
 */
void cmtlp_freeQueue(CMTLP_Queue queue);

/**
 * print the queue, respecting str timings, to stdout.
 */
void cmtlp_print(const CMTLP_Queue queue);

/**
 * print the queue, respecting str timings, to given stream
 */
void cmtlp_fprint(FILE *ostream, const CMTLP_Queue queue);

/**
 * print the queue, respecting str timings, to stdout. Then free the queue.
 */
void cmtlp_printfree(CMTLP_Queue queue);

/**
 * print the queue, respecting str timings, to given stream. Then free the queue
 */
void cmtlp_fprintfree(FILE *ostream, CMTLP_Queue queue);

#endif
