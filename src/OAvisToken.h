/**
  * OAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef OAVISTOKEN_H
#define OAVISTOKEN_H

#include <QtCore/QDebug>

namespace OAvis
{
  class Token
  {
    public:
      Token(QByteArray key, QByteArray secret);

      static Token *fromString(QByteArray text);

      void setKey(QByteArray key) { m_key = key; }
      QByteArray getKey() { return m_key; }

      void setSecret(QByteArray secret) { m_secret = secret; }
      QByteArray getSecret() { return m_secret; }

      void debug() { qDebug() << "OAvis::Token[\n  key=" << m_key << "\n  secret=" << m_secret << "\n]"; }

    private:
      QByteArray m_key;
      QByteArray m_secret;
  };
}

#endif // OAVISTOKEN_H
