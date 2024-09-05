/*
 * Copyright (C) 2018 - Florent Revest <revestflo@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "weatherservice.h"

WeatherService::WeatherService() : Service(QBluetoothUuid(QString(WEATHER_UUID)))
{ }

void WeatherService::onServiceDiscovered()
{
    m_cityChrc = m_service->characteristic(QBluetoothUuid(QString(WEAT_CITY_UUID)));
    m_idsChrc = m_service->characteristic(QBluetoothUuid(QString(WEAT_IDS_UUID)));
    m_minTempsChrc = m_service->characteristic(QBluetoothUuid(QString(WEAT_MINT_UUID)));
    m_maxTempsChrc = m_service->characteristic(QBluetoothUuid(QString(WEAT_MAXT_UUID)));

    if(m_cityChrc.isValid() && m_idsChrc.isValid() && m_minTempsChrc.isValid() && m_maxTempsChrc.isValid())
        emit ready();
}

bool WeatherService::setCity(QString city)
{
    if(m_service && m_cityChrc.isValid()) {
        m_service->writeCharacteristic(m_cityChrc, city.toUtf8(), QLowEnergyService::WriteWithResponse);
        return true;
    } else
        return false;
}

bool WeatherService::setIds(QList<short> l)
{
    if(m_service && m_idsChrc.isValid()) {
        QByteArray data(10, 0);

        for(int i = 0; i < l.length() && i < 5; i++) {
            data[2*i] = (quint8)(l[i] >> 8);
            data[(2*i)+1] = (quint8)(l[i]);
        }

        m_service->writeCharacteristic(m_idsChrc, data, QLowEnergyService::WriteWithResponse);
        return true;
    } else
        return false;
}

bool WeatherService::setMinTemps(QList<short> l)
{
    if(m_service && m_minTempsChrc.isValid()) {
        QByteArray data(10, 0);

        for(int i = 0; i < l.length() && i < 5; i++) {
            data[2*i] = (quint8)(l[i] >> 8);
            data[(2*i)+1] = (quint8)(l[i]);
        }

        m_service->writeCharacteristic(m_minTempsChrc, data, QLowEnergyService::WriteWithResponse);
        return true;
    } else
        return false;
}

bool WeatherService::setMaxTemps(QList<short> l)
{
    if(m_service && m_maxTempsChrc.isValid()) {
        QByteArray data(10, 0);

        for(int i = 0; i < l.length() && i < 5; i++) {
            data[2*i] = (quint8)(l[i] >> 8);
            data[(2*i)+1] = (quint8)(l[i]);
        }

        m_service->writeCharacteristic(m_maxTempsChrc, data, QLowEnergyService::WriteWithResponse);
        return true;
    } else
        return false;
}

bool WeatherService::setWeatherDays(QList<WeatherDay> wd)
{
    QList<short> icons;
    QList<short> minTemps;
    QList<short> maxTemps;

    for(int i = 0; i < wd.length() && i < 5; ++i) {
        icons.push_back(wd[i].m_wxIcon);
        minTemps.push_back(wd[i].m_loTemp);
        maxTemps.push_back(wd[i].m_hiTemp);
    }
    return setIds(icons) && setMinTemps(minTemps) && setMaxTemps(maxTemps);
}
