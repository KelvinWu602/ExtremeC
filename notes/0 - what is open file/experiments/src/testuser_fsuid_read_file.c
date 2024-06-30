// C Program to test user program with root fsuid to read files owned by root

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/fsuid.h>

#include <errno.h>
#include <string.h>


#define FILENAME "lib/testuserhome/testuser-own" //this file owned by testuser
#define TESTUSER_UID 1000 //this refer to a normal user not the testuser, which has no permission to read the testuser-own file

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

void print_identity(){
    printf("real: %d %d eff: %d %d\n", getuid(), getgid(),geteuid(), getegid());
}

int main() {
    // From Linux man page
    //  Normally, the value of the process's filesystem user ID is the
    //    same as the value of its effective user ID.  This is so, because
    //    whenever a process's effective user ID is changed, the kernel
    //    also changes the filesystem user ID to be the same as the new
    //    value of the effective user ID.  A process can cause the value of
    //    its filesystem user ID to diverge from its effective user ID by
    //    using setfsuid() to change its filesystem user ID to the value
    //    given in fsuid.

    // Therefore, it is impossible for a process to change its fsuid ONLY and read files owned by other users.

    print_identity();

    // setfsuid will only work if euid = 0 or fsuid == uid, euid, or saved set-uid, or current fsuid
    setfsuid(TESTUSER_UID);
    // get previous fsuid, which shows whether the previous call has succeeded or not
    uid_t fsuid = setfsuid(-1); //must fail, https://man7.org/linux/man-pages/man2/setfsuid.2.html
    if(fsuid != TESTUSER_UID){
        printf("setfsuid failed, current fsuid is %d\n", fsuid);
    }else{
        printf("setfsuid success, current fsuid is %d\n", fsuid);
    }

    print_identity();
    
    // open file for reading, this should fail even those the process has effective user id 0, proving that process's filesystem permission is evaluated on fsuid, not euid.
    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    printf("opened file\n");
    printf("read '%c'\n", read_a_byte(fd));

    
    // close file
    close(fd);
    printf("closed file\n");

    return 0;
}