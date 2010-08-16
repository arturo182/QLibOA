/**
  * QLibOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#include "QLibOAToken.h"

#include <QtCore/QUrl>

using namespace QLibOA;

Token::Token(QString key, QString secret)
{
  m_key = key;
  m_secret = secret;
}

Token *Token::fromString(QString text)
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
