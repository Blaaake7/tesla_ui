#include "dataprovider.h"
#include "sharedmemory.h"
#include <QDebug>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

extern SharedMemory *shared_memory; // 서버 코드에서 공유 메모리 정의

DataProvider::DataProvider(QObject *parent)
    : QObject(parent)
    , m_zone1Distance(0)
    , m_zone3Distance(0)
    , m_zone1Temperature(0)
    , m_zone2CO2(0)
    , m_sleepScore(0)
    , m_doorStatus(0)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &DataProvider::updateData);
    m_timer->start(1000); // 1초마다 데이터 갱신
}

void DataProvider::updateData()
{
    if (shared_memory != nullptr) {
        qDebug() << "Zone 1 Distance:" << m_zone1Distance;

        // 공유 메모리에서 값 읽기
        m_zone1Distance = shared_memory->zone1_recv.ultrasonic_distance;
        m_zone3Distance = shared_memory->zone3_recv.ultrasonic_distance;
        m_zone1Temperature = shared_memory->zone1_recv.temperature;
        m_zone2CO2 = shared_memory->zone2_recv.co2;
        m_sleepScore = shared_memory->zone2_recv.sleep_score;
        m_doorStatus = shared_memory->zone1_recv.door_status;

        // 값 변경 시 시그널 전송
        emit zone1DistanceChanged();
        emit zone3DistanceChanged();
        emit zone1TemperatureChanged();
        emit zone2CO2Changed();
        emit sleepScoreChanged();
        emit doorStatusChanged();
    } else {
        qDebug() << "Shared memory not initialized.";
    }
}
