#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
void *func1();
void *func2();
void *func3();
sem_t s1;
sem_t s2;
sem_t s3;

int main() {
	sem_init(&s1,0,1);
	sem_init(&s2,0,1);
	sem_init(&s3,0,1);
	pthread_t p1, p2,p3;
	pthread_create(&p1, NULL, func1, NULL); // create thread
	pthread_create(&p2, NULL, func2, NULL);
	pthread_create(&p3, NULL, func3, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3,NULL);

	printf("Thread joined\n");
	return 0;
}

void *func1() {
sem_wait(&s1); 
printf("Thread one acquired first semaphore\n");
sleep(1);
sem_wait(&s2);
printf("Thread one acquired second semaphore\n");
sleep(1);
sem_wait(&s3);
printf("Thread one acquired third semaphore");
sem_post(&s3);
printf("Thread one released third semaphore\n");
sem_post(&s2);
printf("Thread one released second semaphore\n");
sem_post(&s1);
printf("THread one realesed first semaphore\n");
}


void *func2() {
sem_wait(&s2); 
printf("Thread two acquired second  semaphore\n");
sleep(1);
sem_wait(&s3);
printf("Thread two acquired third semaphore\n");
sleep(1);
sem_wait(&s1);
printf("Thread two acquired first  semaphore");
sem_post(&s1);
printf("Thread two released first semaphore\n");
sem_post(&s3);
printf("Thread two released third semaphore\n");
sem_post(&s2);
printf("THread two realesed second semaphore\n");
}


void *func3() {
sem_wait(&s3); 
printf("Thread three acquired third semaphore\n");
sleep(1);
sem_wait(&s2);
printf("Thread three acquired second semaphore\n");
sleep(1);
sem_wait(&s1);
printf("Thread three acquired first semaphore");
sem_post(&s1);
printf("Thread three released first  semaphore\n");
sem_post(&s2);
printf("Thread three released second semaphore\n");
sem_post(&s3);
printf("THread three realesed third semaphore\n");
}

