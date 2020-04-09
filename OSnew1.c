#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
sem_t getcaccess;
sem_t databccess;
int r_count=0;
void *Reader(void *arg);
void *Writer(void *arg);
int main()
{
int i=0,reader_t_number=0,writer_t_num=0;
sem_init(&getcaccess,0,1);
sem_init(&databccess,0,1);
pthread_t th_reader[100],th_writer[100];
printf("Enter readers thread number: \n");
scanf("%d",&reader_t_number);
printf("Enter writers thread number: \n");
scanf("%d",&writer_t_num);
for(i=0;i<reader_t_number;i++)
{
pthread_create(&th_reader[i],NULL,Reader,(void *)i);
}
for(i=0;i<reader_t_number;i++)
{
pthread_join(th_reader[i],NULL);
}
for(i=0;i<writer_t_num;i++)
{
pthread_create(&th_writer[i],NULL,Writer,(void *)i);
}
for(i=0;i<writer_t_num;i++)
{
pthread_join(th_writer[i],NULL);
}
sem_destroy(&databccess);
sem_destroy(&getcaccess);
return 0;
}
void * Writer(void *arg)
{
sleep(1);
int temp=(int)arg;
sem_wait(&databccess);
printf("Writer number %d enter to the database for modifying data\n",temp);
printf("Writer number %d writting to the database\n",temp);
printf("Writer number %d leaving to the database\n",temp);
sem_post(&databccess);
}
void *Reader(void *arg)
{
sleep(1);
int temp=(int)arg;
printf("Reader number %d enter to the database for reading data\n",temp);
sem_wait(&getcaccess);
r_count++;
if(r_count==1)
{
sem_wait(&databccess);
printf("Reader number %d reading to the database\n",temp);
}
sem_post(&getcaccess);
sem_wait(&getcaccess);
r_count--;
if(r_count==0)
{
printf("Reader number %d leaving to the database\n",temp);
sem_post(&databccess);
sem_post(&getcaccess);
}
}

