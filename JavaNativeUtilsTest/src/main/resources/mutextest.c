#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

void sleep5() {
    struct timespec spec;
    spec.tv_sec = 5;
    spec.tv_nsec = 0;
    nanosleep(&spec, &spec);
}

int main(int argc, char* argv[]) {
    printf("Do It %s\n", argv[1]);
    printf("shm_open\n");
    fflush(stdout);

    int shfd = shm_open(argv[1], O_RDWR, 0777);

    if (shfd == -1) {
        perror("shm_open");
        abort();
    }

    printf("mmap\n");
    fflush(stdout);

    void * mem = mmap(0, 4096, PROT_READ | PROT_WRITE,MAP_SHARED, shfd, 0);

    if (mem == 0) {
        abort();
    }

    pthread_mutexattr_t * attr = (pthread_mutexattr_t *) mem;
    pthread_mutex_t * mut = (pthread_mutex_t *) (mem + 256);

    printf("pthread_mutex_lock\n");
    fflush(stdout);
    if (pthread_mutex_lock(mut) != 0) {
        abort();
    }
    printf("LOCKED\n");
    fflush(stdout);
    if (pthread_mutex_unlock(mut) != 0) {
        abort();
    }
    printf("Done\n");
    fflush(stdout);
    return 0;
}


