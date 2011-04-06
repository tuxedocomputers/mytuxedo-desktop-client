/*
 * Copyright (C) by Duncan Mac-Vicar P. <duncan@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#ifndef MIRALL_FOLDER_H
#define MIRALL_FOLDER_H

#include <QObject>
#include <QString>
#include <QStringList>

class QAction;
class QTimer;

namespace Mirall {

class FolderWatcher;

class Folder : public QObject
{
    Q_OBJECT

public:
    Folder(const QString &alias, const QString &path, QObject *parent = 0L);
    virtual ~Folder();

    /**
     * alias or nickname
     */
    QString alias() const;

    /**
     * local folder path
     */
    QString path() const;

    QAction *openAction() const;

    /**
     * Starts a sync operation
     *
     * If the list of changed files is known, it is passed.
     *
     * If the list of changed files is empty, the folder
     * implementation should figure it by itself of
     * perform a full scan of changes
     */
    virtual void startSync(const QStringList &pathList) = 0;

    /**
     * True if the folder is busy and can't initiate
     * a synchronization
     */
    virtual bool isBusy() const = 0;

protected:
    /**
     * The minimum amounts of seconds to wait before
     * doing a full sync to see if the remote changed
     */
    int pollInterval() const;

    /**
     * Sets minimum amounts of seconds that will separate
     * poll intervals
     */
    void setPollInterval(int seconds);

signals:

    void syncStarted();
    void syncFinished();

protected:
    FolderWatcher *_watcher;

private:

    QString _path;
    QAction *_openAction;
    // poll timer for remote syncs
    QTimer *_pollTimer;
    int _pollInterval;
    QString _alias;

protected slots:

    void slotPollTimerTimeout();

    /* called when the watcher detect a list of changed
       paths */
    void slotChanged(const QStringList &pathList);

    void slotOpenFolder();

    void slotSyncStarted();
    void slotSyncFinished();
};

}

#endif
