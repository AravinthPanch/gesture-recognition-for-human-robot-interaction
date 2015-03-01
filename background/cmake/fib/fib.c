# include "stdio.h"
# include "stdlib.h"

int main( int argc, char** argv) {
	if ( argc > 2 || argc == 1 ) {
		printf("Fibonacci takes one postitive integer greater\
                         than two as it's argument\n");
		return EXIT_SUCCESS;
	}
	int a, b;
	a = 0;
	b = 1;
	printf( "%d", b );
	for( int i = 0; i + a <= atof( argv[1] ); b = i ) {
		i = a + b;
		a = b;
		printf( ", %d", i );
	}
	printf("\n");
	return EXIT_SUCCESS;
}