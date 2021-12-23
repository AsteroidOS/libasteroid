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

#include "service.h"

Service::Service(QBluetoothUuid uuid, QObject *parent) : QObject(parent)
{
    m_uuid = uuid;
    m_service = nullptr;
}

void Service::serviceDiscovered(const QBluetoothUuid &uuid)
{
    if(uuid == m_uuid)
        m_foundService = true;
}

void Service::serviceScanDone(QLowEnergyController *ctrl)
{
    if (m_service) {
        delete m_service;
        m_service = 0;
    }

    if (m_foundService)
        m_service = ctrl->createServiceObject(m_uuid, this);

    if (m_service) {
        connect(m_service, &QLowEnergyService::stateChanged, this, &Service::serviceStateChanged);
        connect(m_service, &QLowEnergyService::characteristicChanged, this, &Service::characteristicChanged);
        m_service->discoverDetails();
    }
}

void Service::disconnectService()
{
    m_foundService = false;
    delete m_service;
    m_service = 0;
}

void Service::serviceStateChanged(QLowEnergyService::ServiceState s)
{
    if(s == QLowEnergyService::ServiceDiscovered)
        onServiceDiscovered();
}

void Service::characteristicChanged(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
    onCharacteristicChanged(c, value);
}
