#include <unistd.h>

void redirect(int fds[2], int redirect_fd)
{
    dup2(fds[redirect_fd], redirect_fd);
    close(fds[0]);
    close(fds[1]);
}

int main(int argc, char** argv)
{
    int fds[2];
    pipe(fds);

    if (fork())
    {
        redirect(fds, 1);
        argv[0] = "grep";
        execvp("grep", argv);
    }
    else
    {
        redirect(fds, 0);
        execlp("wc", "wc", "-l", NULL);
    }

    return 0;
}
