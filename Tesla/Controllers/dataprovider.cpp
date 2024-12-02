#include "dataprovider.h"
#include <QDebug>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

DataProvider::DataProvider(QObject *parent)
    : QObject(parent)
    , m_clientId(0)
    , m_sharedMem(nullptr)
    , m_shm_fd(-1)
{
    initSharedMemory();
}

DataProvider::~DataProvider()
{
    if (m_sharedMem != nullptr) {
        munmap(m_sharedMem, sizeof(SharedMemory));
        ::close(m_shm_fd);
    }
}

void DataProvider::initSharedMemory()
{
    m_shm_fd = shm_open("/shared_memory", O_RDWR, 0666);
    if (m_shm_fd == -1) {
        qDebug() << "Failed to open shared memory";
        return;
    }

    m_sharedMem = static_cast<SharedMemory *>(mmap(nullptr, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, m_shm_fd, 0));
    if (m_sharedMem == MAP_FAILED) {
        qDebug() << "Failed to map shared memory";
        m_sharedMem = nullptr;
        ::close(m_shm_fd);
        return;
    }
    qDebug() << "Shared memory initialized successfully";
}

int DataProvider::clientId() const
{
    return m_clientId;
}

void DataProvider::setClientId(int id)
{
    if (m_clientId != id) {
        m_clientId = id;
        emit clientIdChanged();
        updateData();
    }
}

int DataProvider::adcValue() const
{
    return m_data.adc_value;
}

int DataProvider::pwmDutyCycle() const
{
    return m_data.pwm_duty_cycle;
}

int DataProvider::distance() const
{
    return m_data.distance;
}

bool DataProvider::ledState() const
{
    return m_data.led_state == 1;
}

void DataProvider::updateData()
{
    if (m_sharedMem != nullptr) {
        pthread_mutex_lock(&m_sharedMem->mutex);
        if (m_clientId > 0 && m_clientId <= m_sharedMem->client_count && m_clientId <= MAX_CLIENTS) {
            m_data = m_sharedMem->client_data[m_clientId - 1];
            emit dataChanged();
        }
        pthread_mutex_unlock(&m_sharedMem->mutex);
    } else {
        qDebug() << "Shared memory not initialized";
    }
}
