/**
  * OAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#include "OAvisUtil.h"

#include <QtCore/QUrl>
#include <QtCore/QList>
#include <QtCore/QPair>

using namespace OAvis;

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
  if(consumer && token) {
    QString consumerSecret = consumer->getSecret();
    QString tokenSecret = (token)?token->getSecret():"";

    consumerSecret = Util::encode(consumerSecret);
    tokenSecret = Util::encode(tokenSecret);

    return consumerSecret + "&" + tokenSecret;
  } else {
    return "&";
  }
}

OAvis::ParamMap Util::urlToParams(QString url)
{
  OAvis::ParamMap params;

  QUrl qurl(url);
  QList<QPair<QString, QString> > query = qurl.queryItems();
  for(int i = 0; i < query.size(); i++) {
    QString key = Util::decode(query.at(i).first.toAscii());
    QString value = Util::decode(query.at(i).second.toAscii());

    params.insert(key, value);
  }

  return params;
}

OAvis::ParamMap Util::mergeParams(OAvis::ParamMap first, OAvis::ParamMap second)
{
  OAvis::ParamMap::iterator i = second.begin();
  while(i != second.end()) {
    first.replace(i.key(), i.value());
    i++;
  }

  return first;
}

QString Util::buildHTTPQuery(OAvis::ParamMap params)
{
  if(params.size() == 0) {
    return NULL;
  }

  OAvis::ParamMap::iterator i = params.begin();
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
