#include "kalkulaator-window.h"

#ifndef BITMASK
#define BITMASK

G_BEGIN_DECLS

#define KALKULAATOR_TYPE_CALC

typedef struct
{
  int *data;
}nums;

gchar *MaskOptions(int option,const char *exp, int bit);
char *PrintData(nums *num_array, int n);
void Set(nums *num_array, int bit);
void Swap(nums *num_array, int n);
void Clear(nums *num_array, int bit);

#endif //BITMASK
