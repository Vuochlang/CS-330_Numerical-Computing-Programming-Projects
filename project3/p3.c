////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Name: Vuochlang Chang												      //
//	Class: CS330 - Numerical Computing, FALL 2020									      //
//	Programming Project 3: implement four numerical methods for approximating denite integrals and use these to         //
//			estimate the value of u: By divvying up the interval of integration into smaller pieces 	      //
//	Instruction to run the file: I have included a Makefile, so just run make and it will compile. Then the executable    //
//					code can be called as "./main" and the output will print to stdout		      //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288 /* pi */
#endif

void print();
long double trapezoid(long double, long double, int);
long double simpson13(long double, long double, int);
long double boole(long double, long double, int);
long double simpson38(long double, long double, int);
long double f(long double);

int main(){
	long double a=0;//lower limit
	long double b=1;//upper limit 
	long double Trap[17]={0};//error from trapezoid function according to each n value
	long double Simp13[17]={0};//error from simpson 1/3 function 
	long double Simp38[17]={0};//error from simpson 3/8 function
	long double Boole[17]={0};// error from boole function 
	int n[17];

	for(int i=0; i<17; i++){//initialize each value of n=12*2^i, where i=0,1,2,...16
		n[i]=12*pow(2,i);
	}
	for(int i=0; i<17; i++){//loop for using each value of n to go through each function
				//and get the differences between each function and M_PI
		Trap[i]=fabs(M_PI-trapezoid(a,b,n[i]));
		Simp13[i]=fabs(M_PI-simpson13(a,b,n[i]));
		Boole[i]=fabs(M_PI-boole(a,b,n[i]));
		Simp38[i]=fabs(M_PI-simpson38(a,b,n[i]));
	}

	print();//print the top table contents
	for(int i=0; i<17; i++){
		printf("|%d\t|\t%0.10Le\t|\t%0.10Le\t|\t%0.10Le\t|\t%0.10Le\t|\n",n[i],Trap[i],Simp13[i],Simp38[i],Boole[i]);
	}	
return 0;
}

long double boole(long double a, long double b, int n){
	long double result, S1, S2, S3, x1, x2, x3;
	long double h=(b-a)/n;
	S1=S2=S3=0;
	for(int i=1; i<n; i++){
		if(i%2==1){
			x1=a+(h*(i));
			S1=S1+f(x1);
		}
		else{
			if(i%4==0){
				x3=a+(h*i);
				S3=S3+f(x3);
			}
			else{
				x2=a+(h*i);
				S2=S2+f(x2);
			}
		}
	}
	result=((2*h)/45)*((7*(f(a)+f(b)))+(32*S1)+(12*S2)+(14*S3));
	return result;
}

long double simpson38(long double a, long double b, int n){
	long double result, S1, S2, x1, x2;
	long double h=(b-a)/n;
	S1=S2=0;
	for(int i=1; i<n; i++){
		if(i%3==0){
			x1=a+(h*i);
			S1=S1+f(x1);
		}
		else{
			x2=a+(h*i);
			S2=S2+f(x2);
		}
	}
	result=((3*h)/8)*(f(a)+(2*S1)+(3*S2)+f(b));
	return result;
}

long double simpson13(long double a, long double b, int n){
	long double result, S1, S2, x1, x2;
	long double h=(b-a)/n;
	S1=S2=0;
	for(int i=1; i<n; i++){
		if(i%2==1){
			x1=a+(h*i);
			S1=S1+f(x1);
		}
		else{
			x2=a+(h*i);
			S2=S2+f(x2);
		}
	}	
	result=(h/3)*(f(a)+f(b)+(4*S1)+(2*S2));
return result;
}

long double trapezoid(long double a, long double b, int n){
	long double result=0;
	long double h=(b-a)/n;
	long double S=0;
	long double x;
	for(int i=1; i<n; i++){
		x=a+(h*i);
		S=S+f(x);
	}
	result=(h/2)*(f(a)+f(b)+(2*S));
return result;
}

long double f(long double x) {
	return 4.0L/(1.0L + x*x);
}

void print(){
	printf("__________________________________________________________________________________");
	printf("_____________________________________________________\n");
	printf("|n     	| 	   Trap Error           |");
	printf("	 Simp 1/3 Error 	|");
	printf("	 Simp 3/8 Error 	|");
	printf("	  Boole Error 		|\n");
	printf("__________________________________________________________________________________");
	printf("_____________________________________________________\n");
}
