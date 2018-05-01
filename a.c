/*
 author: huyuanzhi
         20163015000045
 data: 2018-05-01
 QQ: 1157799274

*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>  
#include<semaphore.h>
#include<time.h>

typedef int buffer_item;
#define BUFFER_SIZE 7

buffer_item buffer[BUFFER_SIZE];
int count = 0;

//设置三个信号量并初始化
sem_t empty,full;
pthread_mutex_t mutex;

//操作缓冲区
int insert_item(buffer_item item);
int remove_item(buffer_item item);
//生产者消费者
void *producer(void *param);
void *consumer(void *param);

int main(){
    //初始化随机种子
    srand(time(NULL));
    //初始化信号量
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    //创建两个线程
    pthread_t produce, consume;
    pthread_create(&produce, NULL, producer, NULL);
    pthread_create(&consume, NULL, consumer, NULL);

    pthread_join(produce, NULL);
    pthread_join(consume, NULL);
    //释放同步量及关闭互斥量
    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);

    return 0;
}

int insert_item(buffer_item item){
    buffer[count] = item;
    if(buffer[count]==item)
    {
        count++;
        return 0;
    }
    return -1;
}

int remove_item(buffer_item item){
    buffer[count] = 0;
    if(buffer[count]==0)
    {
        count--;
        return 0;
    }
    return -1;
}

void *producer(void *param){
    buffer_item rand_num;
    int sleep_time;
    while(1){
        //睡眠0-2s随机时间，生产者睡眠时间比消费者短，这个是方便测试
        sleep_time = rand() % 2;
        sleep(sleep_time);
        //下面就是经典的p,v操作
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        rand_num = rand() % 10 + 1;
        printf("producer produced %d\n",rand_num);
        if(insert_item(rand_num))
            printf("report error condition");

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *param){
    buffer_item rand_num;
    int sleep_time;
    while(1){
        sleep_time = rand() % 3;
        sleep(sleep_time);

        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        rand_num = buffer[count-1];
        if(remove_item(rand_num))
            printf("report error condition");
        else
            printf("consumer consumed %d\n",rand_num);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}