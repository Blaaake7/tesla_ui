#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include <pthread.h>

// 데이터 구조 정의
typedef struct {
    int ID;
    float ultrasonic_distance;
    float temperature;
    float humidity;
    int pressure;
    int door_status;
    int window_status;
} Zone1_3_Data_recv;

typedef struct {
    int ID;
    float co2;
    float heart;
    int sleep_score;
} Zone2_Data_recv;

typedef struct {
    int window_command;
    int sleep_alert;
} Zone1_3_Data_send;

typedef struct {
    Zone1_3_Data_recv zone1_recv;   // Zone 1 데이터
    Zone2_Data_recv zone2_recv;     // Zone 2 데이터
    Zone1_3_Data_recv zone3_recv;   // Zone 3 데이터
    Zone1_3_Data_send zone1_send;   // Zone 1 전송 데이터
    Zone1_3_Data_send zone3_send;   // Zone 3 전송 데이터
    pthread_mutex_t mutex;
} SharedMemory;

void initialize_shared_memory(SharedMemory **shared_memory);

#endif // SHAREDMEMORY_H
