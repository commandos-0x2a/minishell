#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd;
    pid_t pid, ppid;
    char    buf[128];
    char    *tok;
    char    *comm;

    fd = open("/proc/self/stat", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    ssize_t _read = read(fd, buf, sizeof(buf));
    if (_read == -1)
        return (0);
    buf[_read] = '\0';
    
    pid = atoi(buf);
    tok = strtok(buf, " ");

    comm = strtok(NULL, " ");
    
    strtok(NULL, " ");
    
    tok = strtok(NULL, " ");
    ppid = atoi(tok);
    
    printf("pid: %d\nppid: %d\ncomm: %s\n", pid, ppid, comm);

    close(fd);
    return 0;
}