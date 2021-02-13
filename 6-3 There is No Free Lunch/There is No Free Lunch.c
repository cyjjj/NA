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
void Price( int n, double p[] )
{
    //pi = 2ci + 0.5ci-1 + 0.5ci+1
    //Ax=p,循环三对角矩阵
	//追赶法,A=LUD. Lu=p, Uv=u, Dx=v
	
    //分解, A=LUD
    double a[n-1], b[n];//L
    double q[n-2];//U
    double t[n-1], s;//D
    double r[n-1];
    int i;
    
    b[0] = 2;
	q[0] = 0.5 / b[0];
	r[0] = 0.5 / b[0];
    for(i=1;i<n-2;i++){
		b[i] = 2 - 0.5 * q[i-1];
		q[i] = 0.5 / b[i];
		r[i] = - 0.5 * r[i-1] / b[i];
	}
    b[n-2] = 2 - 0.5 * q[n-3];
    r[n-2] = (0.5 - 0.5 * r[n-3]) / b[n-2];
    b[n-1] = 2 - 0.5 * r[n-2];
    s = 0.5 / b[n-1];

    t[n-2] = r[n-2];
    for(i=n-3;i>=0;i--){
    	t[i] = r[i] - q[i] * t[i+1];
	}
	
	//追, Lu=p
	double u[n];
	u[0] = p[0] / b[0];
	for(i=1;i<n;i++){
		u[i] = (p[i] - 0.5 * u[i-1]) / b[i];
	}
	
	//赶, Uv=u, Dx=v, x存回p[] 
	double v[n];
	v[n-1] = u[n-1];
	v[n-2] = u[n-2];
	for(i=n-3;i>=0;i--){
		v[i] = u[i] - q[i] * v[i+1];
	}
	
	p[n-1] = (v[n-1] - s * v[0]) / (1 - s * t[0]);
	for(i=0;i<n-1;i++){
		p[i] = v[i] - t[i] * p[n-1];
	}
}
