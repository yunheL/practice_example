#include <stdlib.h>
#include "tx.h" 

struct tx_t *tx_init(int val, int diff,
	int (*op)(int val),
	int (*op_by)(int val, int diff)) {
	struct tx_t *tx = (struct tx_t *) malloc(sizeof(struct tx_t));
	union Operation *tx_op = (union Operation *) malloc(sizeof(union Operation));
	tx->val = val;
	tx->diff = diff;
	tx->op = tx_op;
	if (diff == 1) {
		tx->op->op = op;
	} else {
		tx->op->op_by = op_by;
	}
	return tx;
}

void tx_free(struct tx_t *tx) {
	free(tx->op);
	free(tx);
}

int tx_run(struct tx_t *tx) {
	if (tx->diff == 1) {
		return (*tx->op->op)(tx->val);
	} else {
		return (*tx->op->op_by)(tx->val, tx->diff);
	}
}
