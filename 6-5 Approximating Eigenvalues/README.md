# 6-5 Approximating Eigenvalues (40 分)

Approximate an eigenvalue and an associated eigenvector of a given *n*×*n* matrix *A* near a given value *p* and a nonzero vector $\vec{x}=(x_1,\cdots,x_n)^T$.

### Format of function:

```c
int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN);
```

where `int n` is the size of the matrix of which the entries are in the array `double a[][MAX_SIZE]` and `MAX_SIZE` is a constant defined by the judge; `double *lambda` is passed into the function as an initial approximation *p* of the eigenvalue and is supposed to be returned as a more accurate eigenvalue; `double v[]` is passed into the function as the initial vector $\vec{x}$ and is supposed to be returned as the associated eigenvector with *unit* $\parallel \cdot \parallel_\infty$ norm; `double TOL` is the tolerance for the eigenvalue; and finally `int MAXN` is the maximum number of iterations.

The function must return:

- 1 if there is a solution;
- 0 if maximum number of iterations exceeded;
- −1 if *p* is just the accurate eigenvalue.

### Sample program of judge:

```c
#include <stdio.h>

#define MAX_SIZE 10

int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN);

int main()
{
    int n, MAXN, m, i, j, k;
    double a[MAX_SIZE][MAX_SIZE], v[MAX_SIZE];
    double lambda, TOL;

    scanf("%d", &n);
    for (i=0; i<n; i++) 
        for (j=0; j<n; j++) 
            scanf("%lf", &a[i][j]);
    scanf("%lf %d", &TOL, &MAXN);
    scanf("%d", &m);
    for (i=0; i<m; i++) {
        scanf("%lf", &lambda);
        for (j=0; j<n; j++)
            scanf("%lf", &v[j]);
        switch (EigenV(n, a, &lambda, v, TOL, MAXN)) {
            case -1: 
                printf("%12.8f is an eigenvalue.\n", lambda );
                break;
            case 0:
                printf("Maximum number of iterations exceeded.\n");
                break;
            case 1:
                printf("%12.8f\n", lambda );
                for (k=0; k<n; k++)
                    printf("%12.8f ", v[k]);
                printf("\n");
                break;
        }
    }

    return 0;
}

/* Your function will be put here */
```

### Sample Input 1:

```in
3
1 2 3
2 3 4
3 4 5
0.0000000001 1000
1
-0.6 1 1 1
```

### Sample Output 1:

```out
-0.62347538
  1.00000000   0.17206558  -0.65586885 
```

### Sample Input 2:

```
2
0 1
1 0
0.0000000001 10
2
1.0 1 1
100.0 1 0
```

### Sample Output 2:

```
  1.00000000 is an eigenvalue.
Maximum number of iterations exceeded.
```

### 35分/40分

| 提交时间            | 状态     | 分数 | 题目   | 编译器  | 耗时 | 用户 |
| ------------------- | -------- | ---- | ------ | ------- | ---- | ---- |
| 2019/12/05 20:37:37 | 部分正确 | 35   | 函数题 | C (gcc) | 3 ms | *    |

| 测试点 | 结果     | 分数 | 耗时 | 内存   |
| ------ | -------- | ---- | ---- | ------ |
| 0      | 答案正确 | 15   | 3 ms | 256 KB |
| 1      | 答案正确 | 10   | 3 ms | 256 KB |
| 2      | 答案正确 | 10   | 3 ms | 256 KB |
| 3      | 答案错误 | 0    | 3 ms | 256 KB |