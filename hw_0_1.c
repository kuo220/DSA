#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int MAX_SIZE = 256 + 1;

int charToDigit(char num);
void reverseNum(char numA[], char numB[], int a[], int b[], int lenA, int lenB);
void assignNum(int a[], int b[]);
void swap(int a[], int b[]);
int lenOfNum(int num[]);
char compare(int a[], int b[]);
bool isZero(int num[]);
void subtract(int a[], int b[]);
void multiply(int a[], int b[], int ans[]);
void multiplyInt(int ans[], int x);
void divideInt(int a[], int x);
void printBigInt(int ans[]);
void binaryGCD(int a[], int b[], int ans[]);


int main()
{
    char numA[MAX_SIZE] = {0};
    char numB[MAX_SIZE] = {0};
    int a[MAX_SIZE] = {0};
    int b[MAX_SIZE] = {0};
    int ans[MAX_SIZE] = {0};


    scanf("%s%s", numA, numB);

    int lenA = strlen(numA);
    int lenB = strlen(numB);
    int ansLen = sizeof(ans) / sizeof(ans[0]);

    reverseNum(numA, numB, a, b, lenA, lenB);
    binaryGCD(a, b, ans);
    printBigInt(ans);

    
}



int charToDigit(char num)
{
    return num - '0';
}

/* input the char array to the int array */
void reverseNum(char numA[], char numB[], int a[], int b[], int lenA, int lenB) // 17202 => |2|0|2|7|1|
{   
    for(int i = 0; i < lenA; i++)
    {
        a[i] = charToDigit(numA[lenA - 1 - i]);
    }

    for(int j = 0; j < lenB; j++)
    {
        b[j] = charToDigit(numB[lenB - 1 - j]);
    }
}


void assignNum(int a[], int b[]) // b assign to a
{   
    memset(a, 0, MAX_SIZE);

    for(int i = (MAX_SIZE - 1); i >= 0; i--)
    {
        a[i] = b[i];
    }
}


int lenOfNum(int num[])
{
    int i = MAX_SIZE - 1;
    for(; i > 0 && num[i] == 0; i--);
    return i + 1;
}


char compare(int a[], int b[])
{   
    int lenA = lenOfNum(a);
    int lenB = lenOfNum(b);

    if(lenA > lenB)
    {
        return 'a';
    }

    else if(lenA < lenB)
    {
        return 'b';
    }

    else if(lenA == lenB)
    {
        for(int i = (lenA - 1); i >= 0; i--)
        {
            if(a[i] > b[i])
            {
                return 'a';
            }

            else if(a[i] == b[i])
            {
                continue;
            }

            else if(a[i] < b[i])
            {
                return 'b';
            }
           
        }

        
        {
            return 'b';
        }
    }

    return 's';

}


void swap(int a[], int b[])
{   
    int temp[MAX_SIZE] = {0};

    assignNum(temp, a);
    assignNum(a, b);
    assignNum(b, temp);

}



bool isZero(int num[])
{
    int cnt = 0;

    for(int i = 0; i < MAX_SIZE; i++)
    {
        if(num[i] == 0)
        {
            cnt++;
        }
    }

    return (cnt == MAX_SIZE) ? true : false;
}



void subtract(int a[], int b[])
{
    int borrow = 0;
    int temp[MAX_SIZE] = {0};

    if(compare(a, b) == 'a' )
    {
        for(int i = 0; i < MAX_SIZE; i++)
        {
            temp[i] = a[i] - b[i] - borrow;

            if(temp[i] < 0)
            {
                temp[i] += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
        }
    }

    memset(a, 0, MAX_SIZE);
    assignNum(a, temp);
}


void multiply(int a[], int b[], int ans[])
{   
    int carry = 0;

    for(int i = 0; i < MAX_SIZE; i++)
    {   
        if(a[i] == 0)
        {
            continue;
        }

        for(int j = 0; i + j < MAX_SIZE; j++)
        {
            ans[i + j] += a[i] * b[j];
        }
    }


    for(int i = 0; i < MAX_SIZE; i++)
    {
        ans[i] += carry;
        carry = ans[i] / 10;
        ans[i] %= 10;
    }


}

void multiplyInt(int num[], int x)
{   
    int carry = 0;
    int temp[MAX_SIZE] = {0};

    for(int i = 0; i < MAX_SIZE; i++)   
    {
        temp[i] += num[i] * x;
    }

    for(int j = 0; j < MAX_SIZE; j++)
    {
        temp[j] += carry;
        carry = temp[j] / 10;
        temp[j] %= 10;
    }

    assignNum(num, temp);

}


void divideInt(int a[], int x)
{
    int r = 0;
    int q[MAX_SIZE] = {0};

    for(int i = MAX_SIZE - 1; i >= 0 ; i--)
    {
        r = r * 10 + a[i];
        q[i] = r / x;
        r = r % x;
    }

    memset(a, 0, MAX_SIZE);

    for(int i = (MAX_SIZE - 1); i >=0; i--)
    {
        a[i] = q[i];
    }
}


void printBigInt(int ans[])
{   
    int i = MAX_SIZE - 1;
    
    for(; i > 0 && ans[i] == 0; i--);

    while(i >= 0)
    {
        printf("%d", ans[i]);
        i--;
    }
}


void binaryGCD(int a[], int b[], int ans[])
{

    int tempAns[MAX_SIZE] = {0};
    tempAns[0] = 1;
    
    while(isZero(a) == false && isZero(b) == false)
    {   

        if(a[0] % 2 == 0 && b[0] % 2 == 0)
        {
            divideInt(a, 2);
            divideInt(b, 2);
            multiplyInt(tempAns, 2);
        }

        else if(a[0] % 2 == 0 && b[0] % 2 != 0) // a is even
        {
            divideInt(a, 2);
        }

        else if(a[0] % 2 != 0 && b[0] % 2 == 0) // b is even
        {
            divideInt(b, 2);
        }

        if(compare(a, b) == 'b')
        {
            swap(a, b);
        }
        
        subtract(a, b);


    }

    multiply(b, tempAns, ans);
    
}

