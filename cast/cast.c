#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct a {
	int val0;
	double val1;
};

struct b {
	struct a ba;
	int val2;
	long val3;
};

static void dump_a(struct a* ptr) {
	assert(ptr != 0);
	fprintf(stderr, "%d, %f\n", ptr->val0, ptr->val1);
}

static void dump_b(struct b* ptr) {
	assert(ptr != 0);
	dump_a(&ptr->ba);
	fprintf(stderr, "%d, %ld\n", ptr->val2, ptr->val3);
}

int main() {
	// declare and initiate an instance of struct a a0
	struct a *a0 = malloc(sizeof(struct a));
	a0->val0 = 1;
	a0->val1 = 1.5;
	fprintf(stderr, "a0 = ");
	dump_a(a0);
	
	struct b *b0 = (struct b*) a0;
	fprintf(stderr, "b0 = ");
	dump_b(b0);

	return 0;
}
