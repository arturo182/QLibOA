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
      Token(QString key, QString secret);

      static Token *fromString(QString text);

      void setKey(QString key) { m_key = key; }
      QString getKey() { return m_key; }

      void setSecret(QString secret) { m_secret = secret; }
      QString getSecret() { return m_secret; }

      void debug() { qDebug() << "OAvis::Token[\n  key=" << m_key << "\n  secret=" << m_secret << "\n]"; }

    private:
      QString m_key;
      QString m_secret;
  };
}

#endif // OAVISTOKEN_H
