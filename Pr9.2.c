#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    FILE *fp = popen("sudo cat /etc/shadow", "r");
    char buffer[1024];

    if (fp == NULL) {
        printf("Помилка popen !\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);
    return 0;
}