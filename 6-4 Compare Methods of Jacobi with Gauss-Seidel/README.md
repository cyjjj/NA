# 6-4 Compare Methods of Jacobi with Gauss-Seidel (50 分)

Use Jacobi and Gauss-Seidel methods to solve a given *n*×*n* linear system $A\vec{x}=\vec{b}$ with an initial approximation $\vec{x}^{(0)}$.

**Note:** When checking each $a_{ii}$, first scan *downward* for the entry with maximum absolute value ($a_{ii}$ included). If that entry is non-zero, *swap* it to the diagonal. Otherwise if that entry is zero, scan *upward* for the entry with maximum absolute value. If that entry is non-zero, then *add* that row to the $i$-th row.

### Format of functions:

```c
int Jacobi( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );

int Gauss_Seidel( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );
```

where `int n` is the size of the matrix of which the entries are in the array `double a[][MAX_SIZE]` and `MAX_SIZE` is a constant defined by the judge; `double b[]` is for $\vec{b}$, `double x[]` passes in the initial approximation  $\vec{x}^{(0)}$and return the solution $\vec{x}$; `double TOL` is the tolerance for $\parallel{\vec{x}^{(k+1)}-\vec{x}^{(k)}}\parallel_{\infty}$; and finally `int MAXN` is the maximum number of iterations.

The function must return:

- *k* if there is a solution found after *k* iterations;
- 0 if maximum number of iterations exceeded;
- 1 if the matrix has a zero column and hence no unique solution exists;
- 2 if there is no convergence, that is, there is an entry of $\vec{x}^{(K)}$ that is out of the range [`-bound`, `bound`] where `bound` is a constant defined by the judge.

### Sample program of judge:

```c
#include <stdio.h>
#include <math.h>

#define MAX_SIZE 10
#define bound pow(2, 127)
#define ZERO 1e-9 /* X is considered to be 0 if |X|<ZERO */

enum bool { false = 0, true = 1 };
#define bool enum bool

int Jacobi( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );

int Gauss_Seidel( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );

int main()
{
    int n, MAXN, i, j, k;
    double a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE], x[MAX_SIZE];
    double TOL;

    scanf("%d", &n);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++)
            scanf("%lf", &a[i][j]);
        scanf("%lf", &b[i]);
    }
    scanf("%lf %d", &TOL, &MAXN);

    printf("Result of Jacobi method:\n");
    for ( i=0; i<n; i++ )
        x[i] = 0.0;
    k = Jacobi( n, a, b, x, TOL, MAXN );
    switch ( k ) {
        case -2:
            printf("No convergence.\n");
            break;
        case -1: 
            printf("Matrix has a zero column.  No unique solution exists.\n");
            break;
        case 0:
            printf("Maximum number of iterations exceeded.\n");
            break;
        default:
            printf("no_iteration = %d\n", k);
            for ( j=0; j<n; j++ )
                printf("%.8f\n", x[j]);
            break;
    }
    printf("Result of Gauss-Seidel method:\n");
    for ( i=0; i<n; i++ )
        x[i] = 0.0;
    k = Gauss_Seidel( n, a, b, x, TOL, MAXN );
    switch ( k ) {
        case -2:
            printf("No convergence.\n");
            break;
        case -1: 
            printf("Matrix has a zero column.  No unique solution exists.\n");
            break;
        case 0:
            printf("Maximum number of iterations exceeded.\n");
            break;
        default:
            printf("no_iteration = %d\n", k);
            for ( j=0; j<n; j++ )
                printf("%.8f\n", x[j]);
            break;
    }

    return 0;
}

/* Your function will be put here */
```

### Sample Input 1:

```in
3
2    -1    1    -1
2    2    2    4
-1    -1    2    -5
0.000000001 1000
```

### Sample Output 1:

```out
Result of Jacobi method:
No convergence.
Result of Gauss-Seidel method:
no_iteration = 37
1.00000000
2.00000000
-1.00000000
```

### Sample Input 2:

```
3
1    2    -2    7
1    1    1    2
2    2    1    5
0.000000001 1000
```

### Sample Output 2:

```
Result of Jacobi method:
no_iteration = 232
1.00000000
2.00000000
-1.00000000
Result of Gauss-Seidel method:
No convergence.
```

### Sample Input 3:

```
5
2 1 0 0 0 1
1 2 1 0 0 1
0 1 2 1 0 1
0 0 1 2 1 1
0 0 0 1 2 1
0.000000001 100
```

### Sample Output 3:

```
Result of Jacobi method:
Maximum number of iterations exceeded.
Result of Gauss-Seidel method:
no_iteration = 65
0.50000000
0.00000000
0.50000000
0.00000000
0.50000000
```