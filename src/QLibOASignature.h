/**
  * QLibOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  */

#ifndef QLIBOASIGNATURE_H
#define QLIBOASIGNATURE_H

#include "QLibOAConsumer.h"
#include "QLibOAToken.h"

namespace QLibOA
{
  class Request;

  class Signature
  {
    public:
      Signature() { }

      virtual QString getName() = 0;
      virtual QString build(Request *request, Consumer *consumer, Token *token = 0) = 0;
      bool check(Request *request, Consumer *consumer, Token *token, QString sig) { return (build(request, consumer, token) == sig); }
  };
}

#endif // QLIBOASIGNATURE_H
