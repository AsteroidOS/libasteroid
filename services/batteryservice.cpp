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

#include "batteryservice.h"

BatteryService::BatteryService() : Service(QBluetoothUuid(QString(BATTERY_UUID)))
{ }

void BatteryService::onServiceDiscovered()
{
    m_lvlChrc = m_service->characteristic(QBluetoothUuid(QString(BATTERY_LVL_UUID)));

    QLowEnergyDescriptor notification = m_lvlChrc.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
    m_service->writeDescriptor(notification, QByteArray::fromHex("0100"));

    if(m_lvlChrc.isValid())
        emit ready();
}

quint8 BatteryService::level()
{
    if(m_service && m_lvlChrc.isValid()) {
        QByteArray ba = m_lvlChrc.value();
        return ba.at(0);
    } else
        return 0;
}

void BatteryService::onCharacteristicChanged(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
    if (c.uuid() == QBluetoothUuid(QString(BATTERY_LVL_UUID))) {
        quint8 val = value[0];

        emit levelChanged(val);
    }
}
