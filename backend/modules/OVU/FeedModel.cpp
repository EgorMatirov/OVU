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

#include "FeedModel.h"

FeedModel::FeedModel()
{
}

FeedModel::~FeedModel()
{
    qDeleteAll(m_entries);
}

int FeedModel::rowCount(const QModelIndex &parent) const
{
    if( !parent.isValid() ) {
        return m_entries.size();
    }
    return 0;
}

QVariant FeedModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index)
    Q_UNUSED(role)
    if( index.isValid() ) {
        EntryElement *entry = m_entries.at(index.row());
        switch(role) {
        case Qt::DisplayRole:
            return entry->content()->value();
        case TitleRole:
            return entry->title()->value();
        case ThumbnailRole:
            return entry->thumbnail()->url();
        case NavigationLinkRole:
            return entry->navigationFeed()->url();
        case AcquisitionsRole: {
            QList<QVariant> acquisitions;
            foreach( AcquisitionElement *acquisition, entry->acquisitions() ) {
                QList<QVariant> info;
                info << acquisition->contentType()
                     << acquisition->url()
                     << acquisition->isPaid()
                     << acquisition->isSample();
                acquisitions.append(QVariant(info));
            }
            return acquisitions;
        }
        case IsAcquisitionRole:
            return !entry->acquisitions().isEmpty();
            break;
        case AuthorsRole: {
            QStringList authors;
            foreach( AuthorElement *author, entry->authors() ) {
                authors.append(author->name()->value());
            }
            return authors;
        }
        case IsNextLinkRole:
            return entry->isNextEntry();
        }
    }
    return QVariant();
}

QModelIndex FeedModel::index(int row, int column,
                             const QModelIndex &parent) const
{
    if( parent.isValid() ) {
        return QModelIndex();
    }

    if( column != 0 ) {
        return QModelIndex();
    }

    if( row < 0 || row >= m_entries.size() ) {
        return QModelIndex();
    }
    EntryElement *entry = m_entries[row];
    return createIndex(row, column, entry);
}

Qt::ItemFlags FeedModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
}

QHash<int, QByteArray> FeedModel::roleNames() const
{
    QHash<int, QByteArray> hash;
    hash[Qt::DisplayRole] = "content";
    hash[TitleRole] = "title";
    hash[ThumbnailRole] = "thumbnail";
    hash[NavigationLinkRole] = "navigationLink";
    hash[AcquisitionsRole] = "acquisitions";
    hash[IsAcquisitionRole] = "isAcquisition";
    hash[AuthorsRole] = "authors";
    hash[IsNextLinkRole] = "isNextLink";
    return hash;
}

bool FeedModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if( 0 <= row  && row+count-1 < m_entries.size() && !parent.isValid() ) {
        beginRemoveRows(parent, row, row+count-1);
        for(int i = 0; i<count; ++i) {
            m_entries.removeAt(row);
        }
        endRemoveRows();
        return true;
    }
    return false;
}

void FeedModel::appendEntry(EntryElement *entry)
{
    QModelIndex root;
    beginInsertRows(root, rowCount(root),rowCount(root));
    m_entries.append(entry);
    endInsertRows();
}
