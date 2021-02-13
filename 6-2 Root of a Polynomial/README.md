# 6-2 Root of a Polynomial (50 分)

A polynomial of degree *n* has the common form as $p(x)=c_{n}x^{n} + c_{n-1}x^{n-1} + \cdots + c_{1}x + c_0 $. Your task is to write a function to find a root of a given polynomial in a given interval.

### Format of function:

```c
double Polynomial_Root(int n, double c[], double a, double b, double EPS);
```

where `int n` is the degree of the polynomial; `double c[]` is an array of `n`+1 coefficients $c_{n}$, $c_{n-1}$, ... ,$c_{1}$ and $c_{0}$ of the given polynomial; `double a` and `b` are the two end-points of the given interval; and `double EPS` is the accuracy of the root.

The function must return the root.

**Note:** *It is guaranteed that a unique real number \*r* exists in the given interval such that $p(r)=0$.

### Sample program of judge:

```c
#include <stdio.h>
#include <math.h>

#define ZERO 1e-13 /* X is considered to be 0 if |X|<ZERO */
#define MAXN 11    /* Max Polynomial Degree + 1 */

double Polynomial_Root(int n, double c[], double a, double b, double EPS);

int main()
{
    int n;
    double c[MAXN], a, b;
    double EPS = 0.00005;
    int i;

    scanf("%d", &n);
    for (i=n; i>=0; i--) 
        scanf("%lf", &c[i]);
    scanf("%lf %lf", &a, &b);
    printf("%.4f\n", Polynomial_Root(n, c, a, b, EPS));

    return 0;
}

/* Your function will be put here */
```

### Sample Input:

```in
2 1 1.5 -1
0 2
```

### Sample Output:

```out
0.5000
```