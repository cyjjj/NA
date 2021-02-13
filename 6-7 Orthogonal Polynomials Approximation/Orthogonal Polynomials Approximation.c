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
double fy(double x[], double f[], double y[], int m, int poly);//(¦×, y)
double xff(double x[], double f[], int m, int poly);//(x¦×0, ¦×0)
double xfft(double x[], double f[], double ft[], int m, int poly);//(x¦×1, ¦×0) 
double ff(double x[], double f[], int m, int poly);//(¦×, ¦×)
double yy(double y[], int m);//(y,y)
void restore(double a, double c[], double f[], int poly);

int OPA( double (*f)(double t), int m, double x[], double w[], double c[], double *eps )
{
	int i;
	double err = 0;
	double y[MAX_m], b[MAX_n+1], a[MAX_n+1], ct[MAX_n+1];
	
	for(i=0;i<MAX_n+1;i++)   
        c[i] = 0;   
   
    for(i=0;i<m;i++)   
        y[i] = f(x[i]);
     
    double fie[MAX_n+1][MAX_n+2]={(0,0)}; 
	//¦×0(x)=1   
    fie[0][0]=1;
    //a0 = (¦×0, y)/(¦×0, ¦×0)
    a[0]= fy(x,fie[0],y,m,0) / ff(x,fie[0],m,0);
	//P(x) = a0 * ¦×0(x)
    restore(a[0],c,fie[0],0);   
    //err = (y, y) - a0(¦×0, y)
    err = yy(y,m) - a[0] * fy(x,fie[0],y,m,0);
   
	//B1= (x¦×0, ¦×0)/(¦×0, ¦×0)  
    b[1] = xff(x,fie[0],m,0) / ff(x,fie[0],m,0); 
	//¦×1(x) = x - B1; 
    fie[1][1] = 1;   
    fie[1][0] = - b[1];   
    //a1 = (¦×1, y)/(¦×1, ¦×1)
    a[1] = fy(x,fie[1],y,m,1) / ff(x,fie[1],m,1);
    //P(x) += a1 * ¦×1(x);
    restore(a[1],c,fie[1],1);   
    //err -= a1(¦×1, y)   
    err -= a[1] * fy(x,fie[1],y,m,1);
   
    int k=1;   
   
    while ((k < MAX_n) && (fabs(err) >= *eps))   
    {     
        k++;
		//Bk = (x¦×1, ¦×1)/(¦×1, ¦×1)   
        b[k]= xff(x,fie[k-1],m,k-1) / ff(x,fie[k-1],m,k-1);   
        //Ck = (x¦×1, ¦×0)/(¦×0, ¦×0)  
        ct[k] = xfft(x,fie[k-1],fie[k-2],m,k-2) / ff(x,fie[k-2],m,k-2);   
        //¦×2(x) = (x - Bk) * ¦×1(x) - Ck * ¦×0(x);  
        for(i=0;i<MAX_n+1;i++)   
        {   
            fie[k][i+1] = fie[k-1][i];   
        }   
        for (i=0;i<MAX_n+1;i++)   
        {   
            fie[k][i] -= (b[k] * fie[k-1][i] + ct[k] * fie[k-2][i]);   
        } 
		//ak = (¦×2, y)/(¦×2, ¦×2)   
        a[k]= fy(x,fie[k],y,m,k) / ff(x,fie[k],m,k);
        //P(x) += a1 * ¦×1(x);
        restore(a[k],c,fie[k],k);
		//err -= ak(¦×2, y)
        err -= a[k] * fy(x,fie[k],y,m,k);   
    }   
    *eps = err;   
    return k;  
}

double fy(double x[], double f[], double y[], int m, int poly)   
{   
    int i,j;   
    double sum = 0,temp;   
       
    for(i=0;i<m;i++)   
    {   
        temp = 0;   
        for(j=0;j<=poly;j++)   
        {   
            temp += f[j] * pow(x[i],j);   
        }   
        sum += temp * y[i];   
    }   
    return sum;   
}   
   
double xff(double x[], double f[], int m, int poly)   
{   
    int i,j;   
    double sum=0,temp;   
   
    for(i=0;i<m;i++)   
    {   
        temp = 0;   
        for(j=0;j<=poly;j++)   
        {   
            temp += f[j] * pow(x[i],j);   
        }   
        sum += x[i] * temp * temp;   
    }   
    return sum;   
}   
   
double xfft(double x[], double f[], double ft[], int m, int poly)   
{   
    int i,j;   
    double sum = 0,temp1,temp2;   
   
    for(i=0;i<m;i++)   
    {   
        temp1 = temp2 = 0;   
        for(j=0;j<=poly+1;j++)   
        {   
            temp1 += f[j] * pow(x[i],j);   
        }   
        for(j=0;j<=poly;j++)   
        {   
            temp2 += ft[j] * pow(x[i],j);   
        }   
        sum += x[i]*temp1*temp2;   
    }   
    return sum;   
}   
   
   
double ff(double x[], double f[], int m, int poly)   
{   
    int i,j;   
    double sum = 0,temp;   
   
    for(i=0;i<m;i++)   
    {   
        temp = 0;   
        for(j=0;j<=poly;j++)   
        {   
            temp += f[j] * pow(x[i],j);   
        }   
        sum += temp * temp;   
    }   
    return sum;   
}   
   
double yy(double y[], int m)   
{   
    int i;   
    double sum = 0;   
   
    for(i=0;i<m;i++)   
    {   
        sum += y[i] * y[i];   
    }   
    return sum;   
}   
   
   
void restore(double a, double c[], double f[], int poly)   
{   
    int i;   
    for(i=0;i<=poly;i++)   
    {   
        c[i] += a * f[i];
    }   
}
