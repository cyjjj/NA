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
int check( int n, double a[][MAX_SIZE], double b[] )
{
	int i, j, maxrow;
	double max;
	
	for (i=0;i<n;i++){
		//scan downward
		max = fabs(a[i][i]);
		maxrow = i;
		for (j=i;j<n;j++){
			if (fabs(a[j][i]) > max)
                maxrow = j;
		}
		
		//if that entry is zero
		if (a[maxrow][i] < ZERO){
			//scan upward
			max = fabs(a[i][i]);
			maxrow = i;
			for (j=i;j>=0;j--){
                if (fabs(a[j][i]) > max)
                    maxrow = j;
            }
			//all are the 0
            if (a[maxrow][i] < ZERO)
                return -1;
            else{
            	//add that row to the i-th row
                for (j=0;j<n;j++){
                    a[i][j] += a[maxrow][j];
                }
                b[j] += b[maxrow];
            }
        }
		
		//If that entry is non-zero
		else{
			//swap it to the diagonal
			double temp;
			for (j=0;j<n;j++)
            {
                temp = a[i][j];
                a[i][j] = a[maxrow][j];
                a[maxrow][j] = temp;
            }
            temp = b[i];
            b[i] = b[maxrow];
            b[maxrow] = temp;
		}
	}
}

/*
return value:
k---if there is a solution found after k iterations;
0---if maximum number of iterations exceeded;
-1---if the matrix has a zero column and hence no unique solution exists;
-2---if there is no convergence, that is, there is an entry of x(K)that is out of the range
*/
int Jacobi( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN )
{
	int i, j, maxrow, iterations;
	double max, sum, atemp[n][MAX_SIZE], xtemp[n];
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
		    atemp[i][j] = a[i][j];
	}
	
	//check each a[i][i]
	int checking = check(n, atemp, b);
	if(checking == -1)
	    return -1;//the matrix has a zero column
	
	iterations = 1;
	while(iterations <= MAXN){
	    //Step 3
		for(i=0;i<n;i++){
			sum = 0;
			for(j=0;j<n;j++){
				if(j == i) continue;
				sum += atemp[i][j] * x[j];
			}
			xtemp[i] = (b[i] - sum) / atemp[i][i];
		}
	
	    //Step 4
		double maxsub = fabs(xtemp[0] - x[0]);
		for(i=1;i<n;i++){
		    if(fabs(xtemp[i] - x[i]) > maxsub)
			    maxsub = fabs(xtemp[i] - x[i]);
		}
		
		for(i=0;i<n;i++){
			if(fabs(xtemp[i]) > bound)
			    return -2;//out of the rang. there is no convergence
			x[i] = xtemp[i];
		}
		
		if(maxsub < TOL)
		    return iterations;//there is a solution found
		iterations++;
	}
	return 0;//maximum number of iterations exceeded
}

int Gauss_Seidel( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN )
{
	int i, j, maxrow, iterations;
	double max, sum1, sum2, atemp[n][MAX_SIZE], xo[n];
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
		    atemp[i][j] = a[i][j];
	}
	for(i=0;i<n;i++){
		xo[i] = x[i];
	}
	
	//check each a[i][i]
	int checking = check(n, atemp, b);
	if(checking == -1)
	    return -1;//the matrix has a zero column
	
	iterations = 1;
	while(iterations <= MAXN){
	    //Step 3
		for(i=0;i<n;i++){
			sum1 = 0;
			sum2 = 0;
			for(j=0;j<i;j++)
				sum1 += atemp[i][j] * x[j];
			for(j=i+1;j<n;j++)
				sum2 += a[i][j] * x[j];
			x[i]= (b[i] -sum1 - sum2) / a[i][i];
		}
	
	    //Step 4
		double maxsub = fabs(xo[0] - x[0]);
		for(i=1;i<n;i++){
		    if(fabs(xo[i] - x[i]) > maxsub)
			    maxsub = fabs(xo[i] - x[i]);
		}
		
		for(i=0;i<n;i++){
			if(fabs(x[i]) > bound)
			    return -2;//out of the rang. there is no convergence
			xo[i] = x[i];
		}
		
		if(maxsub < TOL)
		    return iterations;//there is a solution found
		iterations++;
	}
	return 0;//maximum number of iterations exceeded
}
