#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "LogFileReader.h"

namespace
{
    const QString STRING_TIME_FORMAT= "hh:mm:ss.zzz";
    const QString BATDATA_DELIMITER= ", ";
    const int COLUMNS = 3;
}

LogFileReader::LogFileReader()
{
}

LogFileReader::~LogFileReader()
{
}

bool LogFileReader::readAll(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open file" << fileName;
        return false;
    }

    QTextStream input(&file);
    while(!input.atEnd())
    {
        QString line = input.readLine();
        BatteryData batteryData;
        if (!parseLine(line, batteryData))
        {
            qDebug() << "Error while parsing" << line;
             return false;
        }
        else
        {
            emit batteryDataReceived(batteryData);
        }
    }

    return true;
}


bool LogFileReader::parseLine(const QString& line, BatteryData& batteryData) const
{
    QStringList sections = line.split(BATDATA_DELIMITER);

    if (sections.length() < COLUMNS)
    {
        qDebug() << "sections length is less than 3";
        return false;
    }

    else if (sections.length() > COLUMNS)
    {
        qDebug() << "sections length is greater than 3";
        return false;
    }

    QString timeString = sections.at(0);
    batteryData.time = QTime::fromString(timeString, STRING_TIME_FORMAT);

    bool doubleConversionVoltage;
    bool doubleConversionCurrent;

    batteryData.voltage = sections.at(1).toDouble(&doubleConversionVoltage);

    batteryData.current = sections.at(2).toDouble(&doubleConversionCurrent);

    if (!doubleConversionVoltage || !doubleConversionCurrent)
    {
        qDebug() << "double_conversion unsuccessful";
        return false;
    }

     if (batteryData.time.isValid())
         return true;
     else
     {
         qDebug() << "time is invalid";
         return false;
     }
}
