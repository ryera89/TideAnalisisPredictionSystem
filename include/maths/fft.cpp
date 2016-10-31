#include "fft.h"

void four1(double *data, const int n, const int isign){
    int nn,mmax,m,j,istep,i;
    double wtemp,wr,wpr,wpi,wi,theta,tempr,tempi;
    if (n<2 || n&(n-1)) throw("n must be power of 2 in four1");
    nn = n << 1;
    j = 1;
    for (i=1;i<nn;i+=2) {
       if (j > i) {
         std::swap(data[j-1],data[i-1]);      //Exchange the two complex numbers.
         std::swap(data[j],data[i]);
       }
       m=n;
       while (m >= 2 && j > m) {
          j -= m;
          m >>= 1;
      }
      j += m;
    }
//Here begins the Danielson-Lanczos section of the routine.
    mmax=2;
   while (nn > mmax) {                  //Outer loop executed log2 n times.
       istep = mmax << 1;
       theta = isign*(6.28318530717959/mmax);    //Initialize the trigonometric recurrence.
       wtemp = std::sin(0.5*theta);
       wpr = -2.0*wtemp*wtemp;
       wpi = std::sin(theta);
       wr = 1.0;
       wi = 0.0;
       for (m=1;m<mmax;m+=2) {                 //Here are the two nested inner loops.
            for (i = m;i <= nn;i += istep) {
                j = i+mmax;                      //This is the Danielson-Lanczos  formula:
                tempr = wr*data[j-1]-wi*data[j];
                tempi = wr*data[j]+wi*data[j-1];
                data[j-1] = data[i-1]-tempr;
                data[j] = data[i]-tempi;
                data[i-1] += tempr;
                data[i] += tempi;
             }
            wr = (wtemp=wr)*wpr-wi*wpi+wr;                  //Trigonometric recurrence.
            wi = wi*wpr+wtemp*wpi+wi;
       }
       mmax=istep;
   }
}
