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
#ifndef TPOPMENUFIND_H
#define TPOPMENUFIND_H

#include "abstractpopmenu.h"

class TPopMenuFind : public TAbstractPopMenu
{
    Q_OBJECT

public:
    TPopMenuFind(QWidget *parent = 0);
    ~TPopMenuFind();

signals:
    void onActionMarkTriggered();
    void onActionFindTriggered();
    void onActionFindNextTriggered();

private:
    QAction *mActionMark;
    QAction *mActionFind;
    QAction *mActionFindNext;

    // TAbstractPopMenu interface
public:
    void retranslateUi() Q_DECL_OVERRIDE;
};


#endif // TPOPMENUFIND_H
