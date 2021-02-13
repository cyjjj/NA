#include <stdio.h>
#include <math.h>

double f0( double x, double l, double t )
{
    return sqrt(1.0+l*l*t*t*cos(t*x)*cos(t*x));
}

double Integral(double a, double b, double (*f)(double x, double y, double z), 
double eps, double l, double t);

int main()
{
    double a=0.0, b, eps=0.005, l, t;

    scanf("%lf %lf %lf", &l, &b, &t);
    printf("%.2f\n", Integral(a, b, f0, eps, l, t));

    return 0;
}

/* Your function will be put here */
#define max 30
#define PI 3.1415926535897932

double Romberg(double a, double b, double (*f)(double x, double y, double z), double eps, double l, double t)
{
	double R[2][max];
	double temp, err;
	int i, j, k, n;
	for(i=0;i<max;i++)     
        R[0][i] = R[1][i] = 0;   
	double h = b - a;
	R[0][0] = h * (f(a,l,t) + f(b,l,t)) / 2;
    int min = log(h * 10) / log(2.0); //log2(10h)
    int kmax = 1;
	for(i=2;i<=max;i++)
	{
		temp = 0;
		for(k = 1; k <= kmax; k++)
			temp += f(a + (k - 0.5) * h, l, t);
		R[1][0] = (R[0][0] + h * temp) / 2;
		double mi = 4.0;
		for(j = 2; j <= i; j++)
		{
			R[1][j-1] = R[1][j-2] + (R[1][j-2] - R[0][j-2]) / (mi - 1);
			mi *= 4;
		}
		if(i > min)   
        {   
		    err = fabs(R[1][i-1] - R[0][i-2]);
            if(fabs(err) < eps) 
                break; 
        }   
		h /= 2;
		kmax *= 2;
		for(j = 1; j <= i; j++)
		    R[0][j-1] = R[1][j-1];
	}
	if(i == max)   
        return R[1][i-2];   
    else   
        return R[1][i-1]; 
}

double Integral(double a, double b, double (*f)(double x, double y, double z), double eps, double l, double t)
{
	double T, left, result;
    int n;
    T = 2.0 * PI / t;//time period
    n = b / T;//number of the time period
    left = b - n * T;//less than a time period
    
    result = Romberg(a, T, f, eps / n, l, t);   
    result = result * n + Romberg(0.0, left, f, eps, l, t);   
    return result / 100; 
}

