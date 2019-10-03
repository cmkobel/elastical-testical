#include <stdio.h>

void my_func(void);
void loop_through(int * array, unsigned int length); 
void test();

void my_func() {
	printf("hello world from ctypes.\n");
}


void loop_through(int * array, unsigned int length) {
	for (unsigned int i = 0; i < length; i++) {
		printf("%d ", array[i])	;
	}
	printf("\n");
}

void test() {
	int data[5] = {1, 2, 2, 3, 5};
	int * data_ = data;
	loop_through(data, 5);

}


