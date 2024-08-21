#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

static int_fast8_t precedence_table[127] = { 
  ['+'] = 0, ['-'] = 0,
  ['*'] = 1,
};

static inline int_fast32_t get_int(char** stream_ptr) {
  int_fast32_t accum = 0;
  while (isdigit(**stream_ptr)) {
    accum = 10*accum + **stream_ptr - '0';
    (*stream_ptr)++;
  }
  return accum;
}

static inline int_fast8_t get_operator(char** stream_ptr) {
  return *((*stream_ptr)++);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s 'your math expression here'", argv[0]);
    return 1;
  }
  
  int_fast32_t precs[2] = { [0] = 0, [1] = 1 };
  int_fast32_t accum = get_int(argv + 1);
  int_fast8_t precedence;
  int_fast8_t highest_inserted_precedence = 0;

  while (argv[1][0]) {
    int_fast8_t operator = get_operator(argv + 1);
    precedence = precedence_table[operator];
    if (highest_inserted_precedence < precedence)
      highest_inserted_precedence = precedence;

    switch (highest_inserted_precedence) {
      case 0:
        precs[0] += accum;
        break;
      case 1:
        precs[1] *= accum;
        break;
    }
    if (highest_inserted_precedence > precedence) {
      highest_inserted_precedence = precedence;
      precs[0] += precs[1];
      precs[1] = 1;
    }
    accum = get_int(argv + 1);
  }

  switch (precedence) {
    case 0:
      precs[0] += accum;
      break;
    case 1:
      precs[1] *= accum;
      break;
  }
  switch (highest_inserted_precedence) {
    case 1:
      precs[0] += precs[1];
  }
  printf("%ld\n", precs[0]);

  return 0;
}
