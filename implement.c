// DINNING PHILOSPHER PROBLEM
#include<stdio.h> //standar library for i/o operations
#include<stdlib.h>
#include<pthread.h> // to perform thread operations    
#include<semaphore.h>//to perform semaphore
#include<unistd.h>  //to perform sleep function
/* define dome state we frequantly used*/
#define N 5         //statically take 5 size
/* define three main process of philospher dinning problem */
#define think 0
#define hungry 1
#define eat   2
/* define left and right side of phulospher(process) */
#define left (ph_num+4)%N
#define right (ph_num+1)%N
sem_t wait;   //globaly declare wait call using semaphore bulit in library
sem_t S[N];   // array of binary semaphore
/* declartion of some main functions of philsopher (process) */
void *philospher(void*);
void take_stick(int);
void put_stick(int);
void test(int);
int state[N];       //declaratio of state (think,eat,hungry)
int phil_num[N]={0,1,2,3,4}; //array of processes
// main function
int main()
{
int i;
pthread_t t_id[N]; //create threads ids for muultiple threads
sem_init(&wait,0,1);
/* for intialization putt all semaphore values 0*/
for(i=0;i<N;i++)
sem_init(&S[i],0,0);
/* create threads of philospers */
for(i=0;i<N;i++)
{
pthread_create(&t_id[i],NULL,philospher,&phil_num[i]);
printf("\nPhilospher %d is thinking",i+1);
}
/* join threads*/
for(i=0;i<N;i++)
{
pthread_join(t_id[i],NULL);
}
}
// philospher function
/* this function call other composite function and take main actions of philsopher*/
void* philospher (void *num)
{
while(1)
{
int *i=num;
sleep(1);
take_stick(*i);
sleep(0);
put_stick(*i);
}
}
// take stick functions
/* the philsopher take the stick if he feels hungry and check wheater the stick is free or  
not(using test function)*/
void take_stick(int ph_num)
{
sem_wait(&wait);
state[ph_num]=hungry;
printf("\nphilospher %d is hungry",ph_num+1);
test(ph_num);
sem_post(&wait);
sem_wait(&S[ph_num]);
sleep(1);
}
// check wheather the sticks free or not */
void test(int ph_num)
{
if(state[ph_num]==hungry&&state[left]!=eat && state[right]!=eat)
{
state[ph_num]=eat;
sleep(2);
printf("\nPhilospher %d takes fork%d and 
%d\n",ph_num+1,left+1,ph_num+1);
printf("\nPhilospher is Eating%d",ph_num+1);
sem_post(&S[ph_num]);
}
}
// put stick
void put_stick(int ph_num)
{
sem_wait(&wait);
state[ph_num]=think;
printf("\nPhilopher %dputting forks %dand %d\n",ph_num+1,left+1,ph_num+1);
printf("\nPhilosopher %dis thinking\n ",ph_num+1);
test(left);
test(right);
sem_post(&wait);
}
