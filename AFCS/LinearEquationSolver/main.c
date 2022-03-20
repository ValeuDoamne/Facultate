#include <stdio.h>
#include <gmp.h>


int main()
{
	char coefficient[128], congruence[128], moduli[128];
	mpz_t  m, b, a, gcd, mod;
	mpz_t solution, alfa, beta;
	printf("The equation has the form a*x = b mod m\n");
	printf("Please input a b m: ");
	scanf("%128s %128s %128s", coefficient, congruence, moduli);
	mpz_init_set_str(a, coefficient, 10);
	mpz_init_set_str(b, congruence, 10);
	mpz_init_set_str(m, moduli, 10);
	mpz_init(gcd);
	mpz_init(mod);
	mpz_init(alfa);
	mpz_init(beta);
	mpz_gcdext(gcd, alfa, beta, a, m);
	mpz_mod(mod, b, gcd);
	if(mpz_cmp_ui(mod, 0) == 0)
	{
		mpz_t intermediarySolution, multiple, b_prime;
	
		mpz_init(multiple);
		mpz_init(intermediarySolution);
		mpz_init(b_prime);

		mpz_div(multiple, m, gcd);
	
		mpz_div(b_prime, b, gcd);
		mpz_init_set(solution, alfa);
		mpz_mul(solution, solution, b_prime);

		mpz_t i;
		for(mpz_init(i); mpz_cmp(gcd, i) > 0 ; mpz_add_ui(i, i, 1) )
		{
			mpz_set(intermediarySolution, multiple);
			mpz_mul(intermediarySolution, intermediarySolution, i);
			mpz_add(intermediarySolution, intermediarySolution, solution);
			mpz_mod(intermediarySolution, intermediarySolution, m);

			gmp_printf("[+] Solution UwU: x_%Zd = %Zd\n", i, intermediarySolution);
		}
		mpz_clear(i);
		mpz_clear(multiple);
		mpz_clear(solution);
		mpz_clear(intermediarySolution);
		mpz_clear(b_prime);
	} else {
		printf("[-] There is no solution OwO\n");
	}
	return 0;
}
