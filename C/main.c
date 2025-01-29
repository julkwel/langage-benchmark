#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ELEMENTS 1000000
#define STR_LEN 13  // value_(k in [0, ELEMENTS[)

typedef struct {
  size_t id;
  char value[STR_LEN];
} Item;

int main() {
  clock_t start, end;

  // Generating array
  start = clock();

  Item* array =
      malloc(ELEMENTS * sizeof(Item));  // fail to allocate if we attempt to use
                                        // the stack on many systems
  for (int i = 0; i < ELEMENTS; ++i) {
    array[i].id = i;
    snprintf(array[i].value, STR_LEN, "value_%d", i);
  }

  end = clock();
  float fetch_time = ((float)(end - start)) / CLOCKS_PER_SEC * 1000;

  // Filtering the array
  start = clock();

  size_t filtered_size = 0;
  Item* filtered = malloc(ELEMENTS * sizeof(Item));
  for (int i = 0; i < ELEMENTS; ++i)
    if (array[i].id % 2 == 0)
      filtered[filtered_size++] = array[i];
  Item* _ = realloc(
      filtered,
      filtered_size * sizeof(Item));  // just making sure we have the right size

  end = clock();
  float filter_time = ((float)(end - start)) / CLOCKS_PER_SEC * 1000;

  // Mapping the array
  start = clock();

  int* mapped = malloc(filtered_size * sizeof(int));
  for (int i = 0; i < filtered_size; ++i)
    mapped[i] = filtered[i].id;

  end = clock();
  float map_time = ((float)(end - start)) / CLOCKS_PER_SEC * 1000;

  // Reducing the array
  start = clock();

  uint64_t sum = 0;
  for (int i = 0; i < filtered_size; ++i)
    sum += filtered[i].id;

  end = clock();
  float reduce_time = ((float)(end - start)) / CLOCKS_PER_SEC * 1000;

  printf(
      "C Benchmark Results\n"
      "Time to fetch: %.2f ms\n"
      "Time to filter: %.2f ms\n"
      "Time to map: %.2f ms\n"
      "Time to reduce: %.2f ms\n",
      fetch_time, filter_time, map_time, reduce_time);

  FILE* file = fopen("../benchmark.log", "w");
  if (file == NULL) {
    perror("Error creating benchmark file");
    return EXIT_FAILURE;
  }

  fprintf(file,
          "C Benchmark Results\n"
          "Time to fetch: %.2f ms\n"
          "Time to filter: %.2f ms\n"
          "Time to map: %.2f ms\n"
          "Time to reduce: %.2f ms\n",
          fetch_time, filter_time, map_time, reduce_time);

  fclose(file);

  free(mapped);
  free(filtered);
  free(array);

  return 0;
}