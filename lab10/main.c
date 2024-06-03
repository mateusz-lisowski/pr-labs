#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

#define KEY 12345
#define TIMEOUT 2 // Timeout in seconds

typedef struct {
    long mtype;
    int count;
} Message;

typedef struct {
    int queue_id;
    int waiting_count;
} Monitor;


void monitor_init(Monitor *monitor) {
    monitor->queue_id = msgget(KEY, IPC_CREAT | 0666);
    if (monitor->queue_id == -1) {
        perror("msgget");
        exit(1);
    }
    monitor->waiting_count = 0;
}

void monitor_destroy(Monitor *monitor) {
    if (msgctl(monitor->queue_id, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
}

void wejscie(Monitor *monitor) {
    Message msg;
    if (msgrcv(monitor->queue_id, &msg, sizeof(msg.count), 1, 0) == -1) {
        perror("msgrcv wejscie");
        exit(1);
    }
}

void wyjscie(Monitor *monitor) {
    Message msg;
    msg.mtype = 1;
    if (msgsnd(monitor->queue_id, &msg, sizeof(msg.count), 0) == -1) {
        perror("msgsnd wyjscie");
        exit(1);
    }
}

int oczekuj(Monitor *monitor) {

    wyjscie(monitor);

    monitor->waiting_count++;
    Message msg;
    msg.mtype = 2;
    if (msgsnd(monitor->queue_id, &msg, sizeof(msg.count), 0) == -1) {
        perror("msgsnd oczekuj");
        exit(1);
    }
    monitor->waiting_count--;

    wejscie(monitor);

    return 0; // Success
}

void notify(Monitor *monitor) {
    for (int i = 0; i < monitor->waiting_count; i++) {
        if (monitor->waiting_count > 0) {
            Message msg;
            msg.mtype = 3; // Changed to type 3 to release the waiting process
            if (msgsnd(monitor->queue_id, &msg, sizeof(msg.count), 0) == -1) {
                perror("msgsnd notify");
                exit(1);
            }
        }
    }
}

void worker(Monitor *monitor) {
    // Ustawienie niezależnego ziarna losowego dla każdego procesu
    srand(time(NULL) ^ (getpid() << 16));

    wejscie(monitor);
    // Krytyczna sekcja
    printf("Proces %d jest w monitorze.\n", getpid());
    
    // Symulacja operacji, która może wymagać oczekiwania i powiadomienia
    if (rand() % 2 == 0) {
        printf("Proces %d czeka...\n", getpid());
        if (oczekuj(monitor) == -1) {
            printf("Proces %d: oczekuj zakończone z powodu timeoutu\n", getpid());
        }
    } else {
        printf("Proces %d powiadamia...\n", getpid());
        notify(monitor);
    }
    
    printf("Proces %d opuszcza monitor.\n", getpid());
    wyjscie(monitor);
    exit(0);
}

int main() {
    Monitor monitor;
    monitor_init(&monitor);

    // Inicjalizacja kolejki
    Message msg;
    msg.mtype = 1;
    msg.count = 0;
    if (msgsnd(monitor.queue_id, &msg, sizeof(msg.count), 0) == -1) {
        perror("msgsnd inicjalizacja");
        exit(1);
    }

    for (int i = 0; i < 10; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            worker(&monitor);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }
    
    // Czekanie na zakończenie wszystkich procesów potomnych
    for (int i = 0; i < 10; i++) {
        wait(NULL);
    }

    monitor_destroy(&monitor);
    return 0;
}
