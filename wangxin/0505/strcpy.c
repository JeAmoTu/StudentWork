#include<stdio.h>

char *my_strcpy(char *dest, const char *src)
{
  /*int i;
  for(i=0;i<strlen(src);i++)
  {
    dest[i]=src[i];
  }
  dest[i]='\0';*/
  
  while(*src!='\0')
  {
    *dest=*src;
    dest++;
    src++;
  }

  *dest='\0';
  return dest;
}

int main()
{
  char ptr[100]="hello world";
  char str[100];
  my_strcpy(str,ptr);
  printf("%s\n",str);
  return 0;
}
