// C Program to test concurrent file open from multiple processes

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define FILENAME "lib/test.txt"

// Will be explained in later chapters
char read_a_byte(int fd){
    char c;
    size_t len = 1;
    ssize_t ret = read(fd, &c, len);
    if(ret == -1){
        perror("read");
        return '\0';
    }
    return c;
}

int main() {
    // print current process id
    pid_t pid = getpid(); 
    printf("Process ID: %d\n", pid);
    // print process working directory (which is inherit from parent process)
    char pwd[100];
    getcwd(pwd,sizeof(pwd));
    printf("Working Directory: %s\n", pwd);

    // open file for reading
    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        // create a format string
        char err[20];
        sprintf(err, "pid %d fail", pid);
        perror(err);
        return 1;
    }
    printf("Process %d opened file\n", pid);

    // If both processes read the same character, it proves that both processes do not share the file object in memory. And they have their own f_pos field.
    printf("Process %d read '%c'\n", pid, read_a_byte(fd));

    // sleep for 1 seconds
    sleep(1);

    // close file
    close(fd);
    printf("Process %d closed file\n", pid);

    return 0;
}