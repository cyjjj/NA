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
double fabs(double x)
{
    return x > 0 ? x : -1 * x;
}

/*
Return Value:
1---if there is a solution
0---if maximum number of iterations exceeded
-1--if p is just the accurate eigenvalue
*/
int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN)
{
    //whether p is just the accurate eigenvalue
    double sum = 0;
    int i = 0, j;
    while(1){
        sum = 0;
        for (j=0;j<n;j++)
            sum += a[i][j] * v[j];
        if (sum == ((*lambda) * v[i])){
            i++;
            if (i == n)
                return -1;//p is just the accurate eigenvalue
            else
                continue;
        }else
            break;
    }
    
    //Power Method
    int index = 0;
    int k = 1;
    double x[n], vm;

    //normalize v
    index = 0;
    for(i=0;i<n;i++){
        if(fabs(v[i]) > fabs(v[index]))
            index = i;
    }
    vm = fabs(v[index]);
    for(i=0;i<n;i++)
        v[i] /= vm;
    
    while(k <= MAXN){
        //x = Av
        for(i=0;i<n;i++){
        	x[i] = 0;
            for(j=0;j<n;j++)
                x[i] += a[j][i] * v[j];
        }

        *lambda = x[index];
        index = 0;
        for(i=0;i<n;i++){
            if(fabs(x[i]) > fabs(x[index]))
            index = i;
        }
        if(x[index] == 0) return 1;

        double err = 0, temp = 0;
        for(i=0;i<n;i++){
            temp = fabs(v[i] - x[i] / x[index]);
            if(temp > err) err = temp; 
            v[i] = x[i] / x[index];
        }
        if(err < TOL) return 1;//there is a solution
        k++; 
    }
    return 0;//maximum number of iterations exceeded
}
