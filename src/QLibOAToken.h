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

#ifndef QLIBOATOKEN_H
#define QLIBOATOKEN_H

#include <QtCore/QDebug>

namespace QLibOA
{
  /*! \brief The token class
   *
   *  This class stores token_key and token_secret for easy access.
   */
  class Token
  {
    public:
      Token(const QString &key, const QString &secret);

      static Token *fromString(const QString &text);

      /*! \brief Sets new token_key value
       *  \param key Token_key to set
       */
      void setKey(const QString &key) { m_key = key; }

      /*! \brief Returns token_key
       *  \return Token_key
       */
      QString key() const { return m_key; }

      /*! \brief Sets new token_secret value
       *  \param secret Token_secret
       */
      void setSecret(const QString &secret) { m_secret = secret; }

      /*! \brief Returns token_secret
       *  \return Token_secret
       */
      QString secret() const { return m_secret; }

      /*! \brief Prints values of this class to qDebug
       */
      void debug() { qDebug() << "QLibOA::Token[\n  key=" << m_key << "\n  secret=" << m_secret << "\n]"; }

    private:
      QString m_key; /*!< token_key */
      QString m_secret; /*!< token_secret */
  };
}

#endif // QLIBOATOKEN_H
