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

#ifndef QLIBOASIGNATURE_H
#define QLIBOASIGNATURE_H

#include "QLibOAConsumer.h"
#include "QLibOAToken.h"

namespace QLibOA
{
  class Request;

  /*! \brief Abstract signature class
   *
   *  This class doesn't really do anything but is a base for other signature classes
   *  \sa SignatureHMAC, SignaturePlainText
   */
  class Signature
  {
    public:
      /*! \brief The constructor
       */
      Signature() { }

      /*! \brief Returns the name of signing algorithm
       */
      virtual QString name() const = 0;

      /*! \brief Generates signature based on \a request, \a consumer and \a token
       *  \return The signature
       */
      virtual QString build(Request *request, Consumer *consumer, Token *token = 0) = 0;

      /*! \brief Function for validating signatures
       *  This function generates signature with supplied info and then checks if
       *  it's the same as user's signature.
       */
      bool check(Request *request, Consumer *consumer, Token *token, QString sig) { return (build(request, consumer, token) == sig); }
  };
}

#endif // QLIBOASIGNATURE_H
