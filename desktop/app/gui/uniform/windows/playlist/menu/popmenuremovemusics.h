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
#ifndef TPOPMENUREMOVEMUSICS_H
#define TPOPMENUREMOVEMUSICS_H

#include "abstractpopmenu.h"

class TPopMenuRemoveMusics : public TAbstractPopMenu
{
    Q_OBJECT

public:
    TPopMenuRemoveMusics(QWidget *parent = 0);
    ~TPopMenuRemoveMusics();

signals:
    void onActionRemoveSelectionsTriggered();
    void onActionRemoveRedundantTriggered();
    void onActionRemoveErrorsTriggered();
    void onActionRemoveAllTriggered();

private:
    QAction *mActionRemoveSelections;
    QAction *mActionRemoveRedundant;
    QAction *mActionRemoveErrors;
    QAction *mActionRemoveAll;

    // TAbstractPopMenu interface
public:
    void retranslateUi() Q_DECL_OVERRIDE;
};

#endif // TPOPMENUREMOVEMUSICS_H
