/**
  * QLibOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#include "QLibOAUtil.h"

#include <QtCore/QUrl>
#include <QtCore/QList>
#include <QtCore/QPair>

using namespace QLibOA;

QString Util::encode(QString text)
{
  return QUrl::toPercentEncoding(text);
}

QString Util::decode(QString text)
{
  return QUrl::fromPercentEncoding(text.toUtf8());
}

QString Util::genKey(Consumer *consumer, Token *token)
{
  QByteArray key;

  if(consumer) {
    key.append(Util::encode(consumer->getSecret()));
  }

  key.append("&");

  if(token) {
    key.append(Util::encode(token->getSecret()));
  }

  return key;
}

QLibOA::ParamMap Util::urlToParams(QString url)
{
  QLibOA::ParamMap params;

  QUrl qurl(url);
  QList<QPair<QString, QString> > query = qurl.queryItems();
  for(int i = 0; i < query.size(); i++) {
    QString key = Util::decode(query.at(i).first.toAscii());
    QString value = Util::decode(query.at(i).second.toAscii());

    params.insert(key, value);
  }

  return params;
}

QLibOA::ParamMap Util::mergeParams(QLibOA::ParamMap first, QLibOA::ParamMap second)
{
  QLibOA::ParamMap::iterator i = second.begin();
  while(i != second.end()) {
    first.replace(i.key(), i.value());
    i++;
  }

  return first;
}

QString Util::buildHTTPQuery(QLibOA::ParamMap params)
{
  if(params.size() == 0) {
    return NULL;
  }

  QLibOA::ParamMap::iterator i = params.begin();
  while(i != params.end()) {
    QString key = Util::encode(i.key());
    QString value = Util::encode(i.value());

    params.remove(i.key());
    params.insert(key, value);

    i++;
  }

  //TODO: sortowanie kluczy
  QList<QString> keys = params.keys();
  //qDebug() << keys;

  QString out;
  i = params.begin();
  while(i != params.end()) {
    out.append(i.key());
    out.append("=");
    out.append(i.value());

    i++;

    if(i != params.end()) {
      out.append("&");
    }
  }

  return out;
}