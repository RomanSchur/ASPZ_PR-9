#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    FILE *fp;
    char line[256];

    printf("Команда: whoami\n");
    fp = popen("whoami", "r");
    if (fp == NULL) {
        printf("Помилка !\n");
        return 1;
    }
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    pclose(fp);

    printf("Команда: id\n");
    fp = popen("id", "r");
    if (fp == NULL) {
        printf("Помилка!\n");
        return 1;
    }
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    pclose(fp);
    return 0;
}