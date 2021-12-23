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

#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>

#include <QBluetoothUuid>
#include <QLowEnergyService>
#include <QLowEnergyController>

#include "common.h"

class Service : public QObject
{
    Q_OBJECT

public:
    explicit Service(QBluetoothUuid uuid, QObject *parent = nullptr);
    void serviceDiscovered(const QBluetoothUuid &gatt);
    void serviceScanDone(QLowEnergyController *ctrl);
    void disconnectService();

signals:
    void ready();

private slots:
    void serviceStateChanged(QLowEnergyService::ServiceState s);
    void characteristicChanged(const QLowEnergyCharacteristic &c, const QByteArray &value);

protected:
    virtual void onServiceDiscovered() = 0;
    virtual void onCharacteristicChanged(const QLowEnergyCharacteristic &c, const QByteArray &value) = 0;

    bool m_foundService;
    QLowEnergyService *m_service;
    QBluetoothUuid m_uuid;
};

#endif // SERVICE_H
