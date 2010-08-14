/**
  * OAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#include "OAvisConsumer.h"

using namespace OAvis;

Consumer::Consumer(QByteArray key, QByteArray secret, QByteArray callback)
{
  m_key = key;
  m_secret = secret;
  m_callback = callback;
}
