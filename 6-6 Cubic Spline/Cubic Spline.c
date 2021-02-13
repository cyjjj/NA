#include <stdio.h>

#define MAX_N 10

void Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[]);

double S( double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[] );

int main()
{
    int n, Type, m, i;
    double x[MAX_N], f[MAX_N], a[MAX_N], b[MAX_N], c[MAX_N], d[MAX_N];
    double s0, sn, Fmax, t0, tm, h, t;

    scanf("%d", &n);
    for (i=0; i<=n; i++) 
        scanf("%lf", &x[i]);
    for (i=0; i<=n; i++) 
        scanf("%lf", &f[i]);
    scanf("%d %lf %lf %lf", &Type, &s0, &sn, &Fmax);

    Cubic_Spline(n, x, f, Type, s0, sn, a, b, c, d);
    for (i=1; i<=n; i++)
        printf("%12.8e %12.8e %12.8e %12.8e \n", a[i], b[i], c[i], d[i]);

    scanf("%lf %lf %d", &t0, &tm, &m);
    h = (tm-t0)/(double)m;
    for (i=0; i<=m; i++) {
        t = t0+h*(double)i;
        printf("f(%12.8e) = %12.8e\n", t, S(t, Fmax, n, x, a, b, c, d));
    }

    return 0;
}

/* Your functions will be put here */
void Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[])
{
	double h[MAX_N], alpha[MAX_N], l[MAX_N], u[MAX_N], z[MAX_N];
	int i;
	
	for(i=0;i<=n;i++)
	    a[i] = f[i];
	for(i=0;i<n;i++)
	    h[i] = x[i+1] - x[i];
	
	if(Type == 1)//clamped boundary condition
	{
		alpha[0] = 3 * (a[1] - a[0]) / h[0] - 3 * s0;   
        alpha[n] = 3 * sn - 3 * (a[n] - a[n-1]) / h[n-1];   
   
        for(i=1;i<n;i++)   
            alpha[i] = 3 / h[i] * (a[i+1] - a[i]) - 3 / h[i-1] * (a[i] - a[i-1]); 
        
		l[0] = 2 * h[0];   
        u[0] = 0.5;   
        z[0] = alpha[0] / l[0];
		  
        for(i=1;i<n;i++)   
        {   
            l[i] = 2 * (x[i+1] - x[i-1]) - h[i-1] * u[i-1];   
            u[i] = h[i] / l[i];   
            z[i] = (alpha[i] - h[i-1] * z[i-1]) / l[i];   
        }   
   
        l[n] = h[n-1] * (2 - u[n-1]);   
        z[n] = (alpha[n] - h[n-1] * z[n-1]) / l[n];   
        c[n] = z[n];   
   
        for(i=n-1;i>=0;i--)   
        {   
            c[i] = z[i] - u[i] * c[i+1];   
            b[i] = (a[i+1] - a[i]) / h[i] - h[i] * (c[i+1] + 2 * c[i]) / 3; 
            d[i] = (c[i+1] - c[i]) / (3 * h[i]);   
        } 
	}
	else if(Type == 2)//natural boundary condition
	{
		for(i=1;i<n;i++)
		    alpha[i] = 3 / h[i] * (a[i+1] - a[i]) - 3 / h[i-1] *  (a[i] - a[i-1]);
		
		l[0] = 1;   
        u[0] = 0;   
        z[0] = 0;
        
		for(i=1;i<n;i++)
        {
        	l[i] = 2 * (x[i+1] - x[i-1]) - h[i-1] * u[i-1];   
            u[i] = h[i] / l[i];   
            z[i] = (alpha[i] - h[i-1] * z[i-1]) / l[i];
		}
		
		l[n] = 1;   
        z[n] = 0;   
        c[n] = 0;
        
		for(i=n-1;i>=0;i--)   
        {   
            c[i] = z[i] - u[i] * c[i+1];   
            b[i] = (a[i+1] - a[i]) / h[i] - h[i] * (c[i+1] + 2 * c[i]) / 3;   
            d[i] = (c[i+1] - c[i]) / (3 * h[i]);   
        } 
	}
	
	for(i=n;i>0;i--)      
    {      
        a[i] = a[i-1];      
        b[i] = b[i-1];      
        c[i] = c[i-1];      
        d[i] = d[i-1];//0~n-1 => 1~n    
    }
}

double S( double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[] )
{
	if(t < x[0] || t > x[n])
	    return Fmax;//default value when t is out of the range
	
	double S, temp;
	int i;
	
	for(i=1;i<n;i++)
	{
		if(t >= x[i-1] && t <= x[i])  
            break;//search position of t
	}
	
	//S(x)=S[j](x)=a[j]+b[j](x-x[j-1])+c[j](x-x[j-1])^2+d[j](x-x[j-1])^3
	temp = t - x[i-1];
	S = d[i] * temp;
	S = (S + c[i]) * temp;
	S = (S + b[i]) * temp;
	S += a[i];
	
	return S;
}
