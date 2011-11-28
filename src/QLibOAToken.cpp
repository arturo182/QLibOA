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

#include "QLibOAToken.h"

#include <QtCore/QUrl>

using namespace QLibOA;

/*! \brief The constructor
 *
 * \param key Token_key value
 * \param secret Token_secret value
 */
Token::Token(const QString &key, const QString &secret)
{
  m_key = key;
  m_secret = secret;
}

/*! \brief Get new Token object from a string
 *
 *  This function is useful for generating Token from OAuth's request_token reply
 *  \param text A string containing oauth_token and oauth_token_secret values
 *  \return Pointer to Token object with info from \a text
 */
Token *Token::fromString(const QString &text)
{
  QUrl url("http://example.com/?"+text);

  QString key;
  QString secret;

  QList<QPair<QString, QString> > query = url.queryItems();
  for(int i = 0; i < query.count(); i++) {
    if(query.at(i).first == "oauth_token") {
      key = query.at(i).second.toAscii();
    } else if(query.at(i).first == "oauth_token_secret") {
      secret = query.at(i).second.toAscii();
    }
  }

  return new Token(key, secret);
}
