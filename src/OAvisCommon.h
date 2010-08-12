/**
  * OAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef OAVIS_H
#define OAVIS_H

#include <QtCore/QDebug>
#include <QtCore/QMultiMap>

namespace OAvis
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

  inline QDebug operator<<(QDebug debug, const OAvis::HttpMethod method)
  {
    debug.nospace() << "TweetAuth::HttpMethod(";
    switch(method) {
      case OAvis::GET:
        debug << "GET";
      break;

      case OAvis::POST:
        debug << "POST";
      break;
    }

    debug << ")";

    return debug.space();
  }

  inline QDebug operator<<(QDebug debug, const OAvis::ParamMap params)
  {
    debug.nospace() << "TweetAuth::ParamMap(\n";

    OAvis::ParamMap::const_iterator i = params.begin();
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

#endif // OAVIS_H
