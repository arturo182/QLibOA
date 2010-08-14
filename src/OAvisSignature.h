/**
  * OAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef OAVISSIGNATURE_H
#define OAVISSIGNATURE_H

#include "OAvisConsumer.h"
#include "OAvisToken.h"

namespace OAvis
{
  class Request;

  class Signature
  {
    public:
      Signature() { }

      virtual QByteArray getName() = 0;
      virtual QByteArray build(Request *request, Consumer *consumer, Token *token = 0) = 0;
      bool check(Request *request, Consumer *consumer, Token *token, QByteArray sig) { return (build(request, consumer, token) == sig); }
  };
}

#endif // OAVISSIGNATURE_H
