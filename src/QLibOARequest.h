/************************************************************************
 * QLibOA                                                               *
 * Copyright (C) 2010 arturo182 <arturo182@tlen.pl>                     *
 *                                                                      *
 * This library is free software: you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation; version 3 only.                        *
 *                                                                      *
 * This library is distributed in the hope that it will be useful,      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with this library. If not, see <http://www.gnu.org/licenses/>. *
 ************************************************************************/

#ifndef QLIBOAREQUEST_H
#define QLIBOAREQUEST_H

#include "QLibOAConsumer.h"
#include "QLibOAToken.h"
#include "QLibOASignature.h"
#include "QLibOACommon.h"

#include <QVariant>

namespace QLibOA
{
  /*! \brief The request class.
   *
   *  This class represents the OAuth request.
   *
   *  There are two ways to create a request:
   *
   *  1. Simply create it trough constructor or Request::fromRequest function:
   *  \code
   *  QVariantMap params;
   *  params.insert("consumer_key", "foo-bar");
   *
   *  Request *req = Request::fromRequest(QLibOA::GET, "http://example.com/access_token", params);
   *  \endcode
   *  2. Create Reply with Consumer and Token information:
   *  \code
   *  QLibOA::Consumer con("foo-bar", "bar-foo");
   *  QLibOA::Token tok("bar-foo", "foo-bar");
   *
   *  QVariantMap params;
   *  params.insert("consumer_key", "foo-bar");
   *
   *  Request *req = Request::fromConsumerAndToken(&con, &tok, QLibOA::POST, "http://example.com/access_token", params);
   *  \endcode
   *  The difference is not only that when you execute fromConsumerAndToken, the consumer and token info is added
   *  to the request, but also default parameters like nonce and timestamp are added.
   *
   *  After you create a request, you may want to sign it, signing is done like this:
   *  \code
   *  QLibOA::Consumer con("foo-bar", "bar-foo");
   *  QLibOA::Token tok("bar-foo", "foo-bar");
   *
   *  Request *req = Request::fromConsumerAndToken(&con, &tok, QLibOA::POST, "http://example.com/access_token");
   *
   *  req->sign(QLibOA::HMAC_SHA1, &con, &tok);
   *  \endcode
   *
   *  After creating and signing a request, there are multiple ways to get a representation of it:<br>
   *  You can get it as a URL for GET requests using Request::toUrl.<br>
   *  If you want to use header-based authorization, you can use Request::toHeader to get
   *  "Authorization" header value and Request::getNormalizedUrl to get the URL.<br>
   *  There are also two functionsto get only the parameters, the Request::toGetdata function
   *  returns only the non-oauth parameters and Request::toPostdata returns all parameters.
   *
   *  All these functions return values that are encoded and ready to send.
   */
  class Request
  {
    public:
      Request(QLibOA::HttpMethod method = QLibOA::GET, const QString &url = QString(), QVariantMap params = QVariantMap());

      void setParam(const QString &key, const QString &value, bool duplicates = true);

      /*! \brief
       *  \return
       */
      QVariant param(const QString &key) { return m_params.value(key); }

      /*! \brief Returns parameter keys
       *  \return A list of sorted parameter keys
       */
      QVariantList paramAll(const QString &key);

      /*! \brief Removes all parameters with \a key key
       */
      void unsetParam(const QString &key) { m_params.remove(key); }

      /*! \brief Returns all parameters
       *  \return A map of request's parameters
       */
      QVariantMap params() { return m_params; }

      QString signableParams();

      QString baseString();
      QString normalizedHTTPMethod();
      QString normalizedUrl();

      static QString genTimestamp();
      static QString genNonce();

      QString toUrl();
      QString toGetdata();
      QString toPostdata();
      QString toHeader(const QString &realm = QString());

      void sign(QLibOA::SignatureMethod method = QLibOA::HMAC_SHA1, Consumer *consumer = NULL, Token *token = NULL);

      static Request *fromRequest(QLibOA::HttpMethod method = QLibOA::GET, const QString &url = QString(), const QVariantMap &params = QVariantMap());
      static Request *fromConsumerAndToken(Consumer *consumer, Token *token = NULL, QLibOA::HttpMethod method = QLibOA::GET, const QString &url = QString(), QVariantMap params = QVariantMap());

      void debug();

    private:
      QVariantMap m_params; /*!< Request's parameters */
      QLibOA::HttpMethod m_method; /*!< Request HTTP method */
      QString m_url;  /*!< Request URL */
  };
}

#endif // QLIBOAREQUEST_H
