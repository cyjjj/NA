# 6-1 Numerical Summation of a Series (40 分)

Produce a table of the values of the series

$$ \phi(x) = \sum_{k=1}^infty \frac{1}{k(k+x)} \text {……(1)} $$

for the 3001 values of *x*, *x* = 0.0, 0.1, 0.2, ..., 300.00. All entries of the table must have an absolute error less than $10^{−10}$. This problem is based on a problem from Hamming (1962), when mainframes were very slow by today's microcomputer standards.

### Format of function:

```c
void Series_Sum( double sum[] );
```

where `double sum[]` is an array of 3001 entries, each contains a value of *ϕ*(*x*) for *x* = 0.0, 0.1, 0.2, ..., 300.00.

### Sample program of judge:

```c
#include <stdio.h>

void Series_Sum( double sum[] );

int main()
{
    int i;
    double x, sum[3001];

    Series_Sum( sum );

    x = 0.0;
    for (i=0; i<3001; i++)
        printf("%6.2f %16.12f\n", x + (double)i * 0.10, sum[i]);

    return 0;
}

/* Your function will be put here */
```

### Sample Output:

```out
0.00   1.644934066848
0.10   1.534607244904
...
1.00   1.000000000000
...
2.00   0.750000000000
...
300.00   0.020942212934
```

### Hint:

The problem with summing the sequence in equation (1) is that too many terms may be required to complete the summation in the given time. Additionally, if enough terms were to be summed, roundoff would render any typical double precision computation useless for the desired precision.

To improve the convergence of the summation process note that

$$ \frac{1}{k(k+1)} = \frac{1}{k} - \frac{1}{k+1} \text {……(2)} $$

which implies *ϕ*(1)=1.0. One can then produce a series for *ϕ*(*x*)−*ϕ*(1) which converges faster than the original series. This series not only converges much faster, it also reduces roundoff loss.

This process of finding a faster converging series may be repeated again on the second series to produce a third sequence, which converges even more rapidly than the second.

The following equation is helpful in determining how may items are required in summing the series above.

$$ \sum__{k=n}^infty \frac{1}{k^r}  < \int_{n-1}^infty {\frac{1}{x^r}} \text {for k > a and r $\geq$ 1 ……(3)} $$