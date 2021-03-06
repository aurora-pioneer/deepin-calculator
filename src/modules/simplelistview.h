/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SIMPLELISTVIEW_H
#define SIMPLELISTVIEW_H

#include <DWidget>
#include <DListView>
#include <QScrollBar>

DWIDGET_USE_NAMESPACE

class SimpleListView : public DListView
{
    Q_OBJECT

public:
    explicit SimpleListView(int mode = 0, DWidget *parent = nullptr); //mode:0-标准模式 1-科学模式
    ~SimpleListView();

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *event);
    void adjustScrollbarMargins();
Q_SIGNALS:
    void clickrow(QString str);

private slots:
    void selectHistory(const QModelIndex &index);
private:
    int m_mode = 0;
};

#endif
