#define NDICT 100001

struct entry
{
	int key, val;
	struct entry *next;
};
typedef struct entry Entry;

Entry *dict[NDICT];

Entry *
mkentry(int key, int val)
{
	Entry *e;
	e = calloc(1, sizeof(*e));

	e->key = key;
	e->val = val;

	return e;
}

Entry **
lookup(int key)
{
	Entry **e = &dict[key % NDICT];

	while (*e != NULL) {
		if ((*e)->key == key)
			return e;

		e = &(*e)->next;
	}

	return e;
}
