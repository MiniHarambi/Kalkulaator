#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmask.h"

char *MaskOptions(int option, const char *exp, int bit)
{
    int n = strlen(exp);
    nums num_array[n];

    for (int i = 0; i < n; i++)
    {
        num_array[i].data = malloc(sizeof(int));
        if (num_array[i].data == NULL)
        {
            exit(EXIT_FAILURE);
        }
        *(num_array[i].data) = exp[i] - '0';
    }

    char *binary = malloc(sizeof(char) * (n + 1));
    if (binary == NULL)
    {
        exit(EXIT_FAILURE);
    }
    if (bit >= 0 && bit < n)
    {
      switch (option)
      {
      case (1):
          Set(&num_array[bit], bit); // Pass the address of the i-th element
          binary = PrintData(num_array, n);
          return binary;
          break;
      case (2):
          Clear(&num_array[bit], bit); // Pass the address of the i-th element
          binary = PrintData(num_array, n);
          return binary;
          break;
      case (3):
          printf("read");
          break;
      case (4):
          printf("toggle");
          break;
      default:
          for (int i = 0; i < n; i++)
          {
              free(num_array[i].data);
          }
          exit(EXIT_FAILURE);
      }
    }

    exit(EXIT_SUCCESS);
}

void Set(nums *num_array, int bit)
{
    *num_array[bit].data = 1;
}

void Clear(nums *num_array, int bit)
{
    *num_array[bit].data = 0;
}

char *PrintData(nums *num_array, int n)
{
    char *binary = malloc(n + 1);
    if (binary == NULL)
    {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++)
    {
        binary[i] = *(num_array[i].data) + '0';
    }
    binary[n] = '\0';
    return binary;
}



void Swap(nums *num_array, int n)
{
    for (int i = 0, x = n - 1; i < n / 2; i++, x--)
    {
        int temp = *num_array[i].data;
        num_array[i].data =num_array[x].data;
        *num_array[x].data = temp;
    }
}

/*

void PrintData(numsnum_array, int n);
void Set(nums num_array, int n, int bit);
void Swap(numsnum_array, int n);
void Clear(nums num_array, int n, int bit);


int main(void) {



    Swap(num_array, n);
    PrintData(num_array, n);

    int setting = 1;
    while(1) {
        printf("bit > ");
        scanf("%d", &bit);
        printf("1 - Set\n2 - Clear\n");
        scanf("%d", &setting);
        switch (setting) {
            case 1:
                Set(num_array, n, bit);
                PrintData(num_array, n);
                break;
            case 2:
                Clear(num_array, n, bit);
                PrintData(num_array, n);
                break;
            default:
                for (int i = 0; i < n; i++) {
                    free(num_array[i].data);
                }
                exit(EXIT_SUCCESS);
        }
    }

    return 0;
}


void Set(numsnum_array, int n, int bit)
{
    num_array[bit].data = 1;
}

void Clear(numsnum_array, int n, int bit)
{
    num_array[bit].data = 0;
}

void PrintData(numsnum_array, int n)
{
    for (int i = n-1; i >= 0; i--)
    {
        printf("%d", num_array[i].data);
    }
    printf("\n\n");
}


void Swap(numsnum_array, int n)
{
    for (int i = 0, x = n - 1; i < n / 2; i++, x--)
    {
        int temp = *num_array[i].data;
        num_array[i].data =num_array[x].data;
        *num_array[x].data = temp;
    }
}

*/




/*
char *int_to_binary(int num, int n)
{
    char *binary_str = (char *)malloc((n + 1) * sizeof(char)); // Allocate memory for the string (n bits + null terminator)
    if (binary_str == NULL)
    {
        return NULL;
    }
    binary_str[n] = '\0'; // Null terminate the string

    for (int i = n - 1; i >= 0; i--) // Corrected loop condition
    {
        binary_str[i] = (num & 1) ? '1' : '0';
        num >>= 1;
    }

    return binary_str;
}
 */
