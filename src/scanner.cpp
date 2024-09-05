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

#include "scanner.h"

#include "services/common.h"

Scanner::Scanner(QObject *parent) : QObject(parent)
{
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &Scanner::addDevice);
#if QT_VERSION >= QT_VERSION_CHECK(6, 2, 0)
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::errorOccurred, this, [=](QBluetoothDeviceDiscoveryAgent::Error error){ this->scanError(error); });
#else
    connect(discoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error), this, [=](QBluetoothDeviceDiscoveryAgent::Error error){ this->scanError(error); });
#endif
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &Scanner::scanFinished);
}

Scanner::~Scanner()
{
    delete discoveryAgent;
    qDeleteAll(devices);
    devices.clear();
}

void Scanner::startScan()
{
    qDeleteAll(devices);
    devices.clear();
    discoveryAgent->start();
}

void Scanner::stopScan()
{
    discoveryAgent->stop();
}

void Scanner::addDevice(const QBluetoothDeviceInfo &info)
{
    if ((info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
            && info.serviceUuids().contains(QBluetoothUuid(QString(ASTEROID_OS_UUID)))) {
        Watch *w = new Watch(info);
        devices.append(w);
        emit watchFound(w);
    }
}

void Scanner::scanFinished()
{
    emit finished();
}

void Scanner::scanError(QBluetoothDeviceDiscoveryAgent::Error err)
{
    emit error(err);
}

QList<Watch *> Scanner::pairedWatches()
{
    return devices;
}
