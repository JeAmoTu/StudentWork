#include<stdio.h>

int main()
{
  int i,j,k,m=0,n;
  printf("please input the num of people:\n");
  scanf("%d",&n);
  int a[n];

  for(i=0;i<n;i++)
  {
    a[i]=i+1;
  }
  
  k=0;
  i=0;
  while(m<n-1)
  {
      if(a[i]!=0)
      {
        k++;
      }

      if(k==3)
      {
        a[i]=0;
	k=0;
	m++;
      }
  
      i++;
      
      if(i==n)
      {
        i=0;
      }
    
  }
  
  for(i=0;i<n;i++)
  {
    if(a[i]!=0)
     break;
  }
  
  printf("the last people's num is %d\n",a[i]);
  
  return 0;
}
