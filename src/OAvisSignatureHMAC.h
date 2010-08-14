/**
  * OAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef OAVISSIGNATUREHMAC_H
#define OAVISSIGNATUREHMAC_H

#include "OAvisSignature.h"

namespace OAvis
{
  class SignatureHMAC: public Signature
  {
    public:
      SignatureHMAC() { }

      QByteArray getName() { return "HMAC-SHA1"; }
      QByteArray hmacSha1(QByteArray data, QByteArray key);
      QByteArray build(Request *request, Consumer *consumer, Token *token = NULL);
  };
}

#endif // QOASIGNATUREHMAC_H
