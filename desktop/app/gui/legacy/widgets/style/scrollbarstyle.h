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
#ifndef TSCROLLBARSTYLE_H
#define TSCROLLBARSTYLE_H

#include "abstractstyle.h"

class TScrollbarStyle : public TAbstractStyle
{
public:
    TScrollbarStyle();

    void drawComplexControl(ComplexControl control,
                            const QStyleOptionComplex *option,
                            QPainter *painter,
                            const QWidget *widget) const;

    int styleHint(StyleHint hint,
                  const QStyleOption *option,
                  const QWidget *widget,
                  QStyleHintReturn *returnData) const;
    int pixelMetric(PixelMetric metric,
                    const QStyleOption *option,
                    const QWidget *widget) const;

    void drawWidget(const QWidget *widget, const QStyleOptionComplex *option, QPainter *painter) const Q_DECL_OVERRIDE;

};

#endif // TSCROLLBARSTYLE_H
