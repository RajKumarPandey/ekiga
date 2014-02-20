
/*
 * Ekiga -- A VoIP and Video-Conferencing application
 * Copyright (C) 2000-2009 Damien Sandras <dsandras@seconix.com>

 * This program is free software; you can  redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version. This program is distributed in the hope
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Ekiga is licensed under the GPL license and as a special exception, you
 * have permission to link or otherwise combine this program with the
 * programs OPAL, OpenH323 and PWLIB, and distribute the combination, without
 * applying the requirements of the GNU GPL to the OPAL, OpenH323 and PWLIB
 * programs, as long as you do follow the requirements of the GNU GPL for all
 * the rest of the software thus combined.
 */


/*
 *                         chat-core.cpp  -  description
 *                         ------------------------------------------
 *   begin                : written in 2007 by Julien Puydt
 *   copyright            : (c) 2007 by Julien Puydt
 *   description          : implementation of the main chat managing object
 *
 */

#include "chat-core.h"

Ekiga::ChatCore::~ChatCore ()
{
}

void
Ekiga::ChatCore::add_dialect (DialectPtr dialect)
{
  add_object (dialect);
  dialect->updated.connect (boost::ref (updated));
  dialect->questions.connect (boost::ref (questions));
  dialect_added (dialect);
}

void
Ekiga::ChatCore::visit_dialects (boost::function1<bool, DialectPtr > visitor) const
{
  bool go_on = true;

  for (const_iterator iter = begin ();
       iter != end () && go_on;
       iter++)
    go_on = visitor (*iter);
}

int
Ekiga::ChatCore::get_unread_messages_count () const
{
  int result = 0;

  for (const_iterator iter = begin ();
       iter != end ();
       ++iter) {

    result += (*iter)->get_unread_messages_count ();
  }

  return result;
}

bool
Ekiga::ChatCore::populate_menu (MenuBuilder &builder)
{
  bool result = false;

  for (iterator iter = begin ();
       iter != end ();
       ++iter)
    result = (*iter)->populate_menu (builder) || result;

  return result;
}
