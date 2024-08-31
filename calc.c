#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

static inline __attribute_pure__ int_fast32_t get_int(char** stream_ptr) {
  int_fast32_t accum = 0;
  while (isdigit(**stream_ptr)) {
    accum = 10*accum + **stream_ptr - '0';
    (*stream_ptr)++;
  }
  return accum;
}

static double process_expression(char**);

static inline __attribute_pure__ double get_parenthesis(char** stream_ptr){
	if(**stream_ptr != '(')
		return (double) get_int(stream_ptr);
	//is in parenthesis
	(*stream_ptr)++;
	double toReturn = process_expression(stream_ptr);
	return toReturn;
}

static inline __attribute_pure__ int_fast8_t get_operator(char** stream_ptr) {
  return *((*stream_ptr)++);
}

static inline __attribute_pure__ double get_pows(char** stream_ptr){
	double pows = get_parenthesis(stream_ptr);
	while (**stream_ptr == '^'){
		(*stream_ptr)++;
		double temp = get_parenthesis(stream_ptr);
		pows = pow(pows, temp);
	}
	return pows;
}

static inline __attribute_pure__ double get_muls(char** stream_ptr) {
  double muls = get_pows(stream_ptr);
  while (**stream_ptr == '*' || **stream_ptr == '/') {
    int_fast8_t operator = get_operator(stream_ptr);
    double temp = get_pows(stream_ptr);
    if (operator == '*')
      muls *= temp;
    else
      muls /= temp;
  }
  return muls;
}

static double process_expression(char** stream_ptr){
	double sum = get_muls(stream_ptr);
	while(**stream_ptr) {
		int_fast8_t operator = get_operator(stream_ptr);
		double temp = get_muls(stream_ptr);
		if (operator == '+')
			sum += temp;
		else
			sum -= temp;
		if(**stream_ptr == ')'){
			(*stream_ptr)++;
			return sum;
		}
	}

	return sum;
}


int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s 'your math expression here'\n", argv[0]);
    return 1;
  }

  double result = process_expression(argv + 1);

  

  printf("Result: %f\n", result);

  return 0;
}
