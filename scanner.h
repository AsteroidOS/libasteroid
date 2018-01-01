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

#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include <QVariant>
#include <QList>

#include <qbluetoothlocaldevice.h>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServiceInfo>

#include "watch.h"

QT_FORWARD_DECLARE_CLASS (QBluetoothDeviceInfo)
QT_FORWARD_DECLARE_CLASS (QBluetoothServiceInfo)

class Scanner: public QObject
{
    Q_OBJECT

public:
    Scanner(QObject *parent = nullptr);
    ~Scanner();
    QList<Watch *> pairedWatches();

signals:
    void watchFound(Watch *w);
    void finished();
    void error(QBluetoothDeviceDiscoveryAgent::Error err);

public slots:
    void startScan();
    void stopScan();

private slots:
    void addDevice(const QBluetoothDeviceInfo&);
    void scanFinished();
    void scanError(QBluetoothDeviceDiscoveryAgent::Error);

private:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QList<Watch *> devices;
};

#endif // SCANNER_H
