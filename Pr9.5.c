#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main() {
    int file_fd;
    char command[512];
    int fd;
    
    file_fd = open("temp_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (file_fd == -1) {
        printf("Помилка створення файлу\n");
        return 1;
    }
    printf("Файл створено: temp_file.txt\n");
    close(file_fd);
   
    sprintf(command, "sudo chown root:wheel  %s", "temp_file.txt");
    if (system(command) != 0) {
        printf("Помилка зміни власника\n");
        return 1;
    }
    printf("Власника файлу змінено\n");

    sprintf(command, "sudo chmod 600 %s", "temp_file.txt");
    if (system(command) != 0) {
        printf("Помилка зміни прав доступу\n");
        return 1;
    }
    printf("Права доступу змінено\n");

    
    fd = open("temp_file.txt", O_RDONLY);
    if (fd == -1) {
        printf("Неможливо відкрити файл для читання\n");
    } else {
        printf("Можливо відкрити файл для читання\n");
        close(fd); 
    }

    fd = open("temp_file.txt", O_WRONLY | O_APPEND);
    if (fd == -1) {
        printf("Неможливо відкрити файл для запису\n");
    } else {
        if (write(fd, "Доданий текст.\n", 50) == -1) {
            printf("Помилка запису у файл\n");
        }
        close(fd);  
    }
  
    if (unlink("temp_file.txt") == -1) {
        printf("Помилка видалення файлу\n");
        return 1;
    }
    printf("Файл видалено\n");

    return 0;
}