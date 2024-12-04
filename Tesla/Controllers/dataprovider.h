#include <QObject>
#include <QTimer>

class DataProvider : public QObject {
    Q_OBJECT
    Q_PROPERTY(float zone1Distance READ zone1Distance NOTIFY zone1DistanceChanged)
    Q_PROPERTY(float zone1Temperature READ zone1Temperature NOTIFY zone1TemperatureChanged)
    Q_PROPERTY(float zone2CO2 READ zone2CO2 NOTIFY zone2CO2Changed)
    Q_PROPERTY(int sleepScore READ sleepScore NOTIFY sleepScoreChanged)
    Q_PROPERTY(int doorStatus READ doorStatus NOTIFY doorStatusChanged)

public:
    explicit DataProvider(QObject *parent = nullptr);

    float zone1Distance() const { return m_zone1Distance; }
    float zone1Temperature() const { return m_zone1Temperature; }
    float zone2CO2() const { return m_zone2CO2; }
    int sleepScore() const { return m_sleepScore; }
    int doorStatus() const { return m_doorStatus; }

signals:
    void zone1DistanceChanged();
    void zone1TemperatureChanged();
    void zone2CO2Changed();
    void sleepScoreChanged();
    void doorStatusChanged();

public slots:
    void updateData();

private:
    QTimer *m_timer;
    float m_zone1Distance;
    float m_zone1Temperature;
    float m_zone2CO2;
    int m_sleepScore;
    int m_doorStatus;
};
