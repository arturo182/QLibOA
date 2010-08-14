/**
  * OAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#include "OAvisSignatureHMAC.h"
#include "OAvisUtil.h"

#include <QtCore/QDebug>
#include <QtCore/QCryptographicHash>

using namespace OAvis;

QByteArray SignatureHMAC::hmacSha1(QByteArray data, QByteArray key)
{
  int size = 64;

  QByteArray opad = QString(0x5C).repeated(size).toAscii();
  QByteArray ipad = QString(0x36).repeated(size).toAscii();

  if(key.length() > size) {
    key = QCryptographicHash::hash(key, QCryptographicHash::Sha1).leftJustified(size, 0x00);
  } else {
    key = key.leftJustified(size, 0x00);
  }

  for(int i = 0; i < key.size() - 1; i++) {
    opad[i] = opad[i] ^ key[i];
    ipad[i] = ipad[i] ^ key[i];
  }

  data = QCryptographicHash::hash(ipad + data, QCryptographicHash::Sha1);
  return QCryptographicHash::hash(opad + data, QCryptographicHash::Sha1).toBase64();
}

QByteArray SignatureHMAC::build(Request *request, Consumer *consumer, Token *token)
{
  QByteArray base = request->getBaseString();
  QByteArray key = Util::genKey(consumer, token);

  qDebug() << "base" << "key";
  return hmacSha1(base, key);
}
