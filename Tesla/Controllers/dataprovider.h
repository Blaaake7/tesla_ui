#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QObject>
#include <pthread.h>

#define MAX_CLIENTS 10

typedef struct {
    int adc_value;
    int pwm_duty_cycle;
    int distance;
    int led_state;
} DataPacket;

struct SharedMemory {
    DataPacket client_data[MAX_CLIENTS];
    int client_count;
    pthread_mutex_t mutex;
};

class DataProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int clientId READ clientId WRITE setClientId NOTIFY clientIdChanged)
    Q_PROPERTY(int adcValue READ adcValue NOTIFY dataChanged)
    Q_PROPERTY(int pwmDutyCycle READ pwmDutyCycle NOTIFY dataChanged)
    Q_PROPERTY(int distance READ distance NOTIFY dataChanged)
    Q_PROPERTY(bool ledState READ ledState NOTIFY dataChanged)

public:
    explicit DataProvider(QObject *parent = nullptr);
    ~DataProvider();

    int clientId() const;
    void setClientId(int id);

    int adcValue() const;
    int pwmDutyCycle() const;
    int distance() const;
    bool ledState() const;

    Q_INVOKABLE void updateData();

signals:
    void clientIdChanged();
    void dataChanged();

private:
    int m_clientId;
    DataPacket m_data;
    SharedMemory *m_sharedMem;
    int m_shm_fd;

    void initSharedMemory();
};

#endif // DATAPROVIDER_H
