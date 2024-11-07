#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 3

pthread_mutex_t mutex;
pthread_cond_t reader_cond;
pthread_cond_t writer_cond;
int read_count=0;
int write_count=0;

int shared_data=0;

void* reader(void* arg){
int reader_id=*(int*)arg;

    pthread_mutex_lock(&mutex);
    while(write_count > 0){
         pthread_cond_wait(&reader_cond,&mutex);
    }
    read_count++;
    pthread_mutex_unlock(&mutex);

    printf("Reader %d: Reading shared data: %d\n", reader_id,shared_data);

     pthread_mutex_lock(&mutex); 
     read_count--;

     if(read_count==0){
     pthread_cond_signal(&writer_cond);
     }
     pthread_mutex_unlock(&mutex);
     return NULL;
}

void* writer(void* arg){
     int writer_id=*(int*)arg;

     pthread_mutex_lock(&mutex);
     write_count++;
     while(read_count > 0){
         pthread_cond_wait(&writer_cond,&mutex);
     }

     shared_data++;
     printf("Writer %d: Writing shared data to: %d\n", writer_id,shared_data);
     write_count--;
     pthread_cond_broadcast(&reader_cond);
     pthread_cond_signal(&writer_cond);
     pthread_mutex_unlock(&mutex);
      return NULL;
}

int main()
{
    pthread_t readers[NUM_READERS],writers[NUM_WRITERS];
    int reader_ids[NUM_READERS],writer_ids[NUM_WRITERS];

    pthread_cond_init(&reader_cond,NULL);
    pthread_cond_init(&writer_cond,NULL);

     for(int i=0;i<NUM_READERS;i++){
     reader_ids[i]=i+1;
     pthread_create(&readers[i],NULL,reader,&reader_ids[i]);
     }

     for(int i=0;i<NUM_WRITERS;i++){
     writer_ids[i]=i+1;
     pthread_create(&writers[i],NULL,writer,&writer_ids[i]);
     }

     for(int i=0;i<NUM_READERS;i++){
     pthread_join(readers[i],NULL);
     }

     for(int i=0;i<NUM_WRITERS;i++){
     pthread_join(writers[i],NULL);
     }

     pthread_mutex_destroy(&mutex);
     pthread_cond_destroy(&reader_cond);
     pthread_cond_destroy(&writer_cond);

     return 0;

}

     

      


    

