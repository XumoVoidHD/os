#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void copy_file(const char *src, const char *dest) {
    int fd1 = open(src, O_RDONLY);
    if (fd1 < 0) {
        perror("Source file open failed");
        return;
    }

    int fd2 = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 < 0) {
        perror("Destination file open failed");
        close(fd1);
        return;
    }

    char buffer[1024];
    ssize_t bytes;

    while ((bytes = read(fd1, buffer, sizeof(buffer))) > 0) {
        write(fd2, buffer, bytes);
    }

    close(fd1);
    close(fd2);
    printf("File copied successfully!\n");
}

int main() {
    copy_file("source.txt", "copy.txt");
    return 0;
}
