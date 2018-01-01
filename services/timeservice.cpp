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

#include "timeservice.h"

#include <QByteArray>

TimeService::TimeService() : Service(QBluetoothUuid(QString(TIME_UUID)))
{ }

void TimeService::onServiceDiscovered()
{
    m_setChrc = m_service->characteristic(QBluetoothUuid(QString(TIME_SET_UUID)));

    if(m_setChrc.isValid())
        emit ready();
}

bool TimeService::setTime(QDateTime t)
{
    if(m_service && m_setChrc.isValid()) {
        QByteArray data(6, 0);
        data[0] = t.date().year() - 1900;
        data[1] = t.date().month()-1;
        data[2] = t.date().day();
        data[3] = t.time().hour();
        data[4] = t.time().minute();
        data[5] = t.time().second();

        m_service->writeCharacteristic(m_setChrc, data, QLowEnergyService::WriteWithoutResponse);
        return true;
    } else
        return false;
}
