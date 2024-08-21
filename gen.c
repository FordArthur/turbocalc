#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char symbols[] = "+*";

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s number-of-calculations max-number", argv[0]);
    return 1;
  }
  int expr_length = 2*atoi(argv[1])-1;
  int max_num = atoi(argv[2]);
  srand(time(NULL));
  for (; expr_length; expr_length--) {
    unsigned int random_num = rand();
    if (expr_length % 2)
      printf("%u", random_num % max_num);
    else 
      printf("%c", symbols[random_num % 2]);
  }
  printf("\n");
}
