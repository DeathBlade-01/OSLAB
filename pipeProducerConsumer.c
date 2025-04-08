#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        close(fd[1]);
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        printf("Child read: %s\n", buffer);
        close(fd[0]);
    } else {
        close(fd[0]);
        char *msg = "Hello from parent via pipe!";
        write(fd[1], msg, strlen(msg)+1);
        close(fd[1]);
    }

    return 0;
}
