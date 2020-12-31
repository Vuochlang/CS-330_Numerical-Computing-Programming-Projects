#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int fact(int n) {
  if (n <= 1) return 1;
  return n*fact(n-1);
}

double min(double a, double b){
	if(a<b) return a;
	return b;
}

int main(){
	int n, smallest_n=15;
	double result=1; //rel.error
	float machineEpsilon=1.19209e-7;

	//EQUATION_12
	printf(" n\trel. error\n");
	for(n=1; n<16; n++){
		double temp=pow((log(2)/2),n+1)/(fact(n+1));
		printf(" %d\t%0.50f\n",n,temp);
		if(temp<machineEpsilon && n<smallest_n){
			smallest_n=n;
			result=temp;
		}
	}
	
	printf("\nsmallest n= %d\n",smallest_n);
	printf("rel. error  = %0.50f\n", result);

return 0;
}
