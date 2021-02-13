# 6-6 Cubic Spline (50 分)

Construct the cubic spline interpolant *S* for the function *f*, defined at points $x_0<x_1<\cdots<x_n$, satisfying some given boundary conditions. Partition a given interval into *m* equal-length subintervals, and approximate the function values at the endpoints of these subintervals.

### Format of functions:

```c
void Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[]);

double S( double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[] );
```

The function `Cubic_Spline` is for calculating the set of coefficients of *S*(*x*) where $S(x)=S^{[j]}(x)=a_j+b_j(x-x_{j-1})+c_j(x-x_{j-1})^2+d_j(x-x_{j-1})^3 $ for $x \in [x_{j-1},x_j]$. The function `S` is for obtaining an approximation of $f(t)$ using the spline function $S(t)$. The parameters are defined as the following:

`int n` is the number of interpolating points−1;

`double x[]` contains `n`+1 distinct real numbers $x_0<x_1<\cdots<x_n$;

`double f[]` contains `n`+1 real numbers $f(x_0),f(x_1),\cdots,f(x_n)$;

`int Type` is the type of boundary conditions, where 1 corresponds to the clamped boundary condition $S'(x_0)=s_0,S'(x_n)=s_n$ and 2 corresponds to the natural boundary condition ;$S''(x_0)=s_0,S''(x_n)=s_n$

`double s0` and `double sn` are $s_0$ and $s_n$, respectively;

`double a[]`, `b[]`, `c[]`, and `d[]` contain the set of coefficients of $S(x)$;

`double t` is an endpoint of a subinterval;

and finally `double Fmax` is the default value that $S(t)$ will assume if *t* is out of the range $[x_0,x_n]$.

### Sample program of judge:

```c
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
```

### Sample Input:

```in
2
0.0 1.0 2.0
0.0 1.0 2.0
1 1.0 1.0 0.0
0.0 3.0 2
```

### Sample Output:

```out
0.00000000e+00 1.00000000e+00 0.00000000e+00 0.00000000e+00 
1.00000000e+00 1.00000000e+00 0.00000000e+00 0.00000000e+00 
f(0.00000000e+00) = 0.00000000e+00
f(1.50000000e+00) = 1.50000000e+00
f(3.00000000e+00) = 0.00000000e+00
```