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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QStackedLayout>
#include <QMenu>

#include "modules/basicmodule.h"
#include "modules/scientificmodule.h"
#include "dsettings.h"

//#define ENABLE_SCIENTIFIC 1

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    //void onViewShortcut();
protected:
    //void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);

private:
    void initTheme();
    //void switchTheme();
    void initModule();
    void switchToSimpleMode();
    void switchToScientificMode();

private:
    DSettings *m_settings;
    QStackedLayout *m_mainLayout;
    DMenu *m_tbMenu;
    QAction *m_themeAction;
    QAction *m_simpleAction;
    QAction *m_scAction;
    QColor m_titlebarColor;

    BasicModule *m_basicModule;
    scientificModule *m_scientificModule;
};

#endif
