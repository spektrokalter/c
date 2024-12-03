#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

void
arrprint(int *p, int len)
{
	for (int *q = p; q != p+len; ++q)
		printf("	%d", *q);

	printf("\n");
}

void
arr2print(int **p, int rows, int cols)
{
	for (int **q = p; q != p+rows; ++q) {
		for (int *r = *q; r != *q+cols; ++r)
			printf("	%d", *r);

		printf("\n");
	}
}

int **
mkarr(void *vp, int nrows, int ncols)
{
	int (*arr)[ncols] = vp;

	int **p;
	p = calloc(nrows, sizeof(*p));

	int (*arrp)[ncols] = arr;
	for (int **pp = p; pp != p+nrows; ++pp) {
		*pp = calloc(ncols, sizeof(**pp));
		memcpy(*pp, *arrp, ncols * sizeof(**pp));
		++arrp;
	}

	return p;
}
