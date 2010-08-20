/**
  * QLibOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  */

#ifndef QLIBOAREQUEST_H
#define QLIBOAREQUEST_H

#include "QLibOAConsumer.h"
#include "QLibOAToken.h"
#include "QLibOASignature.h"
#include "QLibOACommon.h"

namespace QLibOA
{
  class Request
  {
    public:
      Request(QLibOA::HttpMethod method = QLibOA::GET, QString url = QString::null, QLibOA::ParamMap params = QLibOA::ParamMap());

      void setParam(QString key, QString value, bool duplicates = true);
      QString getParam(QString key) { return m_params.value(key); }
      QList<QString> getParamAll(QString key) { QList<QString> params = m_params.values(key); qSort(params); return params; }
      void unsetParam(QString key) { m_params.remove(key); }

      QLibOA::ParamMap getParams() { return m_params; }
      QString getSignableParams();

      QString getBaseString();
      QString getNormalizedHTTPMethod();
      QString getNormalizedUrl();

      static QString genTimestamp();
      static QString genNonce();

      QString toUrl();
      QString toGetdata();
      QString toPostdata();
      QString toHeader(QString realm = QString::null);

      void sign(QLibOA::SignatureMethod method = QLibOA::HMAC_SHA1, Consumer *consumer = NULL, Token *token = NULL);

      static Request *fromRequest(QLibOA::HttpMethod method = QLibOA::GET, QString url = NULL, QLibOA::ParamMap params = QLibOA::ParamMap());
      static Request *fromConsumerAndToken(Consumer *consumer, Token *token = NULL, QLibOA::HttpMethod method = QLibOA::GET, QString url = QString::null, QLibOA::ParamMap params = QLibOA::ParamMap());

      void debug();

    private:
      QLibOA::ParamMap m_params;
      QLibOA::HttpMethod m_method;
      QString m_url;
  };
}

#endif // QLIBOAREQUEST_H
