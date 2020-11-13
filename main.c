#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define SHELL "/bin/sh"

int create_process(const char *command) {
    int status;
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        execl(SHELL, SHELL, "-c", command, NULL);
        _exit(EXIT_FAILURE);
    } else if (pid < 0) {
        status = -1;
    } else {
        if (waitpid(pid, &status, 0) != pid) {
            status = -1;
        }
    }

    return status;
}
void *threadFunc(void* thread_data){
    create_process(thread_data);
    pthread_exit(0);
}

int sendsig(pid_t pid, int signum) {
    if (kill(pid, signum) == -1) {
        return 1;
    }

    return 0;
}

void sighandler(int signum) {
    printf("Signal received successfully\n");
}

int recvsign(int signum) {
    if (signal(signum, sighandler) == SIG_ERR) {
        return 1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    char *line = NULL;
    size_t len = 0;
    char *choice = NULL;

    int exit = 0;
    while (!exit) {
        printf("1 create process\n"
                      "2 create background process\n"
                      "3 exit\n");
        getline(&choice, &len, stdin);
        choice[strlen(choice) - 1] = '\0';
        if (!strcmp(choice, "1")) {
            getline(&line, &len, stdin);
            line[strlen(line) - 1] = '\0';
            if(!strcmp(line, "exit")) {
                exit++;
            }
            create_process(line);
            printf("Procces over...\n");
        } else if (!strcmp(choice, "2")) {
            getline(&line, &len, stdin);
            line[strlen(line) - 1] = '\0';
            if(!strcmp(line, "exit")) {
                exit++;
            }
            void *thread_data = line;
            pthread_t thread;
            pthread_create(&thread, NULL, threadFunc, thread_data);
//            pthread_join(thread, NULL);
        } else if (!strcmp(choice, "3")) {
            exit++;
        } else if (!strcmp(choice, "4")) {
            char *lin1 = NULL, *lin2 = NULL;
            printf("pid\n");
            getline(&lin1, &len, stdin);
            lin1[strlen(lin1) - 1] = '\0';
            printf("signum\n");
            getline(&lin2, &len, stdin);
            lin2[strlen(lin2) - 1] = '\0';
            sendsig(atoi(lin1), atoi(lin2));
        } else if (!strcmp(choice, "5")) {
            int signum;
            printf("signal to receive: ");
            scanf("%d", signum);
            if (recvsign(signum) == 1) {
                printf("failed to receive signal\n");
            }
        } else {
            printf("Wrong key\n");
        }
    }

    return 0;
}