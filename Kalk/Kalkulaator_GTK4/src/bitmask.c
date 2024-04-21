#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmask.h"



void GetMask(int option, int bit, nums *getMask)
{
  bit--;
  GetSet(option, bit, getMask);
  GetClear(option, bit, getMask);
  GetToggle(option, bit, getMask);
  GetShow(option, bit, getMask);
  Print(option, bit, getMask);
}

void GetSet(int option, int bit, nums *getMask)
{
  for(int i = 0; i < option; i++)
  {
    if(bit == i)
      getMask[i].set = "1";
    else
      getMask[i].set = "0";
  }
}

void GetClear(int option, int bit, nums *getMask)
{
  for(int i = 0; i < option; i++)
  {
    if(bit == i)
      getMask[i].clear = "0";
    else
      getMask[i].clear = "1";
  }
}

void GetToggle(int option, int bit, nums *getMask)
{
  for(int i = 0; i < option; i++)
  {
    if(bit == i)
      getMask[i].toggle = "1";
    else
      getMask[i].toggle = "0";
  }
}

void GetShow(int option, int bit, nums *getMask)
{
  for(int i = 0; i < option; i++)
  {
    if(bit == i)
      getMask[i].show = "1";
    else
      getMask[i].show = "0";
  }
}

void Print(int option, int bit, nums *getMask)
{
  for(int i = option-1; i >= 0; i--)
  {
    printf("%s", getMask[i].set);
  }
  printf("\n");
  for(int i = option-1; i >= 0; i--)
  {
    printf("%s", getMask[i].clear);
  }
  printf("\n");
  for(int i = option-1; i >= 0; i--)
  {
    printf("%s", getMask[i].toggle);
  }
  printf("\n");
  for(int i = option-1; i >= 0; i--)
  {
    printf("%s", getMask[i].show);
  }
  printf("\n\n");
}
