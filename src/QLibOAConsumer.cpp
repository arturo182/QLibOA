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

#include "QLibOAConsumer.h"

using namespace QLibOA;

/*! \brief The constructor
 *
 * \param key Consumer_key value
 * \param secret Consumer_secret value
 * \param callback The callback
 */
Consumer::Consumer(QString key, QString secret, QString callback)
{
  m_key = key;
  m_secret = secret;
  m_callback = callback;
}
