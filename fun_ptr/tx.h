union Operation {
	int (*op)(int val);
	int (*op_by)(int val, int diff);
};

struct tx_t {
	int val;
	int diff;
	union Operation *op;
};

struct tx_t *tx_init(int val, int diff,
	int (*op)(int val),
	int (*op_by)(int val, int diff));
void tx_free(struct tx_t *tx);
int tx_run(struct tx_t *tx);
