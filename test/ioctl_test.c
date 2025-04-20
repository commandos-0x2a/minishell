#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main()
{
    struct winsize w;

    if (ioctl(0, TIOCGWINSZ, &w) == -1)
    {
        perror("ioctl");
        return (1);
    }

    printf("rows: %d, cols: %d\n", w.ws_row, w.ws_col);
}