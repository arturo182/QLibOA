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

#ifndef QLIBOAUTIL_H
#define QLIBOAUTIL_H

#include "QLibOAConsumer.h"
#include "QLibOAToken.h"
#include "QLibOARequest.h"

namespace QLibOA
{
  /*! \brief Utilities class
   *
   *  This class provides helper functions used in QLibOA
   */
  class Util
  {
    public:
      /*! \brief The constructor
       */
      Util() { }

      static QString encode(const QString &text);
      static QString decode(const QString &text);
      static QString genKey(Consumer *consumer = 0, Token *token = 0);
      static QVariantMap urlToParams(const QString &url);
      static QVariantMap mergeParams(const QVariantMap &first, const QVariantMap &second);
      static QString buildHTTPQuery(const QVariantMap &params, bool skipOAuth = false);
  };
}

#endif // QLIBOAUTIL_H
