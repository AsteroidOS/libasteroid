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

#include "notificationservice.h"

NotificationService::NotificationService() : Service(QBluetoothUuid(QString(NOTIF_UUID)))
{ }

void NotificationService::onServiceDiscovered()
{
    m_updateChrc = m_service->characteristic(QBluetoothUuid(QString(NOTI_UPD_UUID)));
    m_feedbackChrc = m_service->characteristic(QBluetoothUuid(QString(NOTI_FDB_UUID)));

    if(m_updateChrc.isValid() && m_feedbackChrc.isValid())
        emit ready();
}

bool NotificationService::insertNotification(QString packageName, unsigned int id, QString appName, QString icon, QString summary, QString body, QString vibrate)
{
    if(m_service && m_updateChrc.isValid()) {
        QByteArray data = QString("<insert><pn>%1</pn><id>%2</id><an>%3</an><ai>%4</ai><su>%5</su><bo>%6</bo><vb>%7</vb></insert>")
                .arg(packageName, QString::number(id), appName, icon, summary, body, vibrate).toUtf8();

        m_service->writeCharacteristic(m_updateChrc, data, QLowEnergyService::WriteWithResponse);
        return true;
    } else
        return false;
}

bool NotificationService::removeNotification(unsigned int id)
{
    if(m_service && m_updateChrc.isValid()) {
        QByteArray data = QString("<removed><id>%1</id></removed>").arg(id).toUtf8();
        m_service->writeCharacteristic(m_updateChrc, data, QLowEnergyService::WriteWithResponse);
        return true;
    } else
        return false;
}
