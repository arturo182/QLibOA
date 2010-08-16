/**
  * QLibOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef QLIBOASIGNATUREHMAC_H
#define QLIBOASIGNATUREHMAC_H

#include "QLibOASignature.h"

namespace QLibOA
{
  class SignatureHMAC: public Signature
  {
    public:
      SignatureHMAC() { }

      QString getName() { return "HMAC-SHA1"; }
      QString hmacSha1(QByteArray data, QByteArray key);
      QString build(Request *request, Consumer *consumer, Token *token = NULL);
  };
}

#endif // QOASIGNATUREHMAC_H
