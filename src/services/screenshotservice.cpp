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

#include "screenshotservice.h"

ScreenshotService::ScreenshotService() : Service(QBluetoothUuid(QString(SCREENSH_UUID)))
{ }

void ScreenshotService::onServiceDiscovered()
{
    m_reqChrc = m_service->characteristic(QBluetoothUuid(QString(SCREENSH_REQ_UUID)));
    m_conChrc = m_service->characteristic(QBluetoothUuid(QString(SCREENSH_CON_UUID)));

    QLowEnergyDescriptor notification = m_conChrc.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
    m_service->writeDescriptor(notification, QByteArray::fromHex("0100"));

    if(m_reqChrc.isValid() && m_conChrc.isValid())
        emit ready();
}

bool ScreenshotService::requestScreenshot()
{
    if(m_service && m_reqChrc.isValid() && !m_downloading) {
        m_firstNotify = true;
        m_service->writeCharacteristic(m_reqChrc, QByteArray(1, 0), QLowEnergyService::WriteWithoutResponse);
        return true;
    } else
        return false;
}

void ScreenshotService::onCharacteristicChanged(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
    if (c.uuid() == QBluetoothUuid(QString(SCREENSH_CON_UUID))) {
        if(m_firstNotify && value.size() >= 4) {
            m_totalSize = (
                static_cast<unsigned>(value[0] & 0xff) << 0 | 
                static_cast<unsigned>(value[1] & 0xff) << 8 | 
                static_cast<unsigned>(value[2] & 0xff) << 16 | 
                static_cast<unsigned>(value[3] & 0xff) << 24);
            m_totalData.resize(0);
            m_progress = 0;
            m_firstNotify = false;
        } else {
            m_progress += value.size();
            m_totalData += value;
            if(m_progress == m_totalSize) {
                emit screenshotReceived(m_totalData);
                m_downloading = false;
            } else
                emit progressChanged((m_progress * 100)/m_totalSize);
        }
    }
}
