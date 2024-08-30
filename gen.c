#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char symbols[] = "+-*/";

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s number-of-calculations max-number\n", argv[0]);
    return 1;
  }
  int expr_length = 2*atoi(argv[1])-1;
  int max_num = atoi(argv[2]);
  unsigned int num_of_parens = 0;
  srand(time(NULL));
  for (; expr_length; expr_length--) {
    unsigned int random_num = rand();
    if (expr_length % 2) {
      if (random_num % 13 == 7) {
        num_of_parens++;
        printf("(%u", random_num % max_num);
      } else if (random_num % 13 == 5 && num_of_parens) {
        num_of_parens--;
        printf("%u)", random_num % max_num);
      } else printf("%u", random_num % max_num);
    }
    else
      printf("%c", symbols[random_num % sizeof(symbols)]);
  }
  for (; num_of_parens; num_of_parens--) printf(")");
  printf("\n");
}
