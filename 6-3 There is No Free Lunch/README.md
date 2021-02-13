# 6-3 There is No Free Lunch (40 分)

One day, CYLL found an interesting piece of commercial from newspaper: the Cyber-restaurant was offering a kind of "Lunch Special" which was said that one could "buy one get two for free". That is, if you buy one of the dishes on their menu, denoted by $d_{i}$ with price $p_{i}$, you may get the two neighboring dishes $d_{i-1}$ and $d_{i+1}$ for free! If you pick up *d*1, then you may get $d_{2}$ and the last one $d_{n}$ for free, and if you choose the last one $d_{n}$, you may get $d_{n-1}$ and $d_{1}$ for free.

However, after investigation CYLL realized that there was no free lunch at all. The price $p_{i}$ of the $i$-th dish was actually calculated by adding up twice the cost $c_{i}$ of the dish and half of the costs of the two "free" dishes. Now given all the prices on the menu, you are asked to help CYLL find the cost of each of the dishes.

### Format of function:

```c++
void Price( int n, double p[] );
```

where `int n` satisfies that 2< `n` ≤10000; `double p[]` is passed into the function as an array of prices $p_i$ and then will be returned storing the costs of the dishes.

### Sample program of judge:

```c
#include <stdio.h>

#define Max_size 10000 /* max number of dishes */

void Price( int n, double p[] );

int main()
{
    int n, i;
    double p[Max_size];

    scanf("%d", &n);
    for (i=0; i<n; i++) 
        scanf("%lf", &p[i]);
    Price(n, p);
    for (i=0; i<n; i++)
        printf("%.2f ", p[i]);
    printf("\n");

    return 0;
}

/* Your function will be put here */
```

### Sample Input:

```in
12 23.64 17.39 12.77 16.62 10.67 14.85 12.68 26.90 28.30 15.59 37.99 23.18
```

### Sample Output:

```out
9.20 5.58 3.24 7.00 1.99 6.36 2.25 10.01 11.52 0.50 17.65 4.88 
```