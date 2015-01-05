#include <stdio.h>

int main()
{
   int i,j,k,m,n;
   char str[1000];
   printf("please input a string:\n");
   scanf("%s",str);
   for(i = 0;i<1000;i++)
   {
     if(str[i] == '\0')
     { 
       break;
     }
   }
   
   m = i/2;
   n = i;
   k=0;

   for(i=0;i<m;i++)
   {
     for(j=n;j>m;j--)
     {
        if(str[i]==str[j])
        { 
	  k++;
	}
     } 
   }
   
   if(k == m)
   {
     printf("the string is huiwen.\n");
   }
   else
   {     
     printf("the string is not huiwen.\n");
   }
   
   return 0;

}
