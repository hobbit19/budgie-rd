/*
 * This file is part of budgie-rd
 *
 * Copyright © 2017-2018 Budgie Desktop Developers
 *
 * budgie-rd is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#include "raven.h"

#include <KWindowEffects>
#include <QBoxLayout>
#include <QDebug>
#include <QLabel>

namespace Raven
{
    Window::Window() : position(Position::Right)
    {
        // Push dock-type bits bits
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_X11NetWmWindowTypeDock);
        setAttribute(Qt::WA_ShowWithoutActivating);
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
        setFocusPolicy(Qt::NoFocus);
        setFixedSize(0, 0);

        rootWidget = new QWidget(this);
        auto layout = new QHBoxLayout;
        this->setLayout(layout);
        layout->addWidget(rootWidget);
        layout->setMargin(0);

        // Colour play
        rootWidget->setObjectName("raven-window");
        // rootWidget->setStyleSheet("#raven-window { background-color: rgba(1, 50, 67, 0.8); }");
        rootWidget->setStyleSheet("#raven-window { background-color: rgba(228, 241, 254, 0.8); }");

        auto rlayout = new QBoxLayout(QBoxLayout::TopToBottom);
        rootWidget->setLayout(rlayout);
        rootWidget->layout()->setMargin(0);

        // Mimicking look of old Budgie
        auto fakeHeader = new QWidget(rootWidget);
        rlayout->addWidget(fakeHeader, 0, Qt::AlignTop);
        fakeHeader->setStyleSheet("background-color: rgba(44, 62, 80, 0.99);");
        fakeHeader->setFixedSize(500, 35);

        auto lab = new QLabel("How Pretty Doth The Raven Seem\nIf only seen unto me", rootWidget);
        rlayout->addWidget(lab, 0, Qt::AlignCenter);
    }

    void Window::handleDismiss()
    {
        qDebug() << "Raven go bye bye";
        KWindowEffects::slideWindow(winId(), KWindowEffects::SlideFromLocation::RightEdge, 0);
        hide();
    }

    void Window::updateGeometry(QRect &rect)
    {
        QRect finalPosition;

        KWindowEffects::slideWindow(winId(), KWindowEffects::SlideFromLocation::RightEdge, 0);

        // We're always on the RHS for now with a size equalling 15% of width
        int width = (int)(rect.width() * 0.18);
        if (position == Position::Right) {
            finalPosition.setX((rect.x() + rect.width()) - width);
        } else {
            finalPosition.setX(rect.x());
        }
        finalPosition.setY(rect.y());
        finalPosition.setHeight(rect.height() - 37);
        finalPosition.setWidth(width);

        setFixedSize(finalPosition.width(), finalPosition.height());
        move(finalPosition.x(), finalPosition.y());

        // Be a tart, show off blurs
        KWindowEffects::enableBlurBehind(winId());
    }

    /**
     * For now we'll simply hide/show the window (relying on KWindowEffects to
     * slide) - however in future we'll need to handle Notifications vs Applets
     * view for primary view activation
     */
    void Window::toggleVisibility()
    {
        if (isVisible()) {
            hide();
        } else {
            show();
        }
    }
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=4 tabstop=4 expandtab:
 * :indentSize=4:tabSize=4:noTabs=true:
 */
