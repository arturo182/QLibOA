#include "QLibOAUtil.h"
#include "QLibOARequest.h"
#include "QLibOASignatureHMAC.h"
#include "QLibOASignaturePlainText.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QTextStream>
#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QRegExp>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QLibOA::ParamMap params;
    QList<QString> params2;
    QLibOA::Request *req;
    QLibOA::SignatureHMAC hmac;
    QLibOA::SignaturePlainText plain;
    QLibOA::Consumer consumer("key", "kd94hf93k423kf44");
    QLibOA::Token token("token", "pfkkdhi9sl3r4s00");

    //testing AuthConsumer class
    Q_ASSERT("key" == consumer.getKey());
    Q_ASSERT("kd94hf93k423kf44" == consumer.getSecret());

    //testing AuthToken class
    Q_ASSERT("token" == token.getKey());
    Q_ASSERT("pfkkdhi9sl3r4s00" == token.getSecret());

    //testing getParam function
    params.insert("foo", "bar");
    req = new QLibOA::Request(QLibOA::GET, NULL, params);
    Q_ASSERT("bar" == req->getParam("foo"));
    params.clear();

    //testing getParamAll function
    params.insert("foo", "bar");
    params.insert("foo", "test");
    params2.append("bar");
    params2.append("test");
    req = new QLibOA::Request(QLibOA::GET, NULL, params);
    Q_ASSERT(params2 == req->getParamAll("foo"));
    params.clear();
    params2.clear();

    //testing getParams function
    params.insert("foo", "bar");
    params.insert("test", "baz");
    req = new QLibOA::Request(QLibOA::GET, NULL, params);
    Q_ASSERT(params == req->getParams());
    params.clear();

    //testing setParam function
    req = new QLibOA::Request();
    Q_ASSERT(QString::null == req->getParam("foo"));

    req->setParam("foo", "bar");
    Q_ASSERT("bar" == req->getParam("foo"));

    params2.append("bar");
    params2.append("test");
    req->setParam("foo", "test");
    Q_ASSERT(params2 == req->getParamAll("foo"));
    params2.clear();

    params2.append("test");
    req->setParam("foo", "test", false);
    Q_ASSERT(params2 == req->getParamAll("foo"));
    params2.clear();

    //testing unsetParam function
    req = new QLibOA::Request();
    Q_ASSERT(QString::null == req->getParam("foo"));

    req->setParam("foo", "bar");
    Q_ASSERT("bar" == req->getParam("foo"));

    req->unsetParam("foo");
    Q_ASSERT(QString::null == req->getParam("foo"));

    //testing fromConsumerAndToken function
    req = QLibOA::Request::fromConsumerAndToken(&consumer, &token, QLibOA::POST, "http://example.com");
    Q_ASSERT("POST" == req->getNormalizedHTTPMethod());
    Q_ASSERT("http://example.com" == req->getNormalizedUrl());
    Q_ASSERT("1.0" == req->getParam("oauth_version"));
    Q_ASSERT(consumer.getKey() == req->getParam("oauth_consumer_key"));
    Q_ASSERT(token.getKey() == req->getParam("oauth_token"));
    Q_ASSERT(QString::number(QDateTime::currentDateTime().toTime_t()) == req->getParam("oauth_timestamp"));
    Q_ASSERT(true == QRegExp("[0-9a-f]{32}").exactMatch(req->getParam("oauth_nonce")));

    params.insert("oauth_nonce", "foo");
    req = QLibOA::Request::fromConsumerAndToken(&consumer, &token, QLibOA::POST, "http://example.com", params);
    Q_ASSERT("foo" == req->getParam("oauth_nonce"));
    params.clear();

    params.insert("oauth_nonce", "foo");
    req = QLibOA::Request::fromConsumerAndToken(&consumer, NULL, QLibOA::POST, "http://example.com", params);
    Q_ASSERT(QString::null == req->getParam("oauth_token"));
    params.clear();

    req = QLibOA::Request::fromConsumerAndToken(&consumer, NULL, QLibOA::POST, "http://example.com/?foo=bar");
    Q_ASSERT("bar" == req->getParam("foo"));

    //testing getSignableParams function
    params.insert("foo", "");
    req = new QLibOA::Request(QLibOA::GET, NULL, params);
    Q_ASSERT("foo=" == req->getSignableParams());
    params.clear();

    params.insert("foo", "bar");
    req = new QLibOA::Request(QLibOA::GET, NULL, params);
    Q_ASSERT("foo=bar" == req->getSignableParams());
    params.clear();

    params.insert("foo", "bar");
    params.insert("test", "foo");
    req = new QLibOA::Request(QLibOA::GET, NULL, params);
    Q_ASSERT("foo=bar&test=foo" == req->getSignableParams());
    params.clear();

    params.insert("a", "x!y");
    params.insert("b", "x+y");
    req = new QLibOA::Request(QLibOA::GET, NULL, params);
    Q_ASSERT("a=x%21y&b=x%2By" == req->getSignableParams());
    params.clear();

    params.insert("x", "1");
    params.insert("b", "x+y");
    params.insert("a", "foo bar");
    params.insert("z", "42");
    req = new QLibOA::Request(QLibOA::GET, NULL, params);
    Q_ASSERT("a=foo%20bar&b=x%2By&x=1&z=42" == req->getSignableParams());
    params.clear();

    //testing getNormalizedUrl
    req = new QLibOA::Request(QLibOA::POST, "http://example.com");
    Q_ASSERT("http://example.com" == req->getNormalizedUrl());

    req = new QLibOA::Request(QLibOA::POST, "https://example.com");
    Q_ASSERT("https://example.com" == req->getNormalizedUrl());

    req = new QLibOA::Request(QLibOA::POST, "http://example.com:8080");
    Q_ASSERT("http://example.com:8080" == req->getNormalizedUrl());

    //testing toPostdata function
    req = new QLibOA::Request(QLibOA::POST, "http://example.com");
    Q_ASSERT(QByteArray() == req->toPostdata());

    params.insert("foo", "bar");
    req = new QLibOA::Request(QLibOA::POST, "http://example.com", params);
    Q_ASSERT("foo=bar" == req->toPostdata());
    params.clear();

    req = new QLibOA::Request(QLibOA::POST, "http://example.com/?foo=bar");
    Q_ASSERT("foo=bar" == req->toPostdata());

    //testing toUrl function
    req = new QLibOA::Request(QLibOA::POST, "http://example.com");
    Q_ASSERT("http://example.com" == req->toUrl());


    params.insert("foo", "bar");
    req = new QLibOA::Request(QLibOA::POST, "http://example.com", params);
    Q_ASSERT("http://example.com?foo=bar" == req->toUrl());
    params.clear();

    req = new QLibOA::Request(QLibOA::POST, "http://example.com/?foo=bar");
    Q_ASSERT("http://example.com?foo=bar" == req->toUrl());

    //testing toHeader function
    req = new QLibOA::Request(QLibOA::POST, "http://example.com");
    Q_ASSERT("OAuth" == req->toHeader());
    Q_ASSERT("OAuth realm=\"foo\"" == req->toHeader("foo"));

    params.insert("oauth_test", "foo");
    req = new QLibOA::Request(QLibOA::POST, "http://example.com", params);
    Q_ASSERT("OAuth oauth_test=\"foo\"" == req->toHeader());
    Q_ASSERT("OAuth realm=\"foo\", oauth_test=\"foo\"" == req->toHeader("foo"));
    params.clear();

    params.insert("OAuth realm", "");
    params.insert("oauth_test", "foo");
    params.insert("oauth_baz", "bla,rgh");
    req = new QLibOA::Request(QLibOA::POST, "http://example.com", params);
    Q_ASSERT("OAuth oauth_baz=\"bla%2Crgh\", oauth_test=\"foo\"" == req->toHeader());
    Q_ASSERT("OAuth realm=\"foo\", oauth_baz=\"bla%2Crgh\", oauth_test=\"foo\"" == req->toHeader("foo"));
    params.clear();

    params.insert("oauth_test", "foo");
    params.insert("oauth_test", "bar");
    req = new QLibOA::Request(QLibOA::POST, "http://example.com", params);
    Q_ASSERT(QByteArray() == req->toHeader());
    params.clear();

    //testing getBaseString function
    params.insert("foo", "bar");
    req = new QLibOA::Request(QLibOA::POST, "http://example.com", params);
    Q_ASSERT("POST&http%3A%2F%2Fexample.com&foo%3Dbar" == req->getBaseString());
    params.clear();

    params.insert("oauth_version", "1.0");
    params.insert("oauth_consumer_key", "dpf43f3p2l4k3l03");
    params.insert("oauth_timestamp", "1191242090");
    params.insert("oauth_nonce", "hsu94j3884jdopsl");
    params.insert("oauth_signature_method", "PLAINTEXT");
    params.insert("oauth_signature", "ignored");
    req = new QLibOA::Request(QLibOA::POST, "https://photos.example.net/request_token", params);
    Q_ASSERT("POST&https%3A%2F%2Fphotos.example.net%2Frequest_token&oauth_consumer_key%3Ddpf43f3p2l4k3l03%26oauth_nonce%3Dhsu94j3884jdopsl%26oauth_signature_method%3DPLAINTEXT%26oauth_timestamp%3D1191242090%26oauth_version%3D1.0" == req->getBaseString());
    params.clear();

    params.insert("oauth_version", "1.0");
    params.insert("oauth_consumer_key", "dpf43f3p2l4k3l03");
    params.insert("oauth_timestamp", "1191242096");
    params.insert("oauth_nonce", "kllo9940pd9333jh");
    params.insert("oauth_signature_method", "HMAC-SHA1");
    params.insert("oauth_signature", "ignored");
    params.insert("file", "vacation.jpg");
    params.insert("size", "original");
    params.insert("oauth_token", "nnch734d00sl2jdk");
    req = new QLibOA::Request(QLibOA::GET, "http://photos.example.net/photos?", params);
    Q_ASSERT("GET&http%3A%2F%2Fphotos.example.net%2Fphotos&file%3Dvacation.jpg%26oauth_consumer_key%3Ddpf43f3p2l4k3l03%26oauth_nonce%3Dkllo9940pd9333jh%26oauth_signature_method%3DHMAC-SHA1%26oauth_timestamp%3D1191242096%26oauth_token%3Dnnch734d00sl2jdk%26oauth_version%3D1.0%26size%3Doriginal" == req->getBaseString());
    params.clear();

    //testing build (signatures) function
    req = QLibOA::Request::fromRequest(QLibOA::GET, "http://photos.example.net/photos?file=vacation.jpg&size=original&oauth_version=1.0&oauth_consumer_key=dpf43f3p2l4k3l03&oauth_token=nnch734d00sl2jdk&oauth_timestamp=1191242096&oauth_nonce=kllo9940pd9333jh&oauth_signature=ignored&oauth_signature_method=HMAC-SHA1");
    Q_ASSERT("tR3+Ty81lMeYAr/Fid0kMTYa/WM=" == hmac.build(req, &consumer, &token));
    Q_ASSERT("kd94hf93k423kf44&pfkkdhi9sl3r4s00" == plain.build(req, &consumer, &token));

    req->sign(QLibOA::HMAC_SHA1, &consumer, &token);
    Q_ASSERT("HMAC-SHA1" == req->getParam("oauth_signature_method"));
    Q_ASSERT("tR3+Ty81lMeYAr/Fid0kMTYa/WM=" == req->getParam("oauth_signature"));
    Q_ASSERT("file=vacation.jpg&oauth_consumer_key=dpf43f3p2l4k3l03&oauth_nonce=kllo9940pd9333jh&oauth_signature=tR3%2BTy81lMeYAr%2FFid0kMTYa%2FWM%3D&oauth_signature_method=HMAC-SHA1&oauth_timestamp=1191242096&oauth_token=nnch734d00sl2jdk&oauth_version=1.0&size=original" == req->toPostdata());

    req->sign(QLibOA::PLAINTEXT, &consumer, &token);
    Q_ASSERT("PLAINTEXT" == req->getParam("oauth_signature_method"));
    Q_ASSERT("kd94hf93k423kf44&pfkkdhi9sl3r4s00" == req->getParam("oauth_signature"));
    Q_ASSERT("file=vacation.jpg&oauth_consumer_key=dpf43f3p2l4k3l03&oauth_nonce=kllo9940pd9333jh&oauth_signature=kd94hf93k423kf44%26pfkkdhi9sl3r4s00&oauth_signature_method=PLAINTEXT&oauth_timestamp=1191242096&oauth_token=nnch734d00sl2jdk&oauth_version=1.0&size=original" == req->toPostdata());

    return a.exec();
}
