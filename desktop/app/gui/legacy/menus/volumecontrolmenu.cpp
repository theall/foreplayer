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
#include "volumecontrolmenu.h"

TVolumeControlMenu::TVolumeControlMenu(QWidget *parent) :
    TAbstractMenu(parent)
{
    mActionVolumeUp = new QAction(this);
    mActionVolumeDown = new QAction(this);
    mActionVolumeMute = new QAction(this);
    mActionVolumeMute->setCheckable(true);

    connect(mActionVolumeUp, SIGNAL(triggered()), this, SIGNAL(onVolumeUpTriggered()));
    connect(mActionVolumeDown, SIGNAL(triggered()), this, SIGNAL(onVolumeDownTriggered()));
    connect(mActionVolumeMute, SIGNAL(toggled(bool)), this, SIGNAL(onVolumeMuteToggled(bool)));

    addAction(mActionVolumeUp);
    addAction(mActionVolumeDown);
    addSeparator();
    addAction(mActionVolumeMute);

    retranslateUi();
}

TVolumeControlMenu::~TVolumeControlMenu()
{

}

void TVolumeControlMenu::checkMuteAction(bool checked)
{
    mActionVolumeMute->blockSignals(true);
    mActionVolumeMute->setChecked(checked);
    mActionVolumeMute->blockSignals(false);
}

void TVolumeControlMenu::retranslateUi()
{
    mActionVolumeUp->setText(tr("Up"));
    mActionVolumeDown->setText(tr("Down"));
    mActionVolumeMute->setText(tr("Mute"));
}
