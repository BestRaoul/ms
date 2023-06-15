#include <stdlib.h>
#include <unistd.h>

//gcc execve_leak_test.c -fsanitize=leak

int main(void)
{
    void *bruh = malloc(100);
    char* argv[] = { "echo", "b.", NULL };
    execve("/bin/echo", argv, NULL);
    write(1, "we\n", 3);
    return 0;
}