#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

void swap(int* a, int* b)  
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  


int partition (int P[], int low, int high)  
{  
    int pivot = P[high]; // pivot  
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if(P[j] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&P[i],&P[j]);  
        }  
    }  
    swap(&P[i + 1],&P[high]);  
    return (i + 1);  
}  
  

void quicksort(int P[],int low,int high)
{
	if(low<high){
		int pi=partition(P,low,high);
		
		quicksort(P,low,pi-1);
		quicksort(P,pi+1,high);
		}
}

int sum(int P[],int L[],int index,int data[],int r,int maxsum)
{
	int n=r,c=0;
	while(c!=n)
	{
		for(int i=r-1;i>=0;i--)
		{
			if(data[i]!=0)
			{
			int s=P[i];
			c++;
			for(int j=i-1;j>=0;j--)
			{
				if(s+P[j]<=maxsum && data[j]!=0)
				{
					s+=P[j];
					data[j]=0;
					c++;
				}
			}
			if(s<=maxsum)
			{
				L[index++]=s;
				data[i]=0;
			}
			}
		}
	}
	printf("%d \n",index);
}

void subsetsum(int P[],int L[],int m,int n,int r,int index,int idea[],int maxsum)
{
	if(r-1==0)
		return;

	int data[r];
	for(int i=0;i<r;i++)
	{
		data[i]=-1;
	}
	sum(P,L,index,data,r,maxsum);
}

void supportfunction(int P[],int L[],int m,int n)
{
	int maxsum=P[n-1];
	L[0]=maxsum;
	int index=1;
	int idea[n];
	for(int i=0;i<n;i++)
		idea[i]=0;
	idea[n-1]=1;
	subsetsum(P,L,m,n,n-1,index,idea,maxsum);
}

int main(int argc,char *argv[])
{

	int i,m=0,j=1,n;
	if(argc!=3){
		printf("Usage: %s <number_of_processors> <instance_filename>\n", argv[0]);
		exit(0);
		}

	//read number of processors
	for(i = strlen(argv[1]); i > 0; i--) {
         m += ((*(argv[1] + i - 1)) - '0') * j;
 	 //printf("%d %d %d\n", i, ((*(argv[1] + i - 1)) - '0'), j );
         j = j*10;
    }
	//printf("%d\n\n",m);
	FILE *fp_in;
     	fp_in  = fopen(argv[2],"r");
     
     	if (fp_in != NULL) {
		fscanf(fp_in, "%d", &n);        //Number of tasks in the instance file
    		 } else {
				printf("Cant open file %s\n", argv[2]);
        			exit(0);
    				 }
     
    	 int P[n];
     

	for (i=0; i<n; i++) {
			if ( (fscanf(fp_in, "%d", &P[i])) > 0) { 
					} else {
	    					printf("Not enough arguments in Instance file\n");
	    					exit(0);
						}
     				}					
			
    	 pclose(fp_in);
    	//for (i=0;i<n;i++)
    	//	printf("%d ",P[i]);
       	printf("\nNumber of tasks: %d\n", n);
     	printf("Number of processors: %d\n", m);     
     	printf("Ltotal = ");

	quicksort(P,0,n-1);		
	
	int L[m];
	for(int i=0;i<m;i++)
		L[i]=0;
	
	supportfunction(P,L, m, n);
	
	
	printf("The max load using  is %d\n\n", L[0]);
        
	printf("The load split on different processors is:\n");

        for (i=0; i<m; i++) {
		printf("L%d = %d\n", i, L[i]);
    		 }
}
