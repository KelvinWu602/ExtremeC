// C Program to test file uid and gid and mode

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/fsuid.h>
#include <sys/stat.h>


#define FILENAME "lib/process-created.txt"
#define UID 1000
#define GID 1000
#define NEWMASK 0200


int main() {
    // setfsuid, sets the filesystem uid of this process, which will become the uid of the new file
    setfsuid(UID);
    // setfsgid, sets the filesystem gid of this process, which will become the gid of the new file
    setfsgid(GID);

    // get process real user id (who starts the process, cannot be changed by the process (except called by root user with setuid()))
    uid_t uid = getuid();
    // get process real group id
    gid_t gid = getgid();
    

    // get process effective user id (whose identity assumed by the process, can be changed by seteuid())
    uid_t euid = geteuid();
    // get process effective group id
    gid_t egid = getegid();

    printf("real: %d %d\n", uid,gid);
    printf("effe: %d %d\n", euid,egid);
    printf("fs  : %d %d\n", 1000,1000);

    
    // it returns the old umask, and set the umask as NEWMASK
    mode_t old_umask = umask(NEWMASK);
    printf("umask:   %04o -> %04o\n", old_umask, NEWMASK);

    
    // open file for reading
    int fd = open(FILENAME, O_RDONLY | O_CREAT, 0600);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // get the file stat
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        return 1;
    }

    printf("File mode: %04o\n", sb.st_mode);
    printf("File uid: %d\n", sb.st_uid);
    printf("File gid: %d\n", sb.st_gid);


    close(fd);
    return 0;
}