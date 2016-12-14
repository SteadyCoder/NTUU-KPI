/* amo_lab4.cpp */

#include <iostream>
#include <math.h>
#include "CTR.h"

using namespace std;

double f(double x)
{
	return (exp(x) - (x*x)/2 - x);
}

int main()
{
   cout.precision(12);

   double I = exp(1.0) - (1.0/6.0) - (1.0/2.0) - 1.0; //exact value of definite integral
   double M2 = exp(1.0) - 1.0; //M2 = max(f_2(x)), x E [0;1], f_2(x)=exp(x) - 1
   double eps = 0.01;
   double delta[10];
   double h;
   double I_h;
   double a=0,b=1;
   int n;

   cout<<"Table 1"<<endl;
   cout<<"--------------------------------------------------------------------"<<endl;
   cout<<"     eps |                  h |             I |              delta |"<<endl;
   cout<<"--------------------------------------------------------------------"<<endl;
   
   int i1=0;
   
   for (int i = 0;i<4;++i){
   	
	h = sqrt((12*eps)/(M2*(b - a)));
	n = (int)((b - a) / h);
	//if (n%2 == 0) n = n + 2;
	//else n = n + 1;

	n = n + 2;

	h = (b - a) / n;
     
   I_h = CTR(f,a,b,h);  

   delta[i1] = abs(I_h - I);
   ++i1;

   cout.width(8);
   cout<<eps<<" |";
   cout.width(19);
   cout<<h<<" |";
   cout.width(14);
   cout<<I_h<<" |";
   cout.width(19);
   cout<<delta[i1-1]<<" |"<<endl;

   eps=eps*0.01;
   //if ((eps==1e-005)||(eps==1e-008)) eps=eps*0.01;
   if ((eps<1e-007)&&(eps>1e-009)) eps=eps*0.01;
   }
   cout<<endl;
  
   cout<<"Table 2"<<endl;
   cout<<"-------------------------------------------------------------------------------"<<endl;
   cout<<"          old delta |                  h |             I |          new delta |"<<endl;
   cout<<"-------------------------------------------------------------------------------"<<endl;
   
   for (int i=0; i<i1; ++i){   
   I_h = CTR_RC(f,a,b,delta[i],&h);
   
   cout.width(19);
   cout<<delta[i]<<" |";
   cout.width(19);
   cout<<h<<" |";
   cout.width(14);
   cout<<I_h<<" |";
   cout.width(19);
   cout<<abs(I - I_h)<<" |"<<endl;
   }

	return 0;
}
