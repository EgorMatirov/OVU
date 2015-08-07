#include "ThumbnailElement.h"

ThumbnailElement::ThumbnailElement(const QString &url) :
    m_url(url)
{
}

Element::ElementType ThumbnailElement::type() const
{
    return Element::ThumbnailType;
}

QString ThumbnailElement::url() const
{
    if( m_url.isEmpty() ) {
        return QString();
    }
    if( QUrl(m_url).isRelative() ) {
        return m_baseUrl.toString() + m_url;
    } else {
        return m_url;
    }
}

void ThumbnailElement::setUrl(const QString &url)
{
    m_url = url;
}
QUrl ThumbnailElement::baseUrl() const
{
    return m_baseUrl;
}

void ThumbnailElement::setBaseUrl(const QUrl &baseUrl)
{
    m_baseUrl = baseUrl;
}

