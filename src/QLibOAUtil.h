/**
  * QLibOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  */

#ifndef QLIBOAUTIL_H
#define QLIBOAUTIL_H

#include "QLibOAConsumer.h"
#include "QLibOAToken.h"
#include "QLibOARequest.h"

namespace QLibOA
{
  class Util
  {
    public:
      Util() { }

      static QString encode(QString text);
      static QString decode(QString text);
      static QString genKey(Consumer *consumer = 0, Token *token = 0);
      static QLibOA::ParamMap urlToParams(QString url);
      static QLibOA::ParamMap mergeParams(QLibOA::ParamMap first, QLibOA::ParamMap second);
      static QString buildHTTPQuery(QLibOA::ParamMap params, bool skipOAuth = false);
  };
}

#endif // QLIBOAUTIL_H
