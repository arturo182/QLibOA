/**
  * QLibOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef QLIBOASIGNATUREPLAINTEXT_H
#define QLIBOASIGNATUREPLAINTEXT_H

#include "QLibOASignature.h"
#include "QLibOAUtil.h"

namespace QLibOA
{
  class SignaturePlainText: public Signature
  {
    public:
      SignaturePlainText() { }

      QString getName() { return "PLAINTEXT"; }
      QString build(Request *request, Consumer *consumer, Token *token = NULL) { Q_UNUSED(request); return Util::genKey(consumer, token); }
  };
}

#endif // QLIBOASIGNATUREPLAINTEXT_H
