#include "sharedmemory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

// 공유 메모리를 초기화하는 함수
void initialize_shared_memory(SharedMemory **shared_memory) {
    int shm_fd = shm_open("/shared_memory", O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        exit(1);
    }

    // 공유 메모리를 프로세스 주소 공간에 매핑
    *shared_memory = (SharedMemory *)mmap(NULL, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (*shared_memory == MAP_FAILED) {
        perror("mmap failed");
        close(shm_fd);
        exit(1);
    }

    // 공유 메모리 내 Mutex 초기화
    if (pthread_mutex_init(&(*shared_memory)->mutex, NULL) != 0) {
        perror("pthread_mutex_init failed");
        munmap(*shared_memory, sizeof(SharedMemory));
        close(shm_fd);
        exit(1);
    }

    // 공유 메모리 초기 값 설정 (모든 값을 0으로 초기화)
    pthread_mutex_lock(&(*shared_memory)->mutex);
    memset(*shared_memory, 0, sizeof(SharedMemory));
    pthread_mutex_unlock(&(*shared_memory)->mutex);

    printf("Shared memory initialized successfully.\n");
}
