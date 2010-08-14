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

      static QString encode(QString text);
      static QString decode(QString text);
      static QString genKey(Consumer *consumer = 0, Token *token = 0);
      static OAvis::ParamMap urlToParams(QString url);
      static OAvis::ParamMap mergeParams(OAvis::ParamMap first, OAvis::ParamMap second);
      static QString buildHTTPQuery(OAvis::ParamMap params);
  };
}

#endif // OAVISUTIL_H
