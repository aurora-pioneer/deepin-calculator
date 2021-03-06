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
#include <QTimer>

#include <DPalette>
#include <DImageButton>

#include "basickeypad.h"
#include "dthememanager.h"

const BasicKeypad::KeyDescription BasicKeypad::keyDescriptions[] = {
//    {"MC", Key_MC, 1, 0, 1, 2},       {"MR", Key_MR, 1, 2, 1, 2},
//    {"M+", Key_Mplus, 1, 4, 1, 2},    {"M-", Key_Mminus, 1, 6, 1, 2},
//    {"MS", Key_MS, 1, 8, 1, 2},       {"M^", Key_Mlist, 1, 10, 1, 2},

    {"C", Key_Clear, 1, 0, 1, 3},     {"%", Key_Percent, 1, 3, 1, 3},
    {"", Key_Backspace, 1, 6, 1, 3},  {"", Key_Div, 1, 9, 1, 3},

    {"7", Key_7, 2, 0, 1, 3},         {"8", Key_8, 2, 3, 1, 3},
    {"9", Key_9, 2, 6, 1, 3},         {"", Key_Mult, 2, 9, 1, 3},

    {"4", Key_4, 3, 0, 1, 3},         {"5", Key_5, 3, 3, 1, 3},
    {"6", Key_6, 3, 6, 1, 3},         {"", Key_Min, 3, 9, 1, 3},

    {"1", Key_1, 4, 0, 1, 3},         {"2", Key_2, 4, 3, 1, 3},
    {"3", Key_3, 4, 6, 1, 3},         {"", Key_Plus, 4, 9, 1, 3},

    {"0", Key_0, 5, 0, 1, 3},         {".", Key_Point, 5, 3, 1, 3},
    {"()", Key_Brackets, 5, 6, 1, 3}, {"=", Key_Equals, 5, 9, 1, 3}
};

static DPushButton *createSpecialKeyButton(BasicKeypad::Buttons key)
{
    IconButton *button = new IconButton;

    QString path;
    if (DGuiApplicationHelper::instance()->themeType() == 2)
        path = QString(":/assets/images/%1/").arg("dark");
    else
        path = QString(":/assets/images/%1/").arg("light");

    if (key == BasicKeypad::Key_Div) {
        button->setIconUrl(path + "divide_normal.svg", path + "divide_hover.svg", path + "divide_press.svg");
    } else if (key == BasicKeypad::Key_Mult) {
        button->setIconUrl(path + "x_normal.svg", path + "x_hover.svg", path + "x_press.svg");
    } else if (key == BasicKeypad::Key_Min) {
        button->setIconUrl(path + "-_normal.svg", path + "-_hover.svg", path + "-_press.svg");
    } else if (key == BasicKeypad::Key_Plus) {
        button->setIconUrl(path + "+_normal.svg", path + "+_hover.svg", path + "+_press.svg");
    } else if (key == BasicKeypad::Key_Backspace) {
        button->setIconUrl(path + "clear_normal.svg", path + "clear_hover.svg", path + "clear_press.svg");
    } else if (key == BasicKeypad::Key_Clear) {
        button->setIconUrl(path + "AC_normal.svg", path + "AC_hover.svg", path + "AC_press.svg");
    } else if (key == BasicKeypad::Key_Percent) {
        button->setIconUrl(path + "%_normal.svg", path + "%_hover.svg", path + "%_press.svg");
    } else if (key == BasicKeypad::Key_Brackets) {
        button->setIconUrl(path + "( )_normal.svg", path + "( )_hover.svg", path + "( )_press.svg");
    }
    //connect(button, &IconButton::updateInterface, this, &BasicKeypad::updateInterface);
    return button;
}

BasicKeypad::BasicKeypad(QWidget *parent)
    : DWidget(parent),
      m_layout(new QGridLayout(this)),
      m_mapper(new QSignalMapper(this))
{
    m_layout->setMargin(0);
    m_layout->setSpacing(1);
    m_layout->setContentsMargins(0, 0, 0, 0);

    initButtons();
    initUI();

    connect(m_mapper, SIGNAL(mapped(int)), SIGNAL(buttonPressed(int)));
    //connect(DThemeManager::instance(), &DThemeManager::themeChanged, this, &BasicKeypad::handleThemeChanged);
}

