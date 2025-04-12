#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main2(int argc, char **argv) {
    struct stat buf;
    const char *filepath = argv[1];

    // Test the stat function
	int err = stat(filepath, &buf);
    if (err == 0) {
        printf("File: %s\n", filepath);
        printf("Size: %lld bytes\n", buf.st_size);
        printf("flags: %u \n", buf.st_flags);
        printf("Permissions: %o\n", buf.st_mode);
        printf("Last modified: %ld\n", buf.st_mtime);
    } else {
        perror("stat failed");
		printf("err: %d\n", err);
    }
	S_IFDIR;
    return 0;
}
