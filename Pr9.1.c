#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main() {
    FILE *fp;
    char line[512];
    char *token;    
    char *username;

    fp = popen("getent passwd", "r");
    if (fp == NULL) {
        printf("Помилка при відкритті процесу getent\n");
        return 1;
    }
    uid_t сurrent_uid = getuid();   
    while (fgets(line, sizeof(line), fp) != NULL) {
        username = strtok(line, ":");
        if (username == NULL) continue;
        token = strtok(NULL, ":");
        if (token == NULL) continue;
        token = strtok(NULL, ":");
        if (token == NULL) continue;
        uid_t uid = atoi(token);

        if (uid >= 1000 && uid != сurrent_uid) {            
            printf("Користувач: UID = %d, Username = %s\n", uid, username);
        }
    }
    pclose(fp); 
    return 0;
}