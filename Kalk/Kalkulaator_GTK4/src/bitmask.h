#include "kalkulaator-window.h"

#ifndef BITMASK
#define BITMASK

G_BEGIN_DECLS

#define KALKULAATOR_TYPE_CALC

typedef struct
{
  char *set;
  char *clear;
  char *toggle;
  char *show;
}nums;

void GetMask(int option, int bit, nums *getMask);
void GetSet(int option, int bit, nums *getMask);
void GetClear(int option, int bit, nums *getMask);
void GetToggle(int option, int bit, nums *getMask);
void GetShow(int option, int bit, nums *getMask);
void Print(int option, int bit, nums *getMask);

#endif //BITMASK
