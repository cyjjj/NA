# 6-7 Orthogonal Polynomials Approximation (40 分)

Given a function *f* and a set of *m*>0 distinct points $x_1<x_2<\cdots<x_m$. You are supposed to write a function to approximate *f* by an orthogonal polynomial using the exact function values at the given *m* points with a weight $w(x_i)$ assigned to each point $x_i$. The total error $err=\sum_{i=1}^{m}{w(x_i)[f(x_i)-P_n(x_i)]^2}$ must be no larger than a given tolerance.

### Format of function:

```c
int OPA( double (*f)(double t), int m, double x[], double w[], double c[], double *eps );
```

where the function pointer `double (*f)(double t)` defines the function `f`; `int m` is the number of points; `double x[]` contains points $x_1<x_2<\cdots<x_m$; `double w[]` contains the values of a weight function at the given points `x[]`; `double c[]` contains the coefficients $c_0,c_1,\cdots,c_n$ of the approximation polynomial $P_n(x)=c_0+c_1x+\cdots+c_nx^n$; `double *eps` is passed into the function as the tolerance for the error, and is supposed to be returned as the value of error. The function `OPA` is supposed to return the degree of the approximation polynomial.

**Note:** a constant `Max_n` is defined so that if the total error is still not small enough when *n* = `Max_n`, simply output the result obtained when *n* = `Max_n`.

### Sample program of judge:

```c
#include <stdio.h>
#include <math.h>

#define MAX_m 200
#define MAX_n 5

double f1(double x)
{
    return sin(x);
}

double f2(double x)
{
    return exp(x);
}

int OPA( double (*f)(double t), int m, double x[], double w[], double c[], double *eps );

void print_results( int n, double c[], double eps)
{    
    int i;

    printf("%d\n", n);
    for (i=0; i<=n; i++)
        printf("%12.4e ", c[i]);
    printf("\n");
    printf("error = %9.2e\n", eps);
    printf("\n");
}

int main()
{
    int m, i, n;
    double x[MAX_m], w[MAX_m], c[MAX_n+1], eps;

    m = 90;
    for (i=0; i<m; i++) {
        x[i] = 3.1415926535897932 * (double)(i+1) / 180.0;
        w[i] = 1.0;
    }
    eps = 0.001;
    n = OPA(f1, m, x, w, c, &eps);
    print_results(n, c, eps);

    m = 200;
    for (i=0; i<m; i++) {
        x[i] = 0.01*(double)i;
        w[i] = 1.0;
    }
    eps = 0.001;
    n = OPA(f2, m, x, w, c, &eps);
    print_results(n, c, eps);

    return 0;
}

/* Your function will be put here */
```

### Sample Output:

```out
3
 -2.5301e-03   1.0287e+00  -7.2279e-02  -1.1287e-01 
error =  6.33e-05

4
  1.0025e+00   9.6180e-01   6.2900e-01   7.0907e-03   1.1792e-01 
error =  1.62e-04
```