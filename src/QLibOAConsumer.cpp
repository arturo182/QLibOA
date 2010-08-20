/**
  * QLibOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  */

#include "QLibOAConsumer.h"

using namespace QLibOA;

Consumer::Consumer(QString key, QString secret, QString callback)
{
  m_key = key;
  m_secret = secret;
  m_callback = callback;
}
