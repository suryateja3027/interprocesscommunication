#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <time.h>

const int racedist =  100;
int tpos = 0;
int hpos = 0;
static int sleep_time = 0;
int flag = 0;
pthread_t tid[4]; 
pthread_mutex_t lock1; 
pthread_mutex_t lock2; 
pthread_mutex_t lock3; 
pthread_mutex_t lock4; 


void* reporter(void* arg) 
{ 
    pthread_mutex_lock(&lock3); 
    
    
    
    while(tpos < racedist || hpos < racedist )
    {
    if (tpos >= racedist && hpos < racedist ){
    printf("Turtle won the race\n");
    exit(0);
    
    }
    if (hpos >= racedist && tpos < racedist ){
    printf("Hare won the race\n");
    exit(0);
    }
    }
     
    pthread_mutex_unlock(&lock3); 
  
    return NULL; 
} 
  
void* turtle(void* arg) 
{ 
    pthread_mutex_lock(&lock1); 
    
    
    
    while(tpos < racedist)
    {
    tpos += 1;
    printf("Turtle distance is: %d\n",tpos);
    tpos = tpos + sleep_time;
    usleep(rand()%10);        
    }
     
    pthread_mutex_unlock(&lock1); 
  
    return NULL; 
} 
void* hare(void* arg) 
{ 
    pthread_mutex_lock(&lock2); 
    
    
     
    while(hpos < racedist)
    {
    hpos += 8;
    sleep_time = usleep(rand()%1000);
    printf("Hare distance is: %d\n",hpos);
    
    }
      
  
    pthread_mutex_unlock(&lock2); 
  
    return NULL; 
} 

void* god(void* arg) 
{

    pthread_mutex_lock(&lock4); 
    
   	int error1;
        int error2;
        int error3;
  
        error1 = pthread_create(&(tid[0]), 
                               NULL, 
                               &turtle, NULL); 
        if (error1 != 0) 
            printf("\nThread can't be created :[%s]", 
                   strerror(error1)); 
                   
        error2 = pthread_create(&(tid[1]), 
                               NULL, 
                               &hare, NULL); 
        if (error2 != 0) 
            printf("\nThread can't be created :[%s]", 
                   strerror(error2)); 
                   
	error3 = pthread_create(&(tid[2]), 
                               NULL, 
                               &reporter, NULL); 
        if (error3 != 0) 
            printf("\nThread can't be created :[%s]", 
                   strerror(error3)); 
            
                   
	while (((hpos-tpos) > (rand()%15) ) && (flag <3) && (rand()<racedist) )
	{
	hpos -= (rand() % 10);
	flag += 1;	
	}                   
                   
    pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 
    pthread_join(tid[2], NULL);   
          

  
    pthread_mutex_unlock(&lock4); 
  
    return NULL; 
} 
  
int main(void) 
{ 

time_t t;
srand((unsigned) time(&t));
 
  
    if (pthread_mutex_init(&lock1, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
     if (pthread_mutex_init(&lock2, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
    if (pthread_mutex_init(&lock3, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
    if (pthread_mutex_init(&lock4, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
       
        int error4;
  
        error4 = pthread_create(&(tid[3]), 
                               NULL, 
                               &god, NULL); 
        if (error4 != 0) 
            printf("\nThread can't be created :[%s]", 
                   strerror(error4));  
    
    
  
 
    pthread_join(tid[3], NULL); 
    pthread_mutex_destroy(&lock1); 
    pthread_mutex_destroy(&lock2); 
    pthread_mutex_destroy(&lock3); 
    pthread_mutex_destroy(&lock4); 
  
    return 0; 
}
