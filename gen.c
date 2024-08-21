#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char symbols[] = "+*";

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s number-of-calculations", argv[0]);
    return 1;
  }
  int expr_length = 2*atoi(argv[1])-1;
  srand(time(NULL));
  for (; expr_length; expr_length--) {
    unsigned int random_num = rand();
    if (expr_length % 2)
      printf("%u", random_num);
    else 
      printf("%c", symbols[random_num % 4]);
  }
  printf("\n");
}
