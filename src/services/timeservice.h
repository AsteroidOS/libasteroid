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

#ifndef TIMESERVICE_H
#define TIMESERVICE_H

#include <QObject>
#include <QDateTime>

#include "service.h"

class TimeService : public Service
{
    Q_OBJECT

public:
    TimeService();

    bool setTime(QDateTime t);

protected:
    void onServiceDiscovered() override;
    void onCharacteristicChanged(const QLowEnergyCharacteristic &, const QByteArray &) override {}

private:
    QLowEnergyCharacteristic m_setChrc;
};

#endif // TIMESERVICE_H
