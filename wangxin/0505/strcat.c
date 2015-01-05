#include<stdio.h>

char *my_strcat(char *dest, const char *src)
{
   /* int i,j;
    i=strlen(dest);
    for(j=0;*src!='\0';j++)
    {
      dest[i]=src[j];
      dest[i++];
    }
    dest[i]='\0';*/

   
    while(*dest!='\0')
    {
      dest++;
    }
    while(*dest=='\0')
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
  char str[100]="hello world";
  char ptr[100]="kkkk";
  my_strcat(ptr,str);
  printf("%s\n",ptr);
  
  return 0;
}
