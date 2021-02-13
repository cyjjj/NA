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
double c1[MAXN], c2[MAXN];

double GetFuc(int n, double c[], double x)
//计算函数值
{
    double result = 0;
    int i;
    for(i=n;i>=0;i--)
        result = result * x + c[i];
    return result;
}

void Derivative(int n, double c1[], double c[])
//求导
{
    int i;
    for(i=n;i>0;i--)
        c1[i-1] = i * c[i];
}

int findRoot(int n, double c[], double begin, double end, double p0, double *p, double *err, double EPS)
{
    int flag = 0;//flag=0 不能收敛；flag=1 能收敛
    int i;
    for(i = 0; i < 1000; i++)//最大迭代次数
    {
        double f = GetFuc(n, c , p0);//f(p0)
        if(fabs(f) < ZERO)
		{
			flag = 1;
			break;
		}
        double f1 = GetFuc(n-1, c1, p0);//f'(p0)
        double f2 = GetFuc(n-2, c2, p0);//f''(p0)
        double dino = f1*f1 - f*f2;//f'(p0)*f'(p0) - f(p0)*f''(p0)
		if (fabs(dino) < ZERO)
		{
			flag = 0;
			break;
		}
        *p = p0 - f*f1/dino;//p=p0-f(p0)/(f'(p0)*f'(p0)-f(p0)*f''(p0))
        if (*p > end || *p < begin)//越界
		{
			flag = 0;
			break;
		}
        if (fabs(p0-*p) < EPS)//收敛
		{
			flag = 1;
			break;
		}
        p0 = *p;
    }
    double fp = GetFuc(n, c, *p);
    *err = fabs(fp);
    return flag;
}

double Polynomial_Root(int n, double c[], double a, double b, double EPS)
{
    if(b < a)
    {
        double temp = a;
        a = b;
        b = temp;
    }//确保a<b
    extern double c1[MAXN], c2[MAXN];
    Derivative(n, c1, c);//f'(x)
    Derivative(n-1, c2, c1);//f''(x)

    int step = 3;
    double interval = (b - a) / step;
    double p;//牛顿法传回来的根
	double minErr = 999;//最小误差
	double root;//最终得到的根
	int i;
    for(i = 0; i <= step; i++)
    {
        double p0 = a + interval * i;
		double err;
		if (findRoot(n, c, a, b, p0, &p, &err, EPS) && err < minErr)
        //如果牛顿法最后收敛了并且误差小于当前的最小误差
		{
			minErr = err;
			root = p;
		}
    }
	return root;
}
