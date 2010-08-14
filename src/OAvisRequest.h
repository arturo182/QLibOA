/**
  * OAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef OAVISREQUEST_H
#define OAVISREQUEST_H

#include "OAvisConsumer.h"
#include "OAvisToken.h"
#include "OAvisSignature.h"
#include "OAvisCommon.h"

namespace OAvis
{
  class Request
  {
    public:
      Request(OAvis::HttpMethod method = OAvis::GET, QByteArray url = QByteArray(), OAvis::ParamMap params = OAvis::ParamMap());

      void setParam(QByteArray key, QByteArray value, bool duplicates = true);
      QByteArray getParam(QByteArray key) { return m_params.value(key); }
      QList<QByteArray> getParamAll(QByteArray key) { QList<QByteArray> params = m_params.values(key); qSort(params); return params; }
      void unsetParam(QByteArray key) { m_params.remove(key); }

      OAvis::ParamMap getParams() { return m_params; }
      QByteArray getSignableParams();

      QByteArray getBaseString();
      QByteArray getNormalizedHTTPMethod();
      QByteArray getNormalizedUrl();

      static QByteArray genTimestamp();
      static QByteArray genNonce();

      QByteArray toUrl();
      QByteArray toPostdata();
      QByteArray toHeader(QByteArray realm = QByteArray());

      void sign(OAvis::SignatureMethod method = OAvis::HMAC_SHA1, Consumer *consumer = NULL, Token *token = NULL);

      static Request *fromRequest(OAvis::HttpMethod method = OAvis::GET, QByteArray url = NULL, OAvis::ParamMap params = OAvis::ParamMap());
      static Request *fromConsumerAndToken(Consumer *consumer, Token *token = NULL, OAvis::HttpMethod method = OAvis::GET, QByteArray url = QByteArray(), OAvis::ParamMap params = OAvis::ParamMap());

      void debug();

    private:
      OAvis::ParamMap m_params;
      OAvis::HttpMethod m_method;
      QByteArray m_url;
  };
}

#endif // OAVISREQUEST_H
