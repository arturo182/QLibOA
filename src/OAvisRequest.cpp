/**
  * QOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#include "OAvisRequest.h"
#include "OAvisUtil.h"
#include "OAvisSignatureHMAC.h"
#include "OAvisSignaturePlainText.h"

#include <QtCore/QUrl>
#include <QtCore/QDateTime>
#include <QtCore/QCryptographicHash>

using namespace OAvis;

Request::Request(OAvis::HttpMethod method, QByteArray url, OAvis::ParamMap params)
{
  if(!url.isNull()) {
    params = Util::mergeParams(params, Util::urlToParams(url));
  }

  m_method = method;
  m_url = url;
  m_params = params;
}

void Request::setParam(QByteArray key, QByteArray value, bool duplicates)
{
  if(!duplicates) {
    m_params.remove(key);
  }

  m_params.insert(key, value);
}

Request *Request::fromRequest(OAvis::HttpMethod method, QByteArray url, OAvis::ParamMap params)
{
  return new Request(method, url, params);
}

Request *Request::fromConsumerAndToken(Consumer *consumer, Token *token, OAvis::HttpMethod method, QByteArray url, OAvis::ParamMap params)
{
  OAvis::ParamMap defaults;

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

QByteArray Request::getSignableParams()
{
  OAvis::ParamMap params = m_params;

  params.remove("oauth_signature");

  return Util::buildHTTPQuery(params);
}

QByteArray Request::getBaseString()
{
  QByteArray method = getNormalizedHTTPMethod();
  QByteArray url = getNormalizedUrl();
  QByteArray params = getSignableParams();

  method = Util::encode(method);
  url = Util::encode(url);
  params = Util::encode(params);

  return method + "&" + url + "&" + params;
}

QByteArray Request::getNormalizedHTTPMethod()
{
  switch(m_method) {
    case OAvis::GET:
      return "GET";
    break;

    case OAvis::POST:
      return "POST";
    break;
  }

  return "";
}

QByteArray Request::getNormalizedUrl()
{
  QUrl url(m_url);

  if(url.scheme().isEmpty()) {
    url.setScheme("http");
  }

  return url.toString(QUrl::RemoveQuery | QUrl::StripTrailingSlash).toAscii();
}

QByteArray Request::genTimestamp()
{
  return QByteArray::number(QDateTime::currentDateTime().toTime_t());
}

QByteArray Request::genNonce()
{
  qsrand(QDateTime::currentDateTime().toTime_t());
  return QCryptographicHash::hash(QByteArray::number(qrand()), QCryptographicHash::Md5).toHex();
}

QByteArray Request::toUrl()
{
  QByteArray postData = toPostdata();
  QByteArray out = getNormalizedUrl();

  if(!postData.isEmpty()) {
    out.append("?" + postData);
  }

  return out;
}

QByteArray Request::toPostdata()
{
  return Util::buildHTTPQuery(m_params);
}

QByteArray Request::toHeader(QByteArray realm)
{
	bool first = true;
	QByteArray out;

	if(!realm.isNull()) {
		out = "Authorization: OAuth realm=\"" + Util::encode(realm) + "\"";
		first = false;
	} else {
		out = "Authorization: OAuth";
	}

  OAvis::ParamMap::iterator i = m_params.begin();
  while(i != m_params.end()) {
    if(i.key().mid(0, 5) != "oauth") {
      i++;
      continue;
    }

    if(m_params.values(i.key()).size() > 1) {
      return 0;
    }

    out.append((first)?' ':',');
    out.append(Util::encode(i.key()) + "=\"" + Util::encode(i.value()) + "\"");

    first = false;

    i++;
  }

  return out;
}

void Request::sign(OAvis::SignatureMethod method, Consumer *consumer, Token *token)
{
  Signature *sig = 0;

  switch(method) {
    case OAvis::HMAC_SHA1:
      sig = new SignatureHMAC();
    break;

    case OAvis::PLAINTEXT:
      sig = new SignaturePlainText();
    break;
  }

  if(sig) {
    setParam("oauth_signature_method", sig->getName(), false);
    setParam("oauth_signature", sig->build(this, consumer, token), false);
  }
}

void Request::debug()
{
  qDebug() << "QOARequest[\n  params =" << m_params << "\n  method =" << m_method << "\n  url =" << m_url  << "\n]";
}
