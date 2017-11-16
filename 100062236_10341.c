#include<stdio.h>
#include<math.h>

int p, q, r, s, t, u;

double equation(double x){
    return p*exp(-x)+q*sin(x)+r*cos(x)+s*tan(x)+t*x*x+u;
}

int main(){
    int flag;
    double upper, lower, mid, fm, fu, fl;

    while(scanf("%d%d%d%d%d%d", &p, &q, &r, &s, &t, &u)!=EOF){
        upper=1;
        lower=0;
        flag=0;
        while(upper>lower+1e-7){
            mid=(upper+lower)/2;
            fm=equation(mid);
            fu=equation(upper);
            fl=equation(lower);
            if(fu*fl>0){
                flag=1;
                printf("No solution\n");
                break;
            }
            if(fm*fl<=0) upper=mid;
            else lower=mid;
        }
        if(!flag)
            printf("%.4lf\n", upper);
    }
    return 0;
}
