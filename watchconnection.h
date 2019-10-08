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

#ifndef WATCHCONNECTION_H
#define WATCHCONNECTION_H

#include <QObject>
#include <QTimer>

#include <QLowEnergyController>
#include <QLowEnergyService>

#include "watch.h"
#include "services/service.h"
#include "services/batteryservice.h"
#include "services/mediaservice.h"
#include "services/notificationservice.h"
#include "services/screenshotservice.h"
#include "services/timeservice.h"
#include "services/weatherservice.h"

class WatchConnection : public QObject
{
    Q_OBJECT

public:
    explicit WatchConnection(QObject *parent = nullptr);
    void setDevice(Watch *device);
    bool isConnected();
    Watch *currentWatch();

    BatteryService *batteryService();
    MediaService *mediaService();
    NotificationService *notificationService();
    ScreenshotService *screenshotService();
    TimeService *timeService();
    WeatherService *weatherService();

signals:
    void connected();
    void disconnected();
    void error(QLowEnergyController::Error);
    void servicesDiscovered();
    void currentWatchChanged();

public slots:
    void disconnectService();

private slots:
    void connectionError(QLowEnergyController::Error err);
    void deviceConnected();
    void deviceDisconnected();

private:
    QLowEnergyController *m_control;
    Watch *m_currentDevice;
    QList<Service *> m_services;

    BatteryService *m_batteryService;
    MediaService *m_mediaService;
    NotificationService *m_notificationService;
    ScreenshotService *m_screenshotService;
    TimeService *m_timeService;
    WeatherService *m_weatherService;

    bool m_isConnected;
    int m_connectionAttempts = 0;
    QTimer m_reconnectTimer;

    void serviceDiscovered(const QBluetoothUuid &);
    void serviceScanDone();
    void scheduleReconnect();
    void reconnect();

    void serviceStateChanged(QLowEnergyService::ServiceState s);
    void updateHeartRateValue(const QLowEnergyCharacteristic &c, const QByteArray &value);
    void confirmedDescriptorWrite(const QLowEnergyDescriptor &d, const QByteArray &value);
};

#endif // WATCHCONNECTION_H
