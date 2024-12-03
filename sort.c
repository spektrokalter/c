int
cmpint
	(const void *vp1, const void *vp2)
{
	int x = *(const int*)vp1;
	int y = *(const int*)vp2;
 
	return (x > y) - (x < y);
}

qsort(p, len, sizeof(*p), cmpint);
