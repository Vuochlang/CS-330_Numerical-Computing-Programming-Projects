/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Name: Vuochlang Chang
//	Programming Project 1: Computing exp(x) using Taylor series
//	Result from 4.1:
//		found the smallest_n=6 with the rel.error= 0.00000011916198284421748198936191797184247498364584
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_LOG2E
#define M_LOG2E   1.44269504088896340735992468100189214
#endif

#ifndef M_LN2
#define M_LN2  0.693147180559945309417232121458176568
#endif

int fact(int n) {
	  if (n <= 1) return 1;
	    return n*fact(n-1);
}

float myexp(float x) {
	int n=6;//smallest_n from rerr.c

	float z=x/M_LN2;
	float m=round(z);
	float w=z-m;
	float u=w*M_LN2;

	float twoM=ldexpf(1,m);
	float eU=0;
	for(int i=0; i<n+1; i++){
		eU+=(powf(u,i))/fact(i);
	}
	eU+=(exp(u)/fact(n+1))*powf(u,n+1);
	return (twoM*eU);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <number>\n", argv[0]);
    exit(1);
  }

  const float x = atof(argv[1]);
  const float y = myexp(x);

  printf("%0.9e\n", y);

  return 0;
}
