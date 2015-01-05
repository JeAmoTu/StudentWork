#include<stdio.h>

char *my_strchr(const char *s, int c)
{
  int i;
  while(i<strlen(s))
  {
    if(*s==c)
    {
      break;
    }
    s++;
    i++;
  }
 
  return s;
}

int main()
{
  
  char a[100]="hello world";
  char  *p;
  p=my_strchr(a,'l');
  printf("%c",*p);
  return 0;
}
