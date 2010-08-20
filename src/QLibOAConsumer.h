/**
  * QLibOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  */

#ifndef QLIBOACONSUMER_H
#define QLIBOACONSUMER_H

#include <QtCore/QDebug>

namespace QLibOA
{
  class Consumer
  {
    public:
      Consumer(QString key, QString secret, QString callback = QString::null);

      void setKey(QString key) { m_key = key; }
      QString getKey() { return m_key; }

      void setSecret(QString secret) { m_secret = secret; }
      QString getSecret() { return m_secret; }

      void setCallback(QString callback) { m_callback = callback; }
      QString getCallback() { return m_callback; }

      void debug() { qDebug() << "QLibOA::Consumer[\n  key =" << m_key << "\n  secret =" << m_secret << "\n  callback =" << m_callback << "\n]"; }

    private:
      QString m_key;
      QString m_secret;
      QString m_callback;
  };
}

#endif // QLIBOACONSUMER_H
