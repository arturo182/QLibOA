/**
  * QLibOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  */

#include "QLibOASignatureHMAC.h"
#include "QLibOAUtil.h"

#include <QtCore/QCryptographicHash>

using namespace QLibOA;

QString SignatureHMAC::hmacSha1(QByteArray data, QByteArray key)
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

QString SignatureHMAC::build(Request *request, Consumer *consumer, Token *token)
{
  QString base = request->getBaseString();
  QString key = Util::genKey(consumer, token);

  return hmacSha1(base.toUtf8(), key.toUtf8());
}
