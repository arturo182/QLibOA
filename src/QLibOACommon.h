/**
  * QLibOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef QLIBOA_H
#define QLIBOA_H

#include <QtCore/QDebug>
#include <QtCore/QMultiMap>

namespace QLibOA
{
  typedef QMultiMap<QString, QString> ParamMap;

  enum HttpMethod
  {
    GET = 0,
    POST = 1
  };

  enum SignatureMethod
  {
    HMAC_SHA1 = 0,
    PLAINTEXT = 1
  };

  inline QDebug operator<<(QDebug debug, const QLibOA::HttpMethod method)
  {
    debug.nospace() << "TweetAuth::HttpMethod(";
    switch(method) {
      case QLibOA::GET:
        debug << "GET";
      break;

      case QLibOA::POST:
        debug << "POST";
      break;
    }

    debug << ")";

    return debug.space();
  }

  inline QDebug operator<<(QDebug debug, const QLibOA::ParamMap params)
  {
    debug.nospace() << "TweetAuth::ParamMap(\n";

    QLibOA::ParamMap::const_iterator i = params.begin();
    while(i != params.end()) {
      debug << "    " << i.key() << " = " << i.value();
      i++;

      if(i != params.end()) {
        debug << "\n";
      }
    }
    debug << "\n  )";

    return debug.space();
  }

}

#endif // QLIBOA_H
