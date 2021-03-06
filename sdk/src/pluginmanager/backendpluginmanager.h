/*
 * Copyright (C) Bilge Theall, wazcd_1608@qq.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef BACKENDPLUGINMANAGER_H
#define BACKENDPLUGINMANAGER_H

#include <string>

#include "abstractpluginmanager.h"

/*!
 * \brief The TBackendPluginManager class manage all backend plugins.
 */
class TBackendPluginManager : public TAbstractPluginManager
{
public:
    /*!
     * \brief Construct a TBackendPluginManager with a parent object.
     * \param parent The parent object of the TBackendPluginManager.
     */
    explicit TBackendPluginManager();
    ~TBackendPluginManager();

    static TBackendPluginManager *instance();
    static void deleteInstance();

    TBackendPlugin *parse(wstring file, TMusicInfo* musicInfo);

    TBackendPlugin *loadTrack(TTrackInfo *trackInfo);

private:
    static TBackendPluginManager *mInstance;
    TBackendPlugin *loadPlugin(wstring pluginName) override;
};

#endif // BACKENDPLUGINMANAGER_H
