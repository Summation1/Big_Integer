#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

int main()
{
    mpz_t num1, num2, sum, diff, product, quotient;
    mpz_inits(num1, num2, sum, diff, product, quotient, NULL);

    char input1[1000], input2[1000];
    printf("Enter the first number (up to 1000 digits): ");
    scanf("%s", input1);
    printf("Enter the second number (up to 1000 digits): ");
    scanf("%s", input2);

    mpz_set_str(num1, input1, 10);
    mpz_set_str(num2, input2, 10);

    mpz_add(sum, num1, num2);
    mpz_sub(diff, num1, num2);
    mpz_mul(product, num1, num2);

    if (mpz_sgn(num2) != 0)
    {
        mpz_fdiv_q(quotient, num1, num2);
    }
    else
    {
        printf("Division by zero is undefined.\n");
        mpz_clears(num1, num2, sum, diff, product, quotient, NULL);
        return 1;
    }
    gmp_printf("num1 + num2 = %Zd\n", sum);
    gmp_printf("num1 - num2 = %Zd\n", diff);
    gmp_printf("num1 * num2 = %Zd\n", product);
    gmp_printf("num1 / num2 = %Zd\n", quotient);

    mpz_clears(num1, num2, sum, diff, product, quotient, NULL);
    return 0;
}
