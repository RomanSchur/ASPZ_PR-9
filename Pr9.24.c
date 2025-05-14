#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void check(const char *test_file_path) {
    int fd;
    if (access(test_file_path, F_OK) == 0) {
        printf("Файл існує\n");
    } else {
        printf("Файл не існує\n");
        return; 
    }

    fd = open(test_file_path, O_RDONLY);
    if (fd == -1) {
        printf("Неможливо відкрити файл.\n");
    } else {
        printf("Файл відкрито\n");
        close(fd);
    }
}

int main() {
    char test_dir_path[256];
    char test_file_path[256];

    if (mkdir("test_dir", 0700) == -1) {
        printf("Не вдалось створити каталог!\n");
        return 1;
    }

    snprintf(test_file_path, sizeof(test_file_path), "%s/%s", "test_dir", "test_file.txt");
    int fd = open(test_file_path, O_CREAT | O_WRONLY, 0600);
    if (fd == -1) {
        printf("Не вдалось відкрити файл!.\n");
        return 1;
    }
    write(fd, "Hello World.\n", 50); 
    close(fd);

    printf("Каталог і файл створено.\n");

    if (chmod("test_dir", 0000) == -1) {
        printf("Не вдалось задати права доступу\n");
        return 1;
    }

    printf("\nПрава каталогу: немає доступу:\n");
    snprintf(test_file_path, sizeof(test_file_path), "%s/%s", "test_dir", "test_file.txt");
    check(test_file_path);

   
 if (chmod("test_dir", 0100) == -1) {
        printf("Не вдалось задати права доступу\n");
        return 1;
    }

    printf("\nПрава каталогу: виконання:\n");
    snprintf(test_file_path, sizeof(test_file_path), "%s/%s", "test_dir", "test_file.txt");
    check(test_file_path);

    
   if (chmod("test_dir", 0500) == -1) {
        printf("Не вдалось задати права доступу\n");
        return 1;
    }

    printf("\nПрава каталогу: читання та виконання\n");
    snprintf(test_file_path, sizeof(test_file_path), "%s/%s", "test_dir", "test_file.txt");
    check(test_file_path);

   
    if (chmod("test_dir", 0700) == -1) {
        printf("Не вдалось задати права доступу\n");
        return 1;
    }

    snprintf(test_file_path, sizeof(test_file_path), "rm -r %s", "test_dir");
    system(test_file_path);

    return 0;
}