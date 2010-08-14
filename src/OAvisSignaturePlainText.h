/**
  * OAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef OAVISSIGNATUREPLAINTEXT_H
#define OAVISSIGNATUREPLAINTEXT_H

#include "OAvisSignature.h"
#include "OAvisUtil.h"

namespace OAvis
{
  class SignaturePlainText: public Signature
  {
    public:
      SignaturePlainText() { }

      QByteArray getName() { return "PLAINTEXT"; }
      QByteArray build(Request *request, Consumer *consumer, Token *token = NULL) { Q_UNUSED(request); return Util::genKey(consumer, token); }
  };
}

#endif // OAVISSIGNATUREPLAINTEXT_H
