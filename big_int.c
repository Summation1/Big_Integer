#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int digit;
    struct Node *next;
} Node;

typedef struct BigInt
{
    Node *head;
    int size;
} BigInt;

Node *createNode(int digit)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->digit = digit;
    newNode->next = NULL;
    return newNode;
}

void appendDigit(BigInt *num, int digit)
{
    Node *newNode = createNode(digit);
    newNode->next = num->head;
    num->head = newNode;
    num->size++;
}

int compareBigInt(BigInt *num1, BigInt *num2)
{
    if (num1->size > num2->size)
    {
        return 1;
    }
    else if (num1->size < num2->size)
    {
        return -1;
    }

    Node *current1 = num1->head;
    Node *current2 = num2->head;

    while (current1 != NULL && current2 != NULL)
    {
        if (current1->digit > current2->digit)
        {
            return 1;
        }
        else if (current1->digit < current2->digit)
        {
            return -1;
        }

        current1 = current1->next;
        current2 = current2->next;
    }

    return 0;
}

BigInt *createBigInt(const char *numStr)
{
    BigInt *num = (BigInt *)malloc(sizeof(BigInt));
    num->head = NULL;
    num->size = 0;
    int i;

    int len = strlen(numStr);
    for (i = 0; i < len; i++)
    {
        int digit = numStr[i] - '0';
        appendDigit(num, digit);
    }

    return num;
}
BigInt *createBigIntFromInt(int num)
{
    char numStr[1000];
    snprintf(numStr, sizeof(numStr), "%d", num);
    return createBigInt(numStr);
}
void copyBigInt(BigInt *dest, BigInt *src)
{
    dest->size = src->size;
    dest->head = NULL;

    Node *current = src->head;
    while (current != NULL)
    {
        appendDigit(dest, current->digit);
        current = current->next;
    }
}

void destroyBigInt(BigInt *num)
{
    while (num->head != NULL)
    {
        Node *temp = num->head;
        num->head = num->head->next;
        free(temp);
    }
    free(num);
}

void printBigInt(BigInt *num)
{
    Node *current = num->head;
    while (current != NULL)
    {
        printf("%d", current->digit);
        current = current->next;
    }
    printf("\n");
}

BigInt *addBigInt(BigInt *num1, BigInt *num2)
{
    BigInt *result = (BigInt *)malloc(sizeof(BigInt));
    result->head = NULL;
    result->size = 0;

    int carry = 0;
    Node *current1 = num1->head;
    Node *current2 = num2->head;

    while (current1 != NULL || current2 != NULL || carry != 0)
    {
        int digit1 = (current1 != NULL) ? current1->digit : 0;
        int digit2 = (current2 != NULL) ? current2->digit : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        sum %= 10;

        appendDigit(result, sum);

        if (current1 != NULL)
        {
            current1 = current1->next;
        }
        if (current2 != NULL)
        {
            current2 = current2->next;
        }
    }

    return result;
}

BigInt *subtractBigInt(BigInt *num1, BigInt *num2)
{
    if (compareBigInt(num1, num2) < 0)
    {
        fprintf(stderr, "Error: Result of subtraction would be a negative number.\n");
        exit(EXIT_FAILURE);
    }

    BigInt *result = (BigInt *)malloc(sizeof(BigInt));
    result->head = NULL;
    result->size = 0;

    Node *current1 = num1->head;
    Node *current2 = num2->head;
    int borrow = 0;

    while (current1 != NULL)
    {
        int digit1 = current1->digit;
        int digit2 = (current2 != NULL) ? current2->digit : 0;

        int diff = digit1 - digit2 - borrow;

        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        appendDigit(result, diff);

        if (current1 != NULL)
        {
            current1 = current1->next;
        }
        if (current2 != NULL)
        {
            current2 = current2->next;
        }
    }

    while (result->size > 1 && result->head->digit == 0)
    {

        Node *temp = result->head;
        result->head = result->head->next;
        free(temp);
        result->size--;
    }

    return result;
}
BigInt *multiplyBigInt(BigInt *num1, BigInt *num2)
{

    BigInt *result = createBigInt("0");

    Node *current2 = num2->head;
    int shift = 0;

    while (current2 != NULL)
    {

        BigInt *tempResult = createBigInt("0");

        Node *current1 = num1->head;
        int carry = 0;

        while (current1 != NULL)
        {
            int product = current1->digit * current2->digit + carry;
            carry = product / 10;
            product %= 10;

            appendDigit(tempResult, product);

            current1 = current1->next;
        }

        if (carry > 0)
        {
            appendDigit(tempResult, carry);
        }

        int i;

        for (i = 0; i < shift; i++)
        {
            appendDigit(tempResult, 0);
        }

        result = addBigInt(result, tempResult);

        destroyBigInt(tempResult);

        current2 = current2->next;
        shift++;
    }

    return result;
}

BigInt *divideBigInt(BigInt *num1, BigInt *num2)
{
    if (compareBigInt(num2, createBigInt("0")) == 0)
    {
        fprintf(stderr, "Error: Division by zero is undefined.\n");
        exit(EXIT_FAILURE);
    }

    if (compareBigInt(num1, num2) < 0)
    {
        return createBigInt("0");
    }

    BigInt *quotient = createBigInt("0");
    BigInt *remainder = createBigInt("0");

    BigInt *tempNum1 = createBigInt("0");
    copyBigInt(tempNum1, num1);

    BigInt *tempResult, *tempSum;
    int count;

    while (compareBigInt(tempNum1, num2) >= 0)
    {
        count = 0;

        while (compareBigInt(tempNum1, num2) >= 0)
        {
            tempResult = createBigInt("0");

            Node *current1 = tempNum1->head;
            Node *current2 = num2->head;
            int borrow = 0;

            while (current1 != NULL || current2 != NULL)
            {
                int digit1 = (current1 != NULL) ? current1->digit : 0;
                int digit2 = (current2 != NULL) ? current2->digit : 0;

                int diff = digit1 - digit2 - borrow;

                if (diff < 0)
                {
                    diff += 10;
                    borrow = 1;
                }
                else
                {
                    borrow = 0;
                }

                appendDigit(tempResult, diff);

                if (current1 != NULL)
                {
                    current1 = current1->next;
                }
                if (current2 != NULL)
                {
                    current2 = current2->next;
                }
            }

            if (borrow != 0)
            {
                appendDigit(tempResult, borrow);
            }

            count++;

            destroyBigInt(tempNum1);
            tempNum1 = tempResult;
        }

        tempResult = createBigIntFromInt(count);

        tempSum = addBigInt(quotient, tempResult);

        destroyBigInt(quotient);
        destroyBigInt(tempResult);

        quotient = tempSum;
    }

    copyBigInt(remainder, tempNum1);

    destroyBigInt(tempNum1);

    return quotient;
}
