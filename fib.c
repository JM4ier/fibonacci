#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

#define ll long long int

static void mat_mul(mpz_t *res, mpz_t *a, mpz_t *b) {
	mpz_mul   (res[0], a[0], b[0]);
	mpz_addmul(res[0], a[1], b[2]);

	mpz_mul   (res[1], a[0], b[1]);
	mpz_addmul(res[1], a[1], b[3]);

	mpz_mul   (res[2], a[0], b[2]);
	mpz_addmul(res[2], a[2], b[3]);

	mpz_mul   (res[3], a[1], b[2]);
	mpz_addmul(res[3], a[3], b[3]);
}

static void mat_swap(mpz_t *a, mpz_t *b) {
	mpz_swap(a[0], b[0]);
	mpz_swap(a[1], b[1]);
	mpz_swap(a[2], b[2]);
	mpz_swap(a[3], b[3]);
}

static void mat_mod(mpz_t *a, ll p) {
	if (p) {
		mpz_mod_ui(a[0], a[0], p);
		mpz_mod_ui(a[1], a[1], p);
		mpz_mod_ui(a[2], a[2], p);
		mpz_mod_ui(a[3], a[3], p);
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("usage: %s number [modulus]\n", argv[0]);
		return -1;
	}

	ll n = atoll(argv[1]);
	ll p = 0;
	if (argc > 2) {
		p = atoll(argv[2]);
	}

	mpz_t a[4];
	mpz_t b[4];
	mpz_t c[4];

	for (int i = 0; i < 4; i++) {
		mpz_init(a[i]);
		mpz_init(b[i]);
		mpz_init(c[i]);
	}

	mpz_set_ui(a[0], 1);
	mpz_set_ui(a[1], 1);
	mpz_set_ui(a[2], 1);

	mpz_set_ui(c[0], 1);
	mpz_set_ui(c[3], 1);

	for (ll m = 1; m <= n; m = m << 1) {
		if (m & n) {
			mat_mul(b, a, c);
			mat_swap(b, c);
			mat_mod(c, p);
		}

		mat_mul(b, a, a);
		mat_swap(a, b);
		mat_mod(a, p);
	}

	mpz_out_str(stdout, 10, c[1]);
	printf("\n");

	return 0;
}

