//Name: Vuochlang Chang
//Date: 10/5/2020
//Durand-Kerner method to finding all n (complex) roots for the n-degree polynomial
//NOTE: coefficient will always stores as complex form 

#include <stdio.h>
#include <complex.h>

#define M_PI 3.14159265358979323846264338327950288
int main(){
	int kMax=50;//kMax iterations
	double complex epsilon=0.000001;//value of absolute error
		
	double complex c[20]; //assuming the max coefficient is 20
	int n=0; //counting number of entered coefficient
	int input1=0, input2=0;
	printf("Enter the coefficients:\n");
	while(scanf("%d %d",&input1,&input2)!=EOF){//this will keep reading the given input and storing as a complex number
		c[n] = input1 + input2 * I;
		n++;
	}
	c[n]=1+0*I;//set value for c[n]=1
	for(int i=0; i<n+1; i++){
		printf("c[%d]=\t%0.0f \t+ \t%0.0f i\n",i,creal(c[i]),cimag(c[n]));
	}//loop to print out value of the coefficients
	printf("\nn=%d\n",n);
	
	double complex z[n];
	double complex R=0, maxC=0;
	for(int i=0; i<n; i++){//loop to find max value of cabs(c[n])
		if(cabs(c[i])>creal(maxC)){
			maxC=cabs(c[i]);
		}
	}
	R=1+maxC;//set value to the radius R of the circle

	printf("R=%0.0f + %0.0f i\n\n",creal(R),cimag(R));
	
	double complex thetaJ;
	for(int i=0; i<n; i++){//loop to set value to the inital guess z[0] for j=0,.....,n-1
		thetaJ=i*((2*M_PI)/n);
		z[i]=(ccos(thetaJ)+(I*csin(thetaJ)))*R;	
		printf("z[%d] = %0.10f + %0.10f i\n",i,creal(z[i]),cimag(z[i]));
	}
	
	double complex deltaZMax, qJ, deltaZJ;
	double complex functionZ=0, b[n];
	for(int k=1; k<kMax+1; k++){//loop for each iteration
		printf("\niter %d\n", k);
		deltaZMax=0;
		
		for(int j=0; j<n; j++){//loop to go through each z[j]
			functionZ=0;
			qJ=1;
			
			for(int i=0; i<n; i++){//loop to find value of Qj which Qj cannot be 0 
				if(i!=j){
					qJ*=(z[j]-z[i]);
				}
			}
			
			for(int k1=n; k1>-1; k1--){//loop to implement Horner's Rule to evaluate f(z[j]) and store result in functionZ
				if(k1==n){
					b[k1]=c[k1];
				}
				if(k1!=n){		
					b[k1]=c[k1]+(b[k1+1]*z[j]);
				}
				if(k1==0)	
					functionZ=b[k1];
			}
			
			deltaZJ=-functionZ/qJ;//calculate deltaZJ 

			if(cabs(deltaZJ) > creal(deltaZMax)){//set deltaZMax to the max value of deltaZJ in z[j]
				deltaZMax=cabs(deltaZJ);
			}

			printf("z[%d]= %0.10f + %0.10f i\n",j, creal(z[j]), cimag(z[j]));
			z[j]=z[j]+deltaZJ;//update z[j]
		}

		if(cabs(deltaZMax)<=cabs(epsilon)){//quit the iteration when the different is smaller than the value of epsilon
			break;
		}	
	}
return 0;
}
