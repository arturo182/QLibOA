/**
  * QLibOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  */

#ifndef QLIBOATOKEN_H
#define QLIBOATOKEN_H

#include <QtCore/QDebug>

namespace QLibOA
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

      void debug() { qDebug() << "QLibOA::Token[\n  key=" << m_key << "\n  secret=" << m_secret << "\n]"; }

    private:
      QString m_key;
      QString m_secret;
  };
}

#endif // QLIBOATOKEN_H
