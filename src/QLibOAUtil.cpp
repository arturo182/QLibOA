/************************************************************************
 * QLibOA                                                               *
 * Copyright (C) 2010 arturo182 <arturo182@tlen.pl>                     *
 *                                                                      *
 * This library is free software: you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation; version 3 only.                        *
 *                                                                      *
 * This library is distributed in the hope that it will be useful,      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with this library. If not, see <http://www.gnu.org/licenses/>. *
 ************************************************************************/

#include "QLibOAUtil.h"

#include <QtCore/QUrl>
#include <QtCore/QList>
#include <QtCore/QPair>

using namespace QLibOA;

/*! \brief Encodes \a text using the RFC3986 mechanism
 *
 *  To learn more about parameters encoding, read <a href="http://oauth.net/core/1.0/#encoding_parameters">this</a>
 *  \param text A string to encode
 *  \return Encoded string
 */
QString Util::encode(const QString &text)
{
  return QUrl::toPercentEncoding(text);
}

/*! \brief Decodes text encoded with Util::encode back to normal
 *  \param text A string to decode
 *  \return Decoded string
 */
QString Util::decode(const QString &text)
{
  return QUrl::fromPercentEncoding(text.toUtf8());
}

/*! \brief Generate key for request signing

 *  More info <a href="http://oauth.net/core/1.0/#rfc.section.9.4.1">here</a>
 *  \param consumer A pointer to Consumer object with consumer info
 *  \param token A pointer to Token object with token info
 *  \return Key used for signing requests
 */
QString Util::genKey(Consumer *consumer, Token *token)
{
  QByteArray key;

  if(consumer) {
    key.append(Util::encode(consumer->secret()));
  }

  key.append("&");

  if(token) {
    key.append(Util::encode(token->secret()));
  }

  return key;
}

/*! \brief Converts url to parameter map
 *  \param url URL to convert
 *  \return Map of converted parameters
 */
QVariantMap Util::urlToParams(const QString &url)
{
  QVariantMap params;

  QUrl qurl(url);
  QList<QPair<QString, QString> > query = qurl.queryItems();
  for(int i = 0; i < query.size(); i++) {
    QString key = Util::decode(query.at(i).first.toAscii());
    QString value = Util::decode(query.at(i).second.toAscii());

    params.insert(key, value);
  }

  return params;
}

/*! \brief Merges two parameter maps
 *
 *  This function iterates trough all \a second items and inserts them to \a first,
 *  if there is already a parameter with same key in \a first, it's replaced with \a second's value.
 *  \param first First parameter map
 *  \param second Second parameter map
 *  \return A map of merged parameter maps
 */
QVariantMap Util::mergeParams(const QVariantMap &first, const QVariantMap &second)
{
  QVariantMap merged = first;

  QMapIterator<QString, QVariant> it(second);
  while(it.hasNext()) {
    it.next();

    merged.insert(it.key(), it.value());
  }

  return merged;
}

/*! \brief Returns parameters \a params as a string
 *
 *  The string is formated like this: par1=var1&par2=var2
 *  \param params Parameters to convert
 *  \param skipOAuth Should parameters starting with oauth_ be omitted
 *  \return A string of sorted and encoded parameters
 */
QString Util::buildHTTPQuery(const QVariantMap &params, bool skipOAuth)
{
  if(params.size() == 0) {
    return NULL;
  }

  QString out;
  QMapIterator<QString, QVariant> it(params);
  while(it.hasNext()) {
    it.next();

    QString key = Util::encode(it.key());
    QString value = Util::encode(it.value().toString());

    if(!(skipOAuth && key.contains("oauth_"))) {
        out += QString("%1=%2&").arg(key).arg(value);
    }
  }

  if(out.endsWith("&")) {
    out.chop(1);
  }

  return out;
}
