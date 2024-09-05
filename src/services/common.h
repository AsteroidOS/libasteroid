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

#ifndef COMMON_H
#define COMMON_H

/* GATT Services and Characteristics UUIDs */

#define ASTEROID_OS_UUID  "00000000-0000-0000-0000-00a57e401d05"

#define MEDIA_UUID        "00007071-0000-0000-0000-00A57E401D05"
#define MEDIA_TITLE_UUID  "00007001-0000-0000-0000-00A57E401D05"
#define MEDIA_ALBUM_UUID  "00007002-0000-0000-0000-00A57E401D05"
#define MEDIA_ARTIST_UUID "00007003-0000-0000-0000-00A57E401D05"
#define MEDIA_PLAY_UUID   "00007004-0000-0000-0000-00A57E401D05"
#define MEDIA_COMM_UUID   "00007005-0000-0000-0000-00A57E401D05"

#define NOTIF_UUID        "00009071-0000-0000-0000-00A57E401D05"
#define NOTI_UPD_UUID     "00009001-0000-0000-0000-00A57E401D05"
#define NOTI_FDB_UUID     "00009002-0000-0000-0000-00A57E401D05"

#define WEATHER_UUID      "00008071-0000-0000-0000-00A57E401D05"
#define WEAT_CITY_UUID    "00008001-0000-0000-0000-00A57E401D05"
#define WEAT_IDS_UUID     "00008002-0000-0000-0000-00A57E401D05"
#define WEAT_MINT_UUID    "00008003-0000-0000-0000-00A57E401D05"
#define WEAT_MAXT_UUID    "00008004-0000-0000-0000-00A57E401D05"

#define BATTERY_UUID      "0000180F-0000-1000-8000-00805f9b34fb"
#define BATTERY_LVL_UUID  "00002a19-0000-1000-8000-00805f9b34fb"

#define SCREENSH_UUID     "00006071-0000-0000-0000-00A57E401D05"
#define SCREENSH_REQ_UUID "00006001-0000-0000-0000-00A57E401D05"
#define SCREENSH_CON_UUID "00006002-0000-0000-0000-00A57E401D05"

#define TIME_UUID         "00005071-0000-0000-0000-00A57E401D05"
#define TIME_SET_UUID     "00005001-0000-0000-0000-00A57E401D05"

#endif // COMMON_H
