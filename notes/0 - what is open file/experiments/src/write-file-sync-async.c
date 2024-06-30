// This C Program want to test performance difference between sync and async file write.

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define SYNC_FILE "lib/s.txt"
#define ASYNC_FILE "lib/a.txt"
// generate many words
#define DATA "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " \
             "Hello, World! " 
#define DATA_SIZE 224

int main(){
    int fd = open(SYNC_FILE, O_WRONLY | O_CREAT | O_TRUNC | O_SYNC, 0644);
    if(fd == -1){
        perror("open error");
        exit(1);
    }
    
    double sync_start = (double)clock();
    ssize_t ret = write(fd, DATA, DATA_SIZE);
    double sync_end = (double)clock();
    if (ret <= 0){
        perror("sync write error");
        close(fd);
        exit(1);
    }

    close(fd);

    fd = open(ASYNC_FILE, O_WRONLY | O_CREAT | O_TRUNC , 0644);
    if(fd == -1){
        perror("open error");
        exit(1);
    }


    double async_start = (double)clock();
    ssize_t ret1 = write(fd, DATA, DATA_SIZE);
    double async_end = (double)clock();
    if (ret1 <= 0){
        perror("async write error");
        close(fd);
        exit(1);
    }

    close(fd);

    printf("sync used: %f\n", sync_end - sync_start);
    printf("async used: %f\n", async_end - async_start);
}