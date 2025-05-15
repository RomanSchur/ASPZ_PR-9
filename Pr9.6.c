#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void list_dir (const char *directory) {
    FILE *fp;
    char command[256];
    char buffer[1024];

    sprintf(command, "ls -l %s", directory);
    printf("Файли у %s:\n", directory);

    fp = popen(command, "r");

    if (fp != NULL) {
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }
        pclose(fp);
    } else {
        printf("Помилка popen\n");
    }

    printf("\n");
}

int main() {
    list_dir("/home/roman"); 
    list_dir("/usr/bin");
    list_dir("/etc");

    return 0;
}