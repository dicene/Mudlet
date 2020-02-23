/***************************************************************************
 *   Copyright (C) 2008-2009 by Heiko Koehn - KoehnHeiko@googlemail.com    *
 *   Copyright (C) 2013-2014, 2017-2019 by Stephen Lyons                   *
 *                                               - slysven@virginmedia.com *
 *   Copyright (C) 2014 by Ahmed Charles - acharles@outlook.com            *
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


#include "dlgTriggerMaker.h"
#include "dlgTriggerEditor.h"

#include "mudlet.h"

#include "Host.h"
#include "TConsole.h"
#include "TTrigger.h"

#include "pre_guard.h"
#include <QDir>
#include "post_guard.h"

dlgTriggerMaker::dlgTriggerMaker(Host* pH)
: mpHost(pH)
{
    setupUi(this);

    updateList();

    QShortcut *returnShortcut = new QShortcut(QKeySequence("Return"), this);
    QObject::connect(returnShortcut, SIGNAL(activated()), createTrigger_pushButton, SLOT(click()));
}

dlgTriggerMaker::~dlgTriggerMaker()
{
    // Safety step, just in case:
    if (mpHost && mpHost->mpTriggerMaker) {
        mpHost->mpTriggerMaker = nullptr;
    }
}

void dlgTriggerMaker::updateList()
{
    lastLines_listWidget->clear();

    //lastLines_listWidget->addItem(QString("Test item 1!"));
    //lastLines_listWidget->addItem(QString("Name: " + mpHost->getName()));
    if (mpHost->mpConsole) {
        auto pConsole = mpHost->mpConsole;
        auto rawBuff = pConsole->buffer.rawBuffer;
        //lastLines_listWidget->addItem(QString("pConsole->getLineCount() = %1").arg(pConsole->getLineCount()));
        //lastLines_listWidget->addItem(QString("rawBuff.size() = %1").arg(rawBuff.size()));
        for (int i = 0; i < rawBuff.size() && i < 20; i++){
            lastLines_listWidget->addItem(QString("%1").arg(rawBuff[i]));
        }
        //lastLines_listWidget->addItem(QString("rawBuff[0] = \"%1\"").arg(rawBuff[0]));
        if (lastLines_listWidget->count() > 0) {
            lastLines_listWidget->item(lastLines_listWidget->count() - 1)->setSelected(true);
        }
        lastLines_listWidget->setFocus();
        activateWindow();
    }
}


void dlgTriggerMaker::on_createTrigger_pushButton_clicked()
{
    if (mpHost->mpConsole && lastLines_listWidget->selectedItems().size() > 0) {
        auto pConsole = mpHost->mpConsole;
        auto rawBuff = pConsole->buffer.rawBuffer;
        auto trigEdit = mpHost->mpEditorDialog;
        QString line = lastLines_listWidget->selectedItems()[0]->text();
        //mpHost->*CreateICW()
        pConsole->echo(QString("Selected line: %1\n").arg(line));
        //trigEdit->addTrigger(false);
        //trigEdit->treeWidget_triggers

        //TTrigger* pT;
        QStringList lineList;
        lineList.append(line);
        QList<int> propertyList;
        propertyList << REGEX_EXACT_MATCH;
        /*
//        if (parent.isEmpty()) {
            pT = new TTrigger("a", lineList, propertyList, false, mpHost);
//        } else {
//            TTrigger* pP = mpHost->getTriggerUnit()->findTrigger(parent);
//            if (!pP) {
//                return -1; //parent not found
//            }
//            pT = new TTrigger(pP, mpHost);
//            pT->setRegexCodeList(regexList, propertyList);
//        }
        pT->setIsFolder(false);
        pT->setIsActive(true);
        pT->setTemporary(false);
        pT->registerTrigger();
        pT->setScript(QString(""));
        //pT->setName( name );
        int id = pT->getID();
        pT->setName("New Trigger");
        mpHost->mpEditorDialog->mNeedUpdateData = true;*/

        //trigEdit->slot_save_edit();//save saveTrigger();
        QString name;
//        if (isFolder) {
//            name = tr("New trigger group");
//        } else {
            name = tr("New trigger");