BasicKeypad::~BasicKeypad()
{
}

DPushButton *BasicKeypad::button(Buttons key)
{
    return m_keys.value(key).first;
}

DSuggestButton *BasicKeypad::button()
{
    //return m_equal;
}

void BasicKeypad::animate(Buttons key)
{
    if (button(key)->text().isEmpty()) {
        IconButton *btn = static_cast<IconButton *>(button(key));
        btn->animate();
    } else {
        if (button(key)->text() == "=") {
            EqualButton *btn = dynamic_cast<EqualButton *>(button(key));
            btn->animate();
        } else {
            TextButton *btn = static_cast<TextButton *>(button(key));
            btn->animate();
        }
    }

}

void BasicKeypad::animate()
{
    //m_equal->setChecked(true);

    //QTimer::singleShot(100, this, [=] { m_equal->setChecked(false); });
}

void BasicKeypad::initButtons()
{
    const int count = sizeof(keyDescriptions) / sizeof(keyDescriptions[0]);
    for (int i = 0; i < count; ++i) {
        const KeyDescription *desc = keyDescriptions + i;
        DPushButton *button;

        if (desc->text.isEmpty()) {
            button = createSpecialKeyButton(desc->button);
        } else {
            if (desc->text == "=")
                button = new EqualButton(desc->text);
            else {
                button = new TextButton(desc->text);
                QFont font = button->font();
                font.setFamily("Noto Sans CJK SC");
                button->setFont(font);
            }
        }

        m_layout->addWidget(button, desc->row, desc->column, desc->rowcount, desc->columncount,
                            Qt::AlignHCenter | Qt::AlignBottom);
        const QPair<DPushButton *, const KeyDescription *> hashValue(button, desc);
        m_keys.insert(desc->button, hashValue);

        connect(static_cast<TextButton *>(button), &TextButton::updateInterface, [ = ] {update();});
        connect(button, &DPushButton::clicked, m_mapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
        connect(static_cast<TextButton *>(button), &TextButton::moveLeft, this, &BasicKeypad::moveLeft);
        connect(static_cast<TextButton *>(button), &TextButton::moveRight, this, &BasicKeypad::moveRight);
        m_mapper->setMapping(button, desc->button);
    }
}

void BasicKeypad::initUI()
{
    QHashIterator<Buttons, QPair<DPushButton *, const KeyDescription *>> i(m_keys);

    while (i.hasNext()) {
        i.next();
        i.value().first->setFocusPolicy(Qt::NoFocus);
    }

    button(Key_Div)->setObjectName("SymbolButton");
    button(Key_Mult)->setObjectName("SymbolButton");
    button(Key_Min)->setObjectName("SymbolButton");
    button(Key_Plus)->setObjectName("SymbolButton");

    this->setContentsMargins(12, 0, 13, 0);
}

void BasicKeypad::buttonThemeChanged(int type)
{
    QString path;
    if (type == 2)
        path = QString(":/assets/images/%1/").arg("dark");
    else
        path = QString(":/assets/images/%1/").arg("light");

    IconButton *btn = static_cast<IconButton *>(button(Key_Div));
    btn->setIconUrl(path + "divide_normal.svg", path + "divide_hover.svg", path + "divide_press.svg");
    btn = static_cast<IconButton *>(button(Key_Mult));
    btn->setIconUrl(path + "x_normal.svg", path + "x_hover.svg", path + "x_press.svg");
    btn = static_cast<IconButton *>(button(Key_Min));
    btn->setIconUrl(path + "-_normal.svg", path + "-_hover.svg", path + "-_press.svg");
    btn = static_cast<IconButton *>(button(Key_Plus));
    btn->setIconUrl(path + "+_normal.svg", path + "+_hover.svg", path + "+_press.svg");
    btn = static_cast<IconButton *>(button(Key_Backspace));
    btn->setIconUrl(path + "clear_normal.svg", path + "clear_hover.svg", path + "clear_press.svg", 1);
}
