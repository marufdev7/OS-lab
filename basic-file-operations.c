#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILENAME "example.txt"
#define BUFFER_SIZE 100

int main() {
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    // 1. Create and write to the file
    fd = open(FILENAME, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }
    char *text = "Hello, this is a test file.";
    bytes_written = write(fd, text, strlen(text));
    if (bytes_written == -1) {
        perror("Error writing to file");
        return 1;
    }
    close(fd);
    printf("File created and written successfully.\n");

    // 2. Read from the file
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        return 1;
    }
    bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
        perror("Error reading file");
        return 1;
    }
    buffer[bytes_read] = '\0';
    close(fd);
    printf("File content: %s\n", buffer);

    // 3. Delete the file
    if (unlink(FILENAME) == -1) {
        perror("Error deleting file");
        return 1;
    }
    printf("File deleted successfully.\n");

    return 0;
}
