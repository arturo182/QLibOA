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

QByteArray Util::encode(QByteArray text)
{
  return QUrl::toPercentEncoding(text);
}

QByteArray Util::decode(QByteArray text)
{
  return QUrl::fromPercentEncoding(text).toAscii();
}

QByteArray Util::genKey(Consumer *consumer, Token *token)
{
  if(consumer && token) {
    QByteArray consumerSecret = consumer->getSecret();
    QByteArray tokenSecret = (token)?token->getSecret():"";

    consumerSecret = Util::encode(consumerSecret);
    tokenSecret = Util::encode(tokenSecret);

    return consumerSecret + "&" + tokenSecret;
  } else {
    return "&";
  }
}

OAvis::ParamMap Util::urlToParams(QByteArray url)
{
  OAvis::ParamMap params;

  QUrl qurl(url);
  QList<QPair<QString, QString> > query = qurl.queryItems();
  for(int i = 0; i < query.size(); i++) {
    QByteArray key = Util::decode(query.at(i).first.toAscii());
    QByteArray value = Util::decode(query.at(i).second.toAscii());

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

QByteArray Util::buildHTTPQuery(OAvis::ParamMap params)
{
  if(params.size() == 0) {
    return NULL;
  }

  OAvis::ParamMap::iterator i = params.begin();
  while(i != params.end()) {
    QByteArray key = Util::encode(i.key());
    QByteArray value = Util::encode(i.value());

    params.remove(i.key());
    params.insert(key, value);

    i++;
  }

  //TODO: sortowanie kluczy
  QList<QByteArray> keys = params.keys();
  //qDebug() << keys;

  QByteArray out;
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
