#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

static int_fast8_t precedence_table[127] = { 
  ['+'] = 0, ['-'] = 0,
  ['*'] = 1, ['/'] = 1
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
    fprintf(stderr, "Usage: %s 'your math expression here'\n", argv[0]);
    return 1;
  }

  double precs[2] = { [0] = 0.0, [1] = 1.0 };
  double accum = (double) get_int(argv + 1);
  int_fast8_t precedence;
  int_fast8_t highest_precedence_operator;
  int_fast8_t highest_inserted_precedence = -1;

  while (argv[1][0]) {
    int_fast8_t operator = get_operator(argv + 1);
    precedence = precedence_table[operator];
    if (highest_inserted_precedence < precedence) {
      highest_precedence_operator = operator;
      highest_inserted_precedence = precedence;
    }

    switch (highest_precedence_operator) {
      case '+':
        precs[0] += accum;
        break;
      case '-':
        precs[0] -= accum;
        break;
      case '*':
        precs[1] *= accum;
        break;
      case '/':
        precs[1] /= accum;
        break;
    }
    if (highest_inserted_precedence > precedence) {
      highest_inserted_precedence = precedence;
      highest_precedence_operator = operator;
      precs[0] += precs[1];
      precs[1] = 1;
    } else if (highest_inserted_precedence == precedence) {
      highest_inserted_precedence = precedence;
      highest_precedence_operator = operator;
    }
    accum = (double) get_int(argv + 1);
  }

  switch (highest_precedence_operator) {
    case '+':
      precs[0] += accum;
      break;
    case '-':
      precs[0] -= accum;
      break;
    case '*':
      precs[1] *= accum;
      precs[0] += precs[1];
      break;
    case '/':
      precs[1] /= accum;
      precs[0] += precs[1];
      break;
  }

  printf("%f\n", precs[0]);

  return 0;
}
