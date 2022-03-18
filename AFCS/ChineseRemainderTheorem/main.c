#include <stdio.h>
#include <stdbool.h>
#include <gmp.h>


bool check_for_solution(int size, mpz_t moduli[])
{
	mpz_t gcd;
	mpz_init(gcd);
	for(int i = 0; i < size; i++)
	{
		for(int j = i+1; j < size; j++)
		{
			mpz_gcd(gcd, moduli[i], moduli[j]);
			if(mpz_cmp_ui(gcd, 1) != 0)
				return false;
		}
	}
	mpz_clear(gcd);
	return true;
}


void solve_eq(FILE *fp)
{
	mpz_t c[64], moduli[64], congruence[64], solutions[64], x;
	mpz_t n;
	
	int equations = 0;
	
	mpz_init_set_ui(n, 1);

	for(int i = 0; !feof(fp); i++)
	{
		char cong[1024], mod[1024]; 
		fscanf(fp, "x = %1024s mod %1024s\n", cong, mod);
		mpz_init_set_str(congruence[i], cong, 0);
		mpz_init_set_str(moduli[i], mod, 0);
		mpz_mul(n, n, moduli[i]);
	
		equations++;
	}

	if(check_for_solution(equations, moduli) == false)
	{
		printf("I am not smart enough to solve the problem! :'((((\n\n");
		return;
	}
	
	for(int i = 0; i < equations; i++)
	{
		mpz_init(c[i]);
		mpz_div(c[i], n, moduli[i]);
	}
	
	mpz_t c_intermediar, gcd, alfa, beta;
	
	mpz_init(c_intermediar);
	mpz_init(gcd);
	mpz_init(alfa);
	mpz_init(beta);

	for(int i = 0; i < equations; i++)
	{
		mpz_set(c_intermediar, c[i]);
		mpz_mod(c_intermediar, c_intermediar, moduli[i]);
		mpz_gcdext(gcd, alfa, beta, c_intermediar, moduli[i]);
		mpz_init_set(solutions[i], alfa);
		mpz_mul(solutions[i], solutions[i], congruence[i]);
		mpz_mod(solutions[i], solutions[i], moduli[i]);
	}
	
	mpz_clear(beta);
	mpz_clear(alfa);
	mpz_clear(gcd);
	mpz_clear(c_intermediar);
	

	mpz_init_set_ui(x, 0);

	mpz_t mul;
	mpz_init(mul);
	for(int i = 0; i < equations; i++)
	{
		mpz_set(mul, c[i]);
		mpz_mul(mul, mul, solutions[i]);
		mpz_add(x, x, mul);
		mpz_mod(x, x, n);
	}
	mpz_clear(mul);
	
	gmp_printf("Big Solution To The Equations: x = %Zd\n", x);

	for(int i = 0; i < equations; i++)
	{
		mpz_clear(solutions[i]);
		mpz_clear(c[i]);
		mpz_clear(congruence[i]);
		mpz_clear(moduli[i]);
	}

	mpz_clear(n);
}

int main(int argc, char **argv)
{
	FILE *fp = NULL;
	if(argc < 2)
	{
		printf("Usage: %s input_file\n", argv[0]);
		return 0;
	}
	if((fp = fopen(argv[1], "r") ) != NULL)
	{
		solve_eq(fp);
	} else {
		fprintf(stderr, "Cannot open file\n");
		return -1;
	}
	return 0;
}
