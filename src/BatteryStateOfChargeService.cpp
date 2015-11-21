#include "BatteryStateOfChargeService.h"
#include <iostream>
#include <QTime>
#include <QDebug>
using namespace std;
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
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
    timeRemaining = qAbs(timeRemaining)/2.77778e-7;
    return QTime(0, 0, 0, 0).addMSecs(timeRemaining);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{

    QTime currentTime = batteryData.time;
    changeTime = abs(initialTime.msecsTo(currentTime));
    changeTime = changeTime * 2.77778e-7;
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
    TimeLeft = qAbs(TimeLeft) * 2.77778e-7;

    dTime = initialTime.msecsTo(currentTime);
    dTime = dTime * 2.77778e-7;



    // Update your variables here.
}
