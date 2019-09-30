#include <stdio.h>
using namespace std;

int A(int, int);	//Ackerman's function

int main(){

	int m, n;
	while(scanf("%d %d", &m, &n) != EOF)
		printf("A(%d, %d) = %d\n", m, n, A(m, n));
	
	return 0;
}

// Ackerman's function
int A(int m, int n){
	if(m == 0) 
		return n + 1;
	if(n == 0) 
		return A(m - 1, 1);
	return A(m - 1, A(m, n - 1));
}
