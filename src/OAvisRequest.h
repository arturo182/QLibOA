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
      Request(OAvis::HttpMethod method = OAvis::GET, QString url = QString::null, OAvis::ParamMap params = OAvis::ParamMap());

      void setParam(QString key, QString value, bool duplicates = true);
      QString getParam(QString key) { return m_params.value(key); }
      QList<QString> getParamAll(QString key) { QList<QString> params = m_params.values(key); qSort(params); return params; }
      void unsetParam(QString key) { m_params.remove(key); }

      OAvis::ParamMap getParams() { return m_params; }
      QString getSignableParams();

      QString getBaseString();
      QString getNormalizedHTTPMethod();
      QString getNormalizedUrl();

      static QString genTimestamp();
      static QString genNonce();

      QString toUrl();
      QString toPostdata();
      QString toHeader(QString realm = QString::null);

      void sign(OAvis::SignatureMethod method = OAvis::HMAC_SHA1, Consumer *consumer = NULL, Token *token = NULL);

      static Request *fromRequest(OAvis::HttpMethod method = OAvis::GET, QString url = NULL, OAvis::ParamMap params = OAvis::ParamMap());
      static Request *fromConsumerAndToken(Consumer *consumer, Token *token = NULL, OAvis::HttpMethod method = OAvis::GET, QString url = QString::null, OAvis::ParamMap params = OAvis::ParamMap());

      void debug();

    private:
      OAvis::ParamMap m_params;
      OAvis::HttpMethod m_method;
      QString m_url;
  };
}

#endif // OAVISREQUEST_H
