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

#ifndef WATCH_H
#define WATCH_H

#include <QObject>
#include <QList>

#include <qbluetoothdeviceinfo.h>
#include <qbluetoothaddress.h>

class Watch: public QObject
{
    Q_OBJECT

public:
    Watch(QBluetoothDeviceInfo d);
    QBluetoothAddress getAddress();
    QString getName();
    QBluetoothDeviceInfo getDevice();

signals:
    void deviceChanged();

private:
    QBluetoothDeviceInfo device;
};

#endif // WATCH_H
