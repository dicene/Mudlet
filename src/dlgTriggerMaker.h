#ifndef MUDLET_DLGTRIGGERMAKER_H
#define MUDLET_DLGTRIGGERMAKER_H

/***************************************************************************
 *   Copyright (C) 2008-2009 by Heiko Koehn - KoehnHeiko@googlemail.com    *
 *   Copyright (C) 2014 by Ahmed Charles - acharles@outlook.com            *
 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "pre_guard.h"
#include "ui_trigger_maker.h"
#include <QPointer>
#include "post_guard.h"

class Host;

class dlgTriggerMaker : public QMainWindow, public Ui::trigger_maker
{
    Q_OBJECT

public:
    Q_DISABLE_COPY(dlgTriggerMaker)
    dlgTriggerMaker(Host*);
    ~dlgTriggerMaker();
    void updateList();

private slots:
    void on_createTrigger_pushButton_clicked();

    void on_cancel_pushButton_clicked();

private:
    QPointer<Host> mpHost;
};

#endif // MUDLET_DLGTRIGGERMAKER_H