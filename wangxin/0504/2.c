#include <stdio.h>
#include <stdlib.h>

int main()
{
  unsigned char a[300];
  int i;
  for(i=0;i<300;i++)
  {
    a[i]=-1-i;
    printf("%d ",a[i]);
   // printf("%s ",a[i]);
   // printf("%c ",a[i]);
    printf("\n");
  }
  
  printf("%d",strlen(a));
  return 0;
}
