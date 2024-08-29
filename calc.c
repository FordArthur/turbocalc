#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

static inline __attribute_pure__ int_fast32_t get_int(char** stream_ptr) {
  int_fast32_t accum = 0;
  while (isdigit(**stream_ptr)) {
    accum = 10*accum + **stream_ptr - '0';
    (*stream_ptr)++;
  }
  return accum;
}

static inline __attribute_pure__ int_fast8_t get_operator(char** stream_ptr) {
  return *((*stream_ptr)++);
}

static inline __attribute_pure__ double get_muls(char** stream_ptr) {
  double muls = (double) get_int(stream_ptr);
  while (**stream_ptr == '*' || **stream_ptr == '/') {
    int_fast8_t operator = get_operator(stream_ptr);
    double temp = (double) get_int(stream_ptr);
    if (operator == '*')
      muls *= temp;
    else
      muls /= temp;
  }
  return muls;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s 'your math expression here'\n", argv[0]);
    return 1;
  }

  double sum = get_muls(argv + 1);

  while(argv[1][0]) {
    int_fast8_t operator = get_operator(argv + 1);
    double temp = get_muls(argv + 1);
    if (operator == '+')
      sum += temp;
    else
      sum -= temp;
  }

  printf("Result: %f\n", sum);

  return 0;
}
