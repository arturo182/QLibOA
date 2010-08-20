/**
  * QLibOA
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  */

#include "QLibOARequest.h"
#include "QLibOAUtil.h"
#include "QLibOASignatureHMAC.h"
#include "QLibOASignaturePlainText.h"

#include <QtCore/QUrl>
#include <QtCore/QDateTime>
#include <QtCore/QCryptographicHash>

using namespace QLibOA;

Request::Request(QLibOA::HttpMethod method, QString url, QLibOA::ParamMap params)
{
  if(!url.isNull()) {
    params = Util::mergeParams(params, Util::urlToParams(url));
  }

  m_method = method;
  m_url = url;
  m_params = params;
}

void Request::setParam(QString key, QString value, bool duplicates)
{
  if(!duplicates) {
    m_params.remove(key);
  }

  m_params.insert(key, value);
}

Request *Request::fromRequest(QLibOA::HttpMethod method, QString url, QLibOA::ParamMap params)
{
  return new Request(method, url, params);
}

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

QString Request::getSignableParams()
{
  QLibOA::ParamMap params = m_params;

  params.remove("oauth_signature");

  return Util::buildHTTPQuery(params);
}

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

QString Request::getNormalizedUrl()
{
  QUrl url(m_url);

  if(url.scheme().isEmpty()) {
    url.setScheme("http");
  }

  return url.toString(QUrl::RemoveQuery | QUrl::StripTrailingSlash).toAscii();
}

QString Request::genTimestamp()
{
  return QString::number(QDateTime::currentDateTime().toTime_t());
}

QString Request::genNonce()
{
  qsrand(QDateTime::currentDateTime().toTime_t());
  return QCryptographicHash::hash(QByteArray::number(qrand()), QCryptographicHash::Md5).toHex();
}

QString Request::toUrl()
{
  QString out = getNormalizedUrl();
  QString getData = toGetdata();

  if(!getData.isEmpty()) {
    out.append("?" + getData);
  }

  return out;
}

QString Request::toGetdata()
{
  return Util::buildHTTPQuery(m_params, true);
}

QString Request::toPostdata()
{
  return Util::buildHTTPQuery(m_params);
}

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

void Request::debug()
{
  qDebug() << "QOARequest[\n  params =" << m_params << "\n  method =" << m_method << "\n  url =" << m_url  << "\n]";
}
