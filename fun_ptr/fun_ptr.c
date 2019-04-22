#include <stdio.h>
#include <stdlib.h>
#include "tx.h"
#define TEST_NUM 5
#define TEST_BASE 30

// assumption inc and dec are much faster than inc_by
// this assumption is not realistic, just for practice
int inc(int val) {
	return val + 1;
}

int dec(int val) {
	return val - 1;
}

// use negative diff for dec_by
int inc_by(int val, int diff) {
	return val + diff;
}

// for function pointer, seems like okay to include name
void print_op(int val, int (*op)(int val)) {
	printf("val = %d\n", val);
	int ret = (*op)(val);
	printf("ret = %d\n", ret); 
}

// TODO tx_free

int main(){
	print_op(10, inc);
	print_op(20, dec);

	struct tx_t **tx_arr = (struct tx_t **) malloc(sizeof(struct tx_t) * TEST_NUM);
	int tx_eval;
	for (int i = 0; i < TEST_NUM; i++) {
		tx_arr[i] = tx_init(TEST_BASE, i, inc, inc_by);
		tx_eval = tx_run(tx_arr[i]);
		printf("tx_eval = %d\n", tx_eval);
	}

	// Didn't free tx each time right after 1 tx is allocated
	// because in a more realistic usage, there might be some thing happen between
	// allocation and free
	for (int i = 0; i < TEST_NUM; i++) {
		tx_free(tx_arr[i]);
	}

	free(tx_arr);
	return 0;
}
