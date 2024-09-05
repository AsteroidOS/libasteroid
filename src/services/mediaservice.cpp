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

#include "mediaservice.h"

MediaService::MediaService() : Service(QBluetoothUuid(QString(MEDIA_UUID)))
{ }

void MediaService::onServiceDiscovered()
{
    m_titleChrc = m_service->characteristic(QBluetoothUuid(QString(MEDIA_TITLE_UUID)));
    m_albumChrc = m_service->characteristic(QBluetoothUuid(QString(MEDIA_ALBUM_UUID)));
    m_artistChrc = m_service->characteristic(QBluetoothUuid(QString(MEDIA_ARTIST_UUID)));
    m_playingChrc = m_service->characteristic(QBluetoothUuid(QString(MEDIA_PLAY_UUID)));
    m_commandChrc = m_service->characteristic(QBluetoothUuid(QString(MEDIA_COMM_UUID)));

#if QT_VERSION >= QT_VERSION_CHECK(6, 2, 0)
    QLowEnergyDescriptor notification = m_commandChrc.descriptor(QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration);
#else
    QLowEnergyDescriptor notification = m_commandChrc.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
#endif
    m_service->writeDescriptor(notification, QByteArray::fromHex("0100"));

    if(m_titleChrc.isValid() && m_albumChrc.isValid() && m_artistChrc.isValid() && m_playingChrc.isValid() && m_commandChrc.isValid())
        emit ready();
}

bool MediaService::setTitle(QString title)
{
    if(m_service && m_titleChrc.isValid()) {
        m_service->writeCharacteristic(m_titleChrc, title.toUtf8(), QLowEnergyService::WriteWithResponse);
        return true;
    } else
        return false;
}

bool MediaService::setAlbum(QString album)
{
    if(m_service && m_albumChrc.isValid()) {
        m_service->writeCharacteristic(m_albumChrc, album.toUtf8(), QLowEnergyService::WriteWithResponse);
        return true;
    } else
        return false;
}

bool MediaService::setArtist(QString artist)
{
    if(m_service && m_artistChrc.isValid()) {
        m_service->writeCharacteristic(m_artistChrc, artist.toUtf8(), QLowEnergyService::WriteWithResponse);
        return true;
    } else
        return false;
}

bool MediaService::setPlaying(bool playing)
{
    if(m_service && m_playingChrc.isValid()) {
        QByteArray val = playing ? QByteArray(1, 1) : QByteArray(1, 0);
        m_service->writeCharacteristic(m_playingChrc, val, QLowEnergyService::WriteWithResponse);
        return true;
    } else
        return false;
}

void MediaService::onCharacteristicChanged(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
    if (c.uuid() == QBluetoothUuid(QString(MEDIA_COMM_UUID))) {
        const quint8 *data = reinterpret_cast<const quint8 *>(value.constData());
        quint8 cmd = data[0];

        switch(cmd) {
        case 0x0:
            emit previous();
            break;
        case 0x1:
            emit next();
            break;
        case 0x2:
            emit play();
            break;
        case 0x3:
            emit pause();
            break;
        case 0x4:
            quint8 vol = data[1];
            emit volume(vol);
            break;
        }
    }
}
