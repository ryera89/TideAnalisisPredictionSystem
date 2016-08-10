#include "common_math_algorithms.h"
luint gcd(luint m,luint n){
    while (luint r = m%n){
        m=n;
        n=r;
    }
    return n;
}
luint gcd_opt(luint m,luint n){
    while (luint r=m%n){
        if (!(m=n%r)) return r;
        if (!(n=r%m)) return m;
    }
    return n;
}
luint factorial(const int &n){
    luint r=1;
    for (int i=2;i<=std::abs(n);++i){
        r*=i;
    }
    return r;
}
int* Euclid_Extended(int m, int n){
    int c=m;
    int d=n;
    int a=0;
    int a1=1;
    int b=1;
    int b1=0;
    while (int r=c%d){
        int q=c/d;
        c=d;
        d=r;
        int t=a1;
        a1=a;
        a=t-q*a;
        t=b1;
        b1=b;
        b=t-q*b;
    }
    int* w=new int;
    w[0]=a;
    w[1]=b;
    w[2]=d;
    return w;
}
