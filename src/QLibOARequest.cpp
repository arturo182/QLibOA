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

#include "QLibOARequest.h"
#include "QLibOAUtil.h"
#include "QLibOASignatureHMAC.h"
#include "QLibOASignaturePlainText.h"

#include <QtCore/QUrl>
#include <QtCore/QDateTime>
#include <QtCore/QCryptographicHash>

using namespace QLibOA;

/*! \brief The constructor
 *
 *  Creates a request with no default parameters.
 *  \param method HTTP method of the request
 *  \param url URL of the request
 *  \param params Parameters of the request
 */
Request::Request(QLibOA::HttpMethod method, QString url, QLibOA::ParamMap params)
{
  if(!url.isNull()) {
    params = Util::mergeParams(params, Util::urlToParams(url));
  }

  m_method = method;
  m_url = url;
  m_params = params;
}

/*! \brief Set parameter's value
 *  \param key Name of the parameter
 *  \param value Value of the parameter
 *  \param duplicates Should duplicates be allowed
 */
void Request::setParam(QString key, QString value, bool duplicates)
{
  if(!duplicates) {
    m_params.remove(key);
  }

  m_params.insert(key, value);
}

/*! \brief A static method to create a request.
 *  \param method HTTP method of the request
 *  \param url URL of the request
 *  \param params Parameters of the request
 *  \return A new Request object with supplied arguments.
 *  \sa Request::Request
 */
Request *Request::fromRequest(QLibOA::HttpMethod method, QString url, QLibOA::ParamMap params)
{
  return new Request(method, url, params);
}

/*! \brief A static method to create a request with consumer and token info.
 *
 *  This method differs from fromRequest, because it inserts default oauth parameters (nonce, timestamp, consumer_key, version and, if supplied, token).
 *  \param consumer A pointer to Consumer object with the consumer info
 *  \param token A pointer to Token object with token info
 *  \param method HTTP method of the request
 *  \param url URL of the request
 *  \param params Parameters of the request
 *  \return A new Request object filled with default oauth parameters and consumer and token information
 *  \sa Request::Request, Request::fromRequest
 */
Request *Request::fromConsumerAndToken(Consumer *consumer, Token *token, QLibOA::HttpMethod method, QString url, QLibOA::ParamMap params)
{
  QLibOA::ParamMap defaults;

  defaults.insert("oauth_nonce", Request::genNonce());
  defaults.insert("oauth_timestamp", Request::genTimestamp());
  defaults.insert("oauth_consumer_key", consumer->getKey());
  defaults.insert("oauth_version", "1.0");

  if(token) {
    defaults.insert("oauth_token", token->getKey());
  }

  params = Util::mergeParams(defaults, params);
  return new Request(method, url, params);
}

/*! \brief Returns request parameters for creating base string
 *
 *  The string is formated like this: par1=var1&par2=var2
 *  \return A string of sorted and encoded paramters.
 */
QString Request::getSignableParams()
{
  QLibOA::ParamMap params = m_params;

  params.remove("oauth_signature");

  return Util::buildHTTPQuery(params);
}

/*! \brief Returns base string for creating the signature
 *  \return The request's <a href="http://oauth.net/core/1.0/#anchor14">base string</a>
 */
QString Request::getBaseString()
{
  QString method = getNormalizedHTTPMethod();
  QString url = getNormalizedUrl();
  QString params = getSignableParams();

  method = Util::encode(method);
  url = Util::encode(url);
  params = Util::encode(params);

  return method + "&" + url + "&" + params;
}

/*! \brief Returns request's HTTP method as string
 *  \return String representation of HTTP method
 */
QString Request::getNormalizedHTTPMethod()
{
  switch(m_method) {
    case QLibOA::GET:
      return "GET";
    break;

    case QLibOA::POST:
      return "POST";
    break;
  }

  return "";
}

/*! \brief Returns normalized request URL
 *  \return Request URL that's been stripped of query and trailing slash
 */
QString Request::getNormalizedUrl()
{
  QUrl url(m_url);

  if(url.scheme().isEmpty()) {
    url.setScheme("http");
  }

  return url.toString(QUrl::RemoveQuery | QUrl::StripTrailingSlash).toAscii();
}

/*! \brief Generates current timestamp
 *  \return Current time in unix timestamp format
 */
QString Request::genTimestamp()
{
  return QString::number(QDateTime::currentDateTime().toTime_t());
}

/*! \brief Generates nonce
 * \return A random number hashed with md5 algorithm
 */
QString Request::genNonce()
{
  qsrand(QDateTime::currentDateTime().toTime_t());
  return QCryptographicHash::hash(QByteArray::number(qrand()), QCryptographicHash::Md5).toHex();
}

/*! \brief Convert the request to URL
 *  \return Request's URL + non-oauth parameters
 */
QString Request::toUrl()
{
  QString out = getNormalizedUrl();
  QString getData = toGetdata();

  if(!getData.isEmpty()) {
    out.append("?" + getData);
  }

  return out;
}

/*! \brief Returns non-oauth parameters as a string
 *
 *  The string is formated like this: par1=var1&par2=var2
 *  \return A string of sorted and encoded non-oauth parameters
 */
QString Request::toGetdata()
{
  return Util::buildHTTPQuery(m_params, true);
}

/*! \brief Returns request's parameters as a string
 *
 *  The string is formated like this: par1=var1&par2=var2
 *  \return A string of sorted and encoded paramteres
 */
QString Request::toPostdata()
{
  return Util::buildHTTPQuery(m_params);
}

/*! \brief Returns "Authorization" header value for header-based authorization
 *
 *  To know more about header-based authorization, go <a href="http://oauth.net/core/1.0/#auth_header">here</a>.
 *  \return Header value
 */
QString Request::toHeader(QString realm)
{
	bool first = true;
	QString out;

	if(!realm.isNull()) {
		out = "OAuth realm=\"" + Util::encode(realm) + "\"";
		first = false;
	} else {
		out = "OAuth";
	}

  QLibOA::ParamMap::iterator i = m_params.begin();
  while(i != m_params.end()) {
    if(i.key().mid(0, 5) != "oauth") {
      i++;
      continue;
    }

    if(m_params.values(i.key()).size() > 1) {
      return 0;
    }

    out.append((first)?" ":", ");
    out.append(Util::encode(i.key()) + "=\"" + Util::encode(i.value()) + "\"");

    first = false;

    i++;
  }

  return out;
}

/*! \brief Signs the request
 *
 *  The signature is automatically added to the parameters
 *  \param method Signature generation method
 *  \param consumer A pointer to Consumer object with consumer info
 *  \param token A pointer to Token object with token info
 */
void Request::sign(QLibOA::SignatureMethod method, Consumer *consumer, Token *token)
{
  Signature *sig = 0;

  switch(method) {
    case QLibOA::HMAC_SHA1:
      sig = new SignatureHMAC();
    break;

    case QLibOA::PLAINTEXT:
      sig = new SignaturePlainText();
    break;
  }

  if(sig) {
    setParam("oauth_signature_method", sig->getName(), false);
    setParam("oauth_signature", sig->build(this, consumer, token), false);
  }
}

/*! \brief Prints (some) values of this class to qDebug
 */
void Request::debug()
{
  qDebug() << "QOARequest[\n  params =" << m_params << "\n  method =" << m_method << "\n  url =" << m_url  << "\n]";
}
