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

#ifndef SCREENSHOTSERVICE_H
#define SCREENSHOTSERVICE_H

#include <QObject>

#include "service.h"

class ScreenshotService : public Service
{
    Q_OBJECT

public:
    ScreenshotService();

    bool requestScreenshot();

signals:
    void screenshotReceived(QByteArray data);
    void progressChanged(unsigned int progress);

protected:
    void onServiceDiscovered() override;
    void onCharacteristicChanged(const QLowEnergyCharacteristic &, const QByteArray &) override;

private:
    QLowEnergyCharacteristic m_reqChrc;
    QLowEnergyCharacteristic m_conChrc;

    bool m_firstNotify;
    bool m_downloading;
    QByteArray m_totalData;
    unsigned int m_progress;
    unsigned int m_totalSize;
};

#endif // SCREENSHOTSERVICE_H
