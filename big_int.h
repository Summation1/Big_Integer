#ifndef BIG_INT_H
#define BIG_INT_H

typedef struct BigInt BigInt;

BigInt *createBigInt(const char *numStr);
int compareBigInt(BigInt *num1, BigInt *num2);
BigInt *createBigIntFromInt(int num);
void destroyBigInt(BigInt *num);
void printBigInt(BigInt *num);
void appendDigit(BigInt *num, int digit);
BigInt *addBigInt(BigInt *num1, BigInt *num2);
BigInt *subtractBigInt(BigInt *num1, BigInt *num2);
BigInt *multiplyBigInt(BigInt *num1, BigInt *num2);
BigInt *divideBigInt(BigInt *num1, BigInt *num2);
void copyBigInt(BigInt *dest, BigInt *src);

#endif
