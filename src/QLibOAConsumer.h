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

#ifndef QLIBOACONSUMER_H
#define QLIBOACONSUMER_H

#include <QtCore/QDebug>

namespace QLibOA
{
  /*! \brief The consumer class
   *
   *  This class stores consumer_key and consumer_secret for easy access.
   */
  class Consumer
  {
    public:
      Consumer(const QString &key, const QString &secret, const QString &callback = QString());

      /*! \brief Sets new consumer_key value
       *  \param key Consumer_key to set
       */
      void setKey(const QString &key) { m_key = key; }

      /*! \brief Returns consumer_key
       *  \return Consumer_key
       */
      QString key() { return m_key; }

      /*! \brief Sets new consumer_secret value
       *  \param secret Consumer_secret
       */
      void setSecret(const QString &secret) { m_secret = secret; }

      /*! \brief Returns consumer_secret
       *  \return Consumer_secret
       */
      QString secret() { return m_secret; }

      /*! \brief Sets new callback value
       *  \param callback Callback
       */
      void setCallback(const QString &callback) { m_callback = callback; }

      /*! \brief Returns callback
       *  \return Callback
       */
      QString callback() { return m_callback; }

      /*! \brief Prints values of this class to qDebug
       */
      void debug() { qDebug() << "QLibOA::Consumer[\n  key =" << m_key << "\n  secret =" << m_secret << "\n  callback =" << m_callback << "\n]"; }

    private:
      QString m_key; /*!< consumer_key */
      QString m_secret; /*!< consumer_secret */
      QString m_callback; /*!< callback */
  };
}

#endif // QLIBOACONSUMER_H
