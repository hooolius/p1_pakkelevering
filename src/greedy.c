#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define INF 9999999

int mat[10][10], closed[10], n, dist=0;
void matrix()
{
  int i, j;
  printf("Please type in the number of addresses\n");
  scanf(" %d", &n);
 
for( i=0; i<n ;i++)
     {
     printf("\n Enter Elements of Row # : %d\n", i+1);
     for( j=0; j<n; j++)
     scanf(" %d", &mat[i][j]);
     closed[i] = 0;
     }
 
for( i=0; i<n ;i++)
     {
     printf("\n\n");
     for( j=0; j<n ;j++)
          printf("\t%d", mat[i][j]);
          }        
}
// HERE THE ARRAY IS TRANSFERED IN MATRIX  

  int least(int c)
  {
    int i, node = INF;
    int min = INF, kmin;
    for(i=0; i<n; i++)
      {
       if((mat[c][i] != 0) && (closed[i]==0))
       if(mat[c][i] < min)
      {
        min = mat[i][0] + mat[c][i];
        kmin = mat[c][i];
        node = i;
      }
  }
 
if(min != INF)
dist += kmin;
return node;
}

void price(int point)
{
int i, npoint;
closed[point] = 1;
printf("%d ===> ", point + 1);
npoint = least(point);
 
if(npoint == INF)
    {
     npoint = 0;
     printf("%d", npoint + 1);
     dist += mat[point][npoint];
     return;
     }
 
price(npoint);
}
 
void min()
{
 printf("\n The minimum price:");
 printf("%d", dist);
}
 
int main()
{
matrix();
printf("\n The rute:\n\n");
price(0);
min();
}