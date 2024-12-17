#include "system.h"
#include <QDateTime>

//System 클래스 생성자
System::System(QObject *parent)
    : QObject{parent}     //부모 객체 초기화
    , m_carLocked( true ) // 차량 잠금 상태 초기화 (잠금상태)
    , m_outdoorTemp( 6 )  // 외부 온도 초기화 (6도)
    , m_userName( "Lee" ) // 사용자 이름 초기화 (Lee)
{
    m_currentTimeTimer = new QTimer(this);
    m_currentTimeTimer->setInterval(500);
    m_currentTimeTimer->setSingleShot(true);
    connect(m_currentTimeTimer, &QTimer::timeout, this, &System::setCurrentTimeTimerout);

    setCurrentTimeTimerout();
}

// 차량 잠금 상태를 반환
bool System::carLocked() const {
    return m_carLocked;
}

// 차량 잠금 상태를 설정하고 변경되었을 때 시그널을 발생시킴
void System::setCarLocked(bool carLocked)
{
    if(m_carLocked == carLocked)
        return;

    m_carLocked = carLocked;
    emit carLockedChanged(m_carLocked);
}

// 외부 온도를 반환
int System::outdoorTemp() const
{
    return m_outdoorTemp;
}

// 외부 온도를 설정하고 변경되었을 때 시그널을 발생시킴
void System::setOutdoorTemp(int newOutdoorTemp)
{
    if (m_outdoorTemp == newOutdoorTemp)
        return;
    m_outdoorTemp = newOutdoorTemp;
    emit outdoorTempChanged();
}

// 사용자 이름을 반환
const QString &System::userName() const
{
    return m_userName;
}

// 사용자 이름을 설정하고 변경되었을 때 시그널을 발생시킴
void System::setuserName(const QString &newUserName)
{
    if (m_userName == newUserName)
        return;
    m_userName = newUserName;
    emit userNameChanged();
}

// 현재 시간을 반환
const QString &System::currentTime() const
{
    return m_currentTime;
}

// 현재 시간을 설정하고 변경되었을 때 시그널을 발생시킴
void System::setcurrentTime(const QString &newCurrentTime)
{
    if (m_currentTime == newCurrentTime)
        return;
    m_currentTime = newCurrentTime;
    emit currentTimeChanged();
}

// 현재 시간을 업데이트하고 타이머를 재시작하는 함수
void System::setCurrentTimeTimerout()
{
    QDateTime dateTime;
    QString currentTime = dateTime.currentDateTime().toString("hh:mm ap");

    setcurrentTime( currentTime );
    m_currentTimeTimer->start();
}
