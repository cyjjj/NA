#include <stdio.h>
 
void Series_Sum( double sum[] );
 
int main()
{
    int i;
    double x, sum[3001];
   
    Series_Sum( sum );
 
    x = 0.0;
    for (i=0; i<3001; i++)
        printf("%6.2lf %16.12lf\n", x + (double)i * 0.10, sum[i]);
 
    return 0;
}
 
void Series_Sum( double sum[] )
{
	int i, k;

	for (i=0; i<3001; i++)
		sum[i]=0.0;
	for (i=0; i<10; i++)
	{
		for (k=1; k<100001; k++)
		{
			sum[i]+=1.0/((double)k*((double)k+1.0)*((double)k+2.0)*((double)k+(double)i*0.10));
		}
		sum[i]*=(2.0-(double)i*0.10);
		sum[i]+=1.0/4;
		sum[i]*=(1.0-(double)i*0.10);
		sum[i]+=1.0;
	}	
	for (i=10; i<3001; i++)
	{
		sum[i]=sum[i-10]*(i-10)*1.0/i+100.0/(i*i);
	}
}