//        }
        //QStringList lineList;
        //QList<int> linePropertyList;
        QString script = "";
        QStringList nameL;
        nameL << name;

        //QTreeWidgetItem* pParent = treeWidget_triggers->currentItem();
        QTreeWidgetItem* pNewItem = nullptr;
        TTrigger* pT = nullptr;

        //if (pParent) {
        /*if (false) {
            int parentID = pParent->data(0, Qt::UserRole).toInt();

            TTrigger* pParentTrigger = mpHost->getTriggerUnit()->getTrigger(parentID);
            if (pParentTrigger) {
                // insert new items as siblings unless the parent is a folder
                if (!pParentTrigger->isFolder()) {
                    // handle root items
                    if (!pParentTrigger->getParent()) {
                        goto ROOT_TRIGGER;
                    } else {
                        // insert new item as sibling of the clicked item
                        if (pParent->parent()) {
                            pT = new TTrigger(pParentTrigger->getParent(), mpHost);
                            pNewItem = new QTreeWidgetItem(pParent->parent(), nameL);
                            pParent->parent()->insertChild(0, pNewItem);
                        }
                    }
                } else {
                    pT = new TTrigger(pParentTrigger, mpHost);
                    pNewItem = new QTreeWidgetItem(pParent, nameL);
                    pParent->insertChild(0, pNewItem);
                }
            } else {
                goto ROOT_TRIGGER;
            }
        } else {*/
        //insert a new root item
        /*ROOT_TRIGGER:
            pT = new TTrigger(name, lineList, propertyList, false, mpHost);
            //pNewItem = new QTreeWidgetItem(mpTriggerBaseItem, nameL);
            //treeWidget_triggers->insertTopLevelItem(0, pNewItem);
        //}

        if (!pT) {
            return;
        }


        pT->setName(name);
        pT->setRegexCodeList(lineList, propertyList);
        pT->setScript("--script");
        //pT->setIsFolder(isFolder);
        pT->setIsFolder(false);
        pT->setIsActive(false);
        pT->setIsMultiline(false);
        pT->mStayOpen = 0;
        pT->setConditionLineDelta(0);
        pT->registerTrigger();
        int childID = pT->getID();

        */
        /*pNewItem->setData(0, Qt::UserRole, childID);
        QIcon icon;
        if (isFolder) {
            icon.addPixmap(QPixmap(QStringLiteral(":/icons/folder-red.png")), QIcon::Normal, QIcon::Off);
        } else {
            icon.addPixmap(QPixmap(QStringLiteral(":/icons/document-save-as.png")), QIcon::Normal, QIcon::Off);
        }
        pNewItem->setIcon(0, icon);
        if (pParent) {
            pParent->setExpanded(true);
        }
        mpTriggersMainArea->lineEdit_trigger_name->clear();
        mpTriggersMainArea->groupBox_perlSlashGOption->setChecked(false);

        clearDocument(mpSourceEditorEdbee); // New Trigger

        mpTriggersMainArea->lineEdit_trigger_command->clear();
        mpTriggersMainArea->groupBox_filterTrigger->setChecked(false);
        mpTriggersMainArea->spinBox_stayOpen->setValue(0);
        mpTriggersMainArea->spinBox_lineMargin->setValue(0);
        mpTriggersMainArea->groupBox_multiLineTrigger->setChecked(false);

        mpTriggersMainArea->pushButtonFgColor->setChecked(false);
        mpTriggersMainArea->pushButtonBgColor->setChecked(false);
        mpTriggersMainArea->groupBox_triggerColorizer->setChecked(false);

        mpCurrentTriggerItem = pNewItem;
        treeWidget_triggers->setCurrentItem(pNewItem);
        showInfo(msgInfoAddTrigger);
        slot_trigger_selected(treeWidget_triggers->currentItem());
        */
        TLuaInterpreter* pLuaInterpreter = mpHost->getLuaInterpreter();
        pLuaInterpreter->startPermSubstringTrigger(name, QString(""), lineList, script);
        if (mpHost->mpEditorDialog)
        {
            mpHost->mpEditorDialog->slot_show_triggers();
            //mpHost->mpEditorDialog->mNeedUpdateData = true;
        }

        //trigEdit->slot_save_edit();//save saveTrigger();
        //return 1;
    }
    hide();
}

void dlgTriggerMaker::on_cancel_pushButton_clicked()
{
    hide();
}
