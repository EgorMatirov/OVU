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

#ifndef ENTRY_ELEMENT_H
#define ENTRY_ELEMENT_H

#include "Element.h"

#include "TitleElement.h"
#include "ContentElement.h"
#include "ThumbnailElement.h"
#include "AcquisitionElement.h"
#include "NavigationFeedElement.h"
#include "AuthorElement.h"

#include <QString>
#include <QUrl>
#include <QList>

class EntryElement : public Element
{

    Q_OBJECT

public:
    explicit EntryElement();
    ~EntryElement();

    Element::ElementType type() const override;

    TitleElement *title() const;
    void setTitle(TitleElement *value);

    ContentElement *content() const;
    void setContent(ContentElement *content);

    ThumbnailElement *thumbnail() const;
    void setThumbnail(ThumbnailElement *thumbnail);

    QUrl baseUrl() const;
    void setBaseUrl(const QUrl &baseUrl);

    QList<AcquisitionElement *> acquisitions() const;
    void setAcquisitions(const QList<AcquisitionElement *> &acquisitions);

    void appendAcquisition(AcquisitionElement *acquisition);

    NavigationFeedElement *navigationFeed() const;
    void setNavigationFeed(NavigationFeedElement *navigationFeed);

    QList<AuthorElement *> authors() const;
    void setAuthors(const QList<AuthorElement *> &authors);
    void appendAuthor(AuthorElement *author);

    bool isNextEntry() const;
    void setIsNextEntry(bool isNextEntry);

private:
    TitleElement *m_title;
    ContentElement *m_content;
    ThumbnailElement *m_thumbnail;
    NavigationFeedElement *m_navigationFeed;
    QUrl m_baseUrl;
    QList<AcquisitionElement*> m_acquisitions;
    QList<AuthorElement*> m_authors;
    bool m_isNextEntry;
};

#endif // ENTRY_ELEMENT_H
