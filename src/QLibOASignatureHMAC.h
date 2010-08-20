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

#ifndef QLIBOASIGNATUREHMAC_H
#define QLIBOASIGNATUREHMAC_H

#include "QLibOASignature.h"

namespace QLibOA
{
  /*! \brief A class for signing requests with the HMAC-SHA1 algorithm
   */
  class SignatureHMAC: public Signature
  {
    public:
      SignatureHMAC() { }

      QString getName() { return "HMAC-SHA1"; }
      QString hmacSha1(QByteArray data, QByteArray key);
      QString build(Request *request, Consumer *consumer, Token *token = NULL);
  };
}

#endif // QOASIGNATUREHMAC_H
