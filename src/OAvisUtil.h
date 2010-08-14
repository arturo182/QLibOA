/**
  * OAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef OAVISUTIL_H
#define OAVISUTIL_H

#include "OAvisConsumer.h"
#include "OAvisToken.h"
#include "OAvisRequest.h"

namespace OAvis
{
  class Util
  {
    public:
      Util() { }

      static QByteArray encode(QByteArray text);
      static QByteArray decode(QByteArray text);
      static QByteArray genKey(Consumer *consumer = 0, Token *token = 0);
      static OAvis::ParamMap urlToParams(QByteArray url);
      static OAvis::ParamMap mergeParams(OAvis::ParamMap first, OAvis::ParamMap second);
      static QByteArray buildHTTPQuery(OAvis::ParamMap params);
  };
}

#endif // OAVISUTIL_H
