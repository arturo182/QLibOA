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

#ifndef QLIBOA_H
#define QLIBOA_H

#include <QtCore/QDebug>
#include <QtCore/QMultiMap>

/*!
  \mainpage

  \section what What does this library do?
  QLibOA is a library for creating and signing OAuth request. It was written with Twitter's API authorization
  but can be used with any service that uses OAuth. To learn more about OAuth visit <a href="http://oauth.net/">OAuth.net</a>

  \section bug Bugs and support
  If you want to inform me about any bugs you run across while using QLibOA, go to <a href="http://github.com/arturo182/QLibOA/issues">github.com</a>
  or contact me via my website <a href="http://www.arturpacholec.pl/">arturpacholec.pl</a>

  \section help Help with coding
  If you want to add some functionality to QLibOA, don't hesitate, fork it on github and modify, after you finish, send me a pull request.

  \section usage Usage
  If you use QLibOA in your application, let me know, I would love to see what my library was helpful for.

  \section insp Inspiration
  I won't lie that I did everything myself, I got some inspiration:<br>
  <a href="http://github.com/ayoy/qoauth/">QOAuth</a> - another OAuth library for Qt, I created mine cause I didn't want to depend on QCA<br>
  <a href="http://oauth.googlecode.com/svn/code/php/">PHP OAuth</a> - I basically rewrote this library in Qt
*/

/*! \brief The library namespace
 */
namespace QLibOA
{
  /*! \brief Just a multimap of QStrings for request parameters.
   */
  typedef QMultiMap<QString, QString> ParamMap;

  /*! \brief A enum of HTTP methods for requests.
   */
  enum HttpMethod
  {
    GET = 0, /*!< GET method */
    POST = 1 /*!< POST method*/
  };

  /*! \brief A enum of signature methods.
   *
   *  For more information about signature methods, go <a href="http://oauth.net/core/1.0/#signing_process">here</a>.
   *  OAuth currently supports three signature methods, but QLibOA
   *  implements only two: HMAC-SHA1 and Plaintext.
   */
  enum SignatureMethod
  {
    HMAC_SHA1 = 0, /*!< Sign using HMAC-SHA1 algorithm */
    PLAINTEXT = 1 /*!< Sign using Plaintext */
  };

  /*! \brief An overloaded operator function to allow qDebug print HttpMethod properly.
  */
  inline QDebug operator<<(QDebug debug, const QLibOA::HttpMethod method)
  {
    debug.nospace() << "QLibOA::HttpMethod(";
    switch(method) {
      case QLibOA::GET:
        debug << "GET";
      break;

      case QLibOA::POST:
        debug << "POST";
      break;
    }

    debug << ")";

    return debug.space();
  }

  /*! \brief An overloaded operator function to allow qDebug print ParamMap properly.
  */
  inline QDebug operator<<(QDebug debug, const QLibOA::ParamMap params)
  {
    debug.nospace() << "QLibOA::ParamMap(\n";

    QLibOA::ParamMap::const_iterator i = params.begin();
    while(i != params.end()) {
      debug << "    " << i.key() << " = " << i.value();
      i++;

      if(i != params.end()) {
        debug << "\n";
      }
    }
    debug << "\n  )";

    return debug.space();
  }

}

#endif // QLIBOA_H
