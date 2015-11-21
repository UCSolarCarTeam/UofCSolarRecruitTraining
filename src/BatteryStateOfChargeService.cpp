#include "BatteryStateOfChargeService.h"
#include <iostream>
#include <QTime>
#include <QDebug>
using namespace std;
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const QString CONVERT_TO_MILLISECONDS = 2.7778e-7;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    AmpHours = BATTERY_AMP_HOUR_CAPACITY*(initialStateOfChargePercent_/100);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY-AmpHours;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (Current < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double timeRemaining = (BATTERY_AMP_HOUR_CAPACITY-AmpHours)/inCurrent;
    timeRemaining = qAbs(timeRemaining)/CONVERT_TO_MILLISECONDS;
    return QTime(0, 0, 0, 0).addMSecs(timeRemaining);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{

    QTime currentTime = batteryData.time;
    changeTime = abs(initialTime.msecsTo(currentTime));
    changeTime = changeTime * CONVERT_TO_MILLISECONDS;
    initialTime = currentTime;
    if ((Current > 0 && Current < 10000000000) || Current < 0 )
    {
        inCurrent = Current;
    }
    Current = batteryData.current;

    if (inCurrent == 0)
    {
        objectCurrent = 0;
    }
    else
    {
        objectCurrent = (inCurrent + Current)/2;
    }

    inVoltage = batteryData.voltage;
    Voltage = batteryData.voltage;
    AmpChange = (objectCurrent * changeTime);

    AmpHours += AmpChange;

    counter++;
    SumCurrent += inCurrent;
    AverageCurrent = SumCurrent/counter;
    TimeLeft= (BATTERY_AMP_HOUR_CAPACITY-AmpHours)/AverageCurrent;
    TimeLeft = qAbs(TimeLeft) * CONVERT_TO_MILLISECONDS;

    dTime = initialTime.msecsTo(currentTime);
    dTime = dTime * CONVERT_TO_MILLISECONDS;
}
