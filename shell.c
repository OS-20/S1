#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void typeline(char *opt, char *fname) {
    FILE *fp = fopen(fname, "r");
    if (!fp) { perror("File"); return; }
    char line[200]; int n = 0;
    if (opt[0] == '+') {
        int limit = atoi(opt + 1);
        while (fgets(line, sizeof(line), fp) && n++ < limit) printf("%s", line);
    } else if (!strcmp(opt, "-a"))
        while (fgets(line, sizeof(line), fp)) printf("%s", line);
    else
        printf("Usage: typeline +n filename | typeline -a filename\n");
    fclose(fp);
}

int main() {
    char input[100], *args[10];
    while (1) {
        printf("myshell$ ");
        if (!fgets(input, sizeof(input), stdin)) break;
        if ((args[0] = strtok(input, " \t\n")) == NULL) continue;
        int i = 0; while ((args[++i] = strtok(NULL, " \t\n")));
        if (!strcmp(args[0], "exit")) break;
        else if (!strcmp(args[0], "typeline")) {
            if (args[1] && args[2]) typeline(args[1], args[2]);
            else printf("Usage: typeline +n filename | typeline -a filename\n");
        } else if (fork() == 0) {
            execvp(args[0], args);
            perror("Command"); exit(1);
        } else wait(NULL);
    }
    return 0;
}
