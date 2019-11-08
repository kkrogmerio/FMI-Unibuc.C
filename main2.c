#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

struct arg_struct {
	int **a;
	int **b;
	int i;
	int j;
};	


void *thread_function(void *arg) {
	struct arg_struct *args = (struct arg_struct *)arg;
	unsigned k;
	int *c = malloc(sizeof(int));
	*c = 0;
	for(k = 0; k < 2; k ++) {
		*c += args->a[args->i][k]*args->b[k][args->j];
	}
	return (void *)c;
}


int main(int argc, char **argv) {
	unsigned i, j;
	int **a = (int **)malloc(2 * sizeof(int *));
	for(i = 0; i < 2; i ++) a[i] = (int *)malloc(2 * sizeof(int));
	int **b = (int **)malloc(2 * sizeof(int *));
	for(i = 0; i < 2; i ++) b[i] = (int *)malloc(2 * sizeof(int));


	// -- initializare matrice --
	a[0][0] = 2; a[0][1] = 3;
	a[1][0] = 4; a[1][1] = 5;

	b[0][0] = 7; b[0][1] = 5;
	b[1][0] = 3; b[1][1] = 9;


	pthread_t threads[4];

	int contor = 0;	
	for(i = 0; i < 2; i ++) {
		for(j = 0; j < 2; j ++) {

			struct arg_struct *args = (struct arg_struct *)malloc(sizeof(struct arg_struct));
			args->a = a;
			args->b = b;
			args->i = i;
			args->j = j;
			if(pthread_create(&threads[contor], NULL, thread_function, (void *)args)) {
				perror(NULL);
				return errno;
			}
			contor ++;	
		}
	}

	void *result = NULL;
	for(i = 0; i < 4; i ++) {
		if(pthread_join(threads[i], &result)) {
			perror(NULL);
			return errno;
		}
		printf("%d ", *(int *)result);
	}	

	return 0;
}
