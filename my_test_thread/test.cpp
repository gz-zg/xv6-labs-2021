#include <iostream>
#include <vector>
#include <string>
#include <pthread.h>

int cnt = 0;
pthread_mutex_t lock;

void* add(void* arg)
{
    int num = *(int*)arg;
    for(int i = 1; i <= num; i++)
    {
        pthread_mutex_lock(&lock);
        cnt++;
        pthread_mutex_unlock(&lock);
    } 
    std::string* response = new std::string("OK!");
    return response;
}

int main()
{
    std::vector<pthread_t> pthread(10);
    pthread_mutex_init(&lock, NULL);
    
    for(int i = 0; i < 10; i++){
        int num = 1e6;
        pthread_create(&pthread[i], NULL, add, &num);
    }

    for(int i=0;i<10;i++){
        std::string* flag;
        pthread_join(pthread[i], (void**)&flag);
        std::cout<< *flag << std::endl;
        delete flag;
    }

    pthread_mutex_destroy(&lock);

    std::cout << "std: " << cnt << std::endl;

    return 0;
}