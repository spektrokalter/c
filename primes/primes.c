#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int *
primes(int limit, int *len)
{
	bool *sieve;
	sieve = calloc(limit, sizeof(*sieve));

	sieve[0] = sieve[1] = true;
	*len = 0;

	for (bool *sp = sieve; sp != sieve+limit; ++sp) {
		if (*sp)
			continue;

		++*len;

		int prime = sp - sieve;
		for (bool *notprime = sp+prime; notprime < sieve+limit; notprime += prime)
			*notprime = true;
	}

	int *primes;
	primes = calloc(*len, sizeof(*primes));

	int *p = primes;
	for (bool *sp = sieve; sp != sieve+limit; ++sp) {
		if (!*sp)
			*(p++) = sp - sieve;
	}

	free(sieve);

	return primes;
}

int
main(void)
{
	int len = 0;
	int *p = primes(1000, &len);

	for (int *pp = p; pp != p+len; ++pp)
		printf("%d\n", *pp);

	return 0;
}
