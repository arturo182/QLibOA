/**
  * OAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef OAVISCONSUMER_H
#define OAVISCONSUMER_H

#include <QtCore/QDebug>

namespace OAvis
{
  class Consumer
  {
    public:
      Consumer(QByteArray key, QByteArray secret, QByteArray callback = QByteArray());

      void setKey(QByteArray key) { m_key = key; }
      QByteArray getKey() { return m_key; }

      void setSecret(QByteArray secret) { m_secret = secret; }
      QByteArray getSecret() { return m_secret; }

      void setCallback(QByteArray callback) { m_callback = callback; }
      QByteArray getCallback() { return m_callback; }

      void debug() { qDebug() << "OAvis::Consumer[\n  key =" << m_key << "\n  secret =" << m_secret << "\n  callback =" << m_callback << "\n]"; }

    private:
      QByteArray m_key;
      QByteArray m_secret;
      QByteArray m_callback;
  };
}

#endif // OAVISCONSUMER_H
