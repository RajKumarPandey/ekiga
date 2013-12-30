
/* Ekiga -- A VoIP and Video-Conferencing application
 * Copyright (C) 2000-2009 Damien Sandras <dsandras@seconix.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * Ekiga is licensed under the GPL license and as a special exception,
 * you have permission to link or otherwise combine this program with the
 * programs OPAL, OpenH323 and PWLIB, and distribute the combination,
 * without applying the requirements of the GNU GPL to the OPAL, OpenH323
 * and PWLIB programs, as long as you do follow the requirements of the
 * GNU GPL for all the rest of the software thus combined.
 */


/*
 *                         engine.cpp  -  description
 *                         ------------------------------------------
 *   begin                : written in 2007 by Damien Sandras
 *   copyright            : (c) 2007 by Damien Sandras
 *   description          : Vroom.
 *
 */

#include "config.h"

#include "engine.h"

#include "services.h"
#include "kickstart.h"

#include "notification-core.h"
#include "plugin-core.h"
#include "presence-core.h"
#include "account-core.h"
#include "contact-core.h"
#include "call-core.h"
#include "chat-core.h"
#include "friend-or-foe.h"
#include "videooutput-core.h"
#include "videoinput-core.h"
#include "audioinput-core.h"
#include "audiooutput-core.h"
#include "hal-core.h"
#include "history-main.h"
#include "local-roster-main.h"
#include "local-roster-bridge.h"
#include "gtk-core-main.h"
#include "gtk-frontend.h"
#include "gmconf-personal-details.h"

#ifndef WIN32
#include "videooutput-main-x.h"
#endif

#ifdef HAVE_DX
#include "videooutput-main-dx.h"
#endif

#include "videooutput-main-clutter-gst.h"

#include "videoinput-main-mlogo.h"
#include "audioinput-main-null.h"
#include "audiooutput-main-null.h"

#include "videoinput-main-ptlib.h"
#include "audioinput-main-ptlib.h"
#include "audiooutput-main-ptlib.h"

#ifdef HAVE_DBUS
#include "hal-main-dbus.h"
#endif

#include "opal-main.h"

#define DEBUG_STARTUP 0

#if DEBUG_STARTUP
#include <iostream>
#endif

void
engine_init (Ekiga::ServiceCorePtr service_core,
	     int argc,
             char *argv [])
{
  // FIRST we add a few things by hand
  // (for speed and because that's less code)

  Ekiga::ServicePtr notification_core(new Ekiga::NotificationCore);
  boost::shared_ptr<Ekiga::AccountCore> account_core (new Ekiga::AccountCore);
  boost::shared_ptr<Ekiga::ContactCore> contact_core (new Ekiga::ContactCore);
  boost::shared_ptr<Ekiga::CallCore> call_core (new Ekiga::CallCore);
  boost::shared_ptr<Ekiga::ChatCore> chat_core (new Ekiga::ChatCore);
  boost::shared_ptr<Ekiga::VideoOutputCore> videooutput_core (new Ekiga::VideoOutputCore);
  boost::shared_ptr<Ekiga::VideoInputCore> videoinput_core (new Ekiga::VideoInputCore (*service_core, videooutput_core));
  boost::shared_ptr<Ekiga::AudioOutputCore> audiooutput_core (new Ekiga::AudioOutputCore (*service_core));
  boost::shared_ptr<Ekiga::AudioInputCore> audioinput_core (new Ekiga::AudioInputCore(*service_core));
  boost::shared_ptr<Ekiga::HalCore> hal_core (new Ekiga::HalCore);
  boost::shared_ptr<Ekiga::FriendOrFoe> friend_or_foe (new Ekiga::FriendOrFoe);
  boost::shared_ptr<Gmconf::PersonalDetails> details(new Gmconf::PersonalDetails);
  boost::shared_ptr<Ekiga::PresenceCore> presence_core(new Ekiga::PresenceCore (details));

  service_core->add (notification_core);
  service_core->add (contact_core);
  service_core->add (chat_core);
  service_core->add (friend_or_foe);
  service_core->add (videoinput_core);
  service_core->add (videooutput_core);
  service_core->add (audioinput_core);
  service_core->add (audiooutput_core);
  service_core->add (hal_core);
  service_core->add (call_core);
  service_core->add (account_core);
  service_core->add (details);
  service_core->add (presence_core);

  if (!videoinput_mlogo_init (*service_core, &argc, &argv)) {
    return;
  }

  if (!videooutput_clutter_gst_init (*service_core, &argc, &argv)) {
    return;
  }

  // THEN we use the kickstart scheme

  Ekiga::KickStart kickstart;

  audioinput_null_init (kickstart);
  audiooutput_null_init (kickstart);

  videoinput_ptlib_init (kickstart);

  audioinput_ptlib_init (kickstart);
  audiooutput_ptlib_init (kickstart);

#ifdef HAVE_DBUS
  hal_dbus_init (kickstart);
#endif

  opal_init (kickstart);

  history_init (kickstart);

  local_roster_init (kickstart);

  local_roster_bridge_init (kickstart);

  plugin_init (kickstart);

  // FIXME: Some parts in the kickstart need the gui.  The gui needs
  //  some parts in the kickstart.  So we will kick a first time to
  //  get things not needing the gui up and running, then start the
  //  gui (which will hence find what it needs) and kick a second time
  //  to really make the engine go vroom. It would be nicer to either
  //  push the parts needed by the gui in the hand-crafted part of
  //  this initialization, or put the gui in the kickstart too.

  kickstart.kick (*service_core, &argc, &argv);

  // FIXME: can't we have a single function for the whole gui?
  gtk_core_init (*service_core, &argc, &argv);

  if (!gtk_frontend_init (*service_core, &argc, &argv)) {

    return;
  }

  kickstart.kick (*service_core, &argc, &argv);

  /* FIXME: everything that follows except the debug output shouldn't
     be there, as that means we're doing the work of initializing
     those in the correct order here instead of having the specific
     code in question to do it itself
   */

  videooutput_core->setup ();
  videoinput_core->setup ("any");
  audioinput_core->setup ();
  audiooutput_core->setup ();


  hal_core->videoinput_device_added.connect (boost::bind (&Ekiga::VideoInputCore::add_device, boost::ref (*videoinput_core), _1, _2, _3, _4));
  hal_core->videoinput_device_removed.connect (boost::bind (&Ekiga::VideoInputCore::remove_device, boost::ref (*videoinput_core), _1, _2, _3, _4));
  hal_core->audiooutput_device_added.connect (boost::bind (&Ekiga::AudioOutputCore::add_device, boost::ref (*audiooutput_core), _1, _2, _3));
  hal_core->audiooutput_device_removed.connect (boost::bind (&Ekiga::AudioOutputCore::remove_device, boost::ref (*audiooutput_core), _1, _2, _3));
  hal_core->audioinput_device_added.connect (boost::bind (&Ekiga::AudioInputCore::add_device, boost::ref (*audioinput_core), _1, _2, _3));
  hal_core->audioinput_device_removed.connect (boost::bind (&Ekiga::AudioInputCore::remove_device, boost::ref (*audioinput_core), _1, _2, _3));

#if DEBUG_STARTUP
  std::cout << "Here is what ekiga is made of for this run :" << std::endl;
  service_core->dump (std::cout);
#endif
}
