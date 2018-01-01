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

#include "watchconnection.h"

WatchConnection::WatchConnection(QObject *parent) : QObject(parent)
{
    m_control = nullptr;

    m_batteryService = new BatteryService();
    m_mediaService = new MediaService();
    m_notificationService = new NotificationService();
    m_screenshotService = new ScreenshotService();
    m_timeService = new TimeService();
    m_weatherService = new WeatherService();

    m_services.append(m_batteryService);
    m_services.append(m_mediaService);
    m_services.append(m_notificationService);
    m_services.append(m_screenshotService);
    m_services.append(m_timeService);
    m_services.append(m_weatherService);
}

void WatchConnection::setDevice(Watch *device)
{
    m_currentDevice = device;

    if (m_control) {
        m_control->disconnectFromDevice();
        delete m_control;
        m_control = 0;
    }

    if (m_currentDevice) {
        m_control = new QLowEnergyController(m_currentDevice->getDevice(), this);
        m_control->setRemoteAddressType(QLowEnergyController::PublicAddress);
        connect(m_control, &QLowEnergyController::serviceDiscovered, this, &WatchConnection::serviceDiscovered);
        connect(m_control, &QLowEnergyController::discoveryFinished, this, &WatchConnection::serviceScanDone);
        connect(m_control, SIGNAL(error(QLowEnergyController::Error)), this, SLOT(connectionError(QLowEnergyController::Error)));
        connect(m_control, &QLowEnergyController::connected, this, &WatchConnection::deviceConnected);
        connect(m_control, &QLowEnergyController::disconnected, this, &WatchConnection::deviceDisconnected);

        m_control->connectToDevice();
    }
}

void WatchConnection::connectionError(QLowEnergyController::Error err)
{
    emit error(err);
}

void WatchConnection::deviceConnected()
{
    emit connected();
    m_control->discoverServices();
}

void WatchConnection::deviceDisconnected()
{
    emit disconnected();
}

void WatchConnection::serviceDiscovered(const QBluetoothUuid &gatt)
{
    QListIterator<Service *> i(m_services);
    while(i.hasNext())
        i.next()->serviceDiscovered(gatt);
}

void WatchConnection::serviceScanDone()
{
    QListIterator<Service *> i(m_services);
    while(i.hasNext())
        i.next()->serviceScanDone(m_control);

    emit servicesDiscovered();
}

void WatchConnection::disconnectService()
{
    QListIterator<Service *> i(m_services);
    while(i.hasNext())
        i.next()->disconnectService();

    if(m_control)
        m_control->disconnectFromDevice();
}

BatteryService *WatchConnection::batteryService()
{
    return m_batteryService;
}

MediaService *WatchConnection::mediaService()
{
    return m_mediaService;
}

NotificationService *WatchConnection::notificationService()
{
    return m_notificationService;
}

ScreenshotService *WatchConnection::screenshotService()
{
    return m_screenshotService;
}

TimeService *WatchConnection::timeService()
{
    return m_timeService;
}

WeatherService *WatchConnection::weatherService()
{
    return m_weatherService;
}
