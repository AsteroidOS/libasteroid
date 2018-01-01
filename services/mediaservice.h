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

#ifndef MEDIASERVICE_H
#define MEDIASERVICE_H

#include <QObject>

#include "service.h"

class MediaService : public Service
{
    Q_OBJECT

public:
    MediaService();

    bool setTitle(QString title);
    bool setAlbum(QString album);
    bool setArtist(QString artist);
    bool setPlaying(bool playing);

signals:
    bool previous();
    bool next();
    bool play();
    bool pause();

protected:
    void onServiceDiscovered() override;
    void onCharacteristicChanged(const QLowEnergyCharacteristic &, const QByteArray &) override;

private:
    QLowEnergyCharacteristic m_titleChrc;
    QLowEnergyCharacteristic m_albumChrc;
    QLowEnergyCharacteristic m_artistChrc;
    QLowEnergyCharacteristic m_playingChrc;
    QLowEnergyCharacteristic m_commandChrc;
};

#endif // MEDIASERVICE_H
