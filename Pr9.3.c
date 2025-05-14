#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char file_path[256];
    char copy_file_path[256];
    char *home_dir = getenv("HOME"); // Отримуємо з змінної середовища

    if (!home_dir) {
        printf("Не вдалось отримати домашній каталог з змінної середовища!\n");
        return 1;
    }

    snprintf(file_path, sizeof(file_path), "%s/%s", home_dir, "test_file.txt");
    int fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        printf("Не вдалось створити тимчасовий файл!\n");
        return 1;
    }
    write(fd, "This is a temporary file.\n", 26);
    close(fd);

    snprintf(copy_file_path, sizeof(copy_file_path), "%s/%s", home_dir, "copy_file.txt");
    char command[512];
    snprintf(command, sizeof(command), "sudo cp %s %s", file_path, copy_file_path);
    if (system(command) != 0) {
        printf("Не вдалось скопіювати файл!\n");
    }

    fd = open(copy_file_path, O_WRONLY | O_APPEND);
    if (fd != -1) {
        write(fd, "Adding more text.\n", 18);
        close(fd);
        printf("Файл змінено.\n");
    } else {
        printf("Неможливо відкрити файл для запису.\n");
    }

    snprintf(command, sizeof(command), "rm %s", copy_file_path);
    system(command);

    return 0;
}