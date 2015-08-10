/**
  * This file is part of OVU.
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program. If not, see <http://www.gnu.org/licenses/>.
  *
  * Copyright (C) 2015 Mikhail Ivchenko <ematirov@gmail.com>
  *
  **/

#ifndef FEED_MODEL_H
#define FEED_MODEL_H

#include "Elements/EntryElement.h"

#include <QAbstractListModel>

class FeedModel : public QAbstractListModel {

    Q_OBJECT

public:
    explicit FeedModel();
    ~FeedModel();

    enum Roles{
        TitleRole = Qt::UserRole,
        ThumbnailRole,
        NavigationLinkRole,
        IsAcquisitionRole,
        AuthorsRole,
        IsNextLinkRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int,QByteArray> roleNames() const override;
    bool removeRows(int row, int count, const QModelIndex &parent);

public:
    // Our own functions.
    void appendEntry(EntryElement *entry);

private:
    QList<EntryElement*> m_entries;
};

#endif // FEED_MODEL_H
