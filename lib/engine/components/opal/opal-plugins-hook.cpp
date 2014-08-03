
/* Ekiga -- A VoIP and Video-Conferencing application
 * Copyright (C) 2000-2010 Damien Sandras <dsandras@seconix.com>
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
 *                         opal-plugins-hook.cpp  -  description
 *                         --------------------------------
 *   begin                : Sun Sept 26 2010
 *   copyright            : (C) 2010 by Julien Puydt
 *   description          : Code to connect the various ekiga plugins to opal
 *
 */

#include "opal-audio.h"
#include "opal-videoinput.h"
#include "opal-videooutput.h"

#include "opal-plugins-hook.h"

// we first declare the three plugin service descriptor classes

class PSoundChannel_EKIGA_PluginServiceDescriptor : public PDevicePluginServiceDescriptor
{
public:

  PSoundChannel_EKIGA_PluginServiceDescriptor (Ekiga::ServiceCore& core):
    audioinput_core(core.get<Ekiga::AudioInputCore> ("audioinput-core")),
    audiooutput_core(core.get<Ekiga::AudioOutputCore> ("audiooutput-core"))
  {}

  virtual PObject* CreateInstance (int) const
  {
    // FIXME: if that happens in a thread, that's bad...
    boost::shared_ptr<Ekiga::AudioInputCore> input = audioinput_core.lock ();
    boost::shared_ptr<Ekiga::AudioOutputCore> output = audiooutput_core.lock ();
    if (input && output)
      return new PSoundChannel_EKIGA (input, output);
    else
      return NULL;
  }

  virtual PStringArray GetDeviceNames(int) const
  { return PStringList ("EKIGA"); }

  virtual bool ValidateDeviceName (const PString & deviceName,
				   int) const
  { return deviceName.Find ("EKIGA") == 0; }

private:
  boost::weak_ptr<Ekiga::AudioInputCore> audioinput_core;
  boost::weak_ptr<Ekiga::AudioOutputCore> audiooutput_core;
};

class PVideoInputDevice_EKIGA_PluginServiceDescriptor : public PDevicePluginServiceDescriptor
{
public:

  PVideoInputDevice_EKIGA_PluginServiceDescriptor (Ekiga::ServiceCore& core):
    videoinput_core(core.get<Ekiga::VideoInputCore> ("videoinput-core"))
  {}

  virtual PObject* CreateInstance (int) const
  {
    // FIXME: if it happens in a thread, that's bad...
    boost::shared_ptr<Ekiga::VideoInputCore> output = videoinput_core.lock ();
    if (output)
      return new PVideoInputDevice_EKIGA (output);
    else
      return NULL;
  }


  virtual PStringArray GetDeviceNames (int) const
  { return PStringList ("EKIGA"); }

  virtual bool ValidateDeviceName (const PString & deviceName,
				   int) const
  { return deviceName.Find ("EKIGA") == 0; }

private:

  boost::weak_ptr<Ekiga::VideoInputCore> videoinput_core;
};

class PVideoOutputDevice_EKIGA_PluginServiceDescriptor : public PDevicePluginServiceDescriptor
{
public:

  PVideoOutputDevice_EKIGA_PluginServiceDescriptor (Ekiga::ServiceCore& core):
    videooutput_core(core.get<Ekiga::VideoOutputCore> ("videooutput-core"))
  {}

  virtual PObject *CreateInstance (int) const
  {
    // FIXME: if it happens in a thread, that's bad...
    boost::shared_ptr<Ekiga::VideoOutputCore> output = videooutput_core.lock ();
    if (output)
      return new PVideoOutputDevice_EKIGA (output);
    else
      return NULL;
  }

  virtual PStringArray GetDeviceNames (int) const
  { return PStringList("EKIGA"); }

  virtual bool ValidateDeviceName (const PString & deviceName,
				   int) const
  { return deviceName.Find ("EKIGA") == 0; }

private:

  boost::weak_ptr<Ekiga::VideoOutputCore> videooutput_core;
};

// now, let's rock :

static boost::shared_ptr<PSoundChannel_EKIGA_PluginServiceDescriptor> audio;
static boost::shared_ptr<PVideoInputDevice_EKIGA_PluginServiceDescriptor> videoinput;
static boost::shared_ptr<PVideoOutputDevice_EKIGA_PluginServiceDescriptor> videooutput;

void
hook_ekiga_plugins_to_opal (Ekiga::ServiceCore& core)
{
  /*
  audio = boost::shared_ptr<PSoundChannel_EKIGA_PluginServiceDescriptor> (new PSoundChannel_EKIGA_PluginServiceDescriptor (core));
  videoinput = boost::shared_ptr<PVideoInputDevice_EKIGA_PluginServiceDescriptor> (new PVideoInputDevice_EKIGA_PluginServiceDescriptor (core));
  videooutput = boost::shared_ptr<PVideoOutputDevice_EKIGA_PluginServiceDescriptor> (new PVideoOutputDevice_EKIGA_PluginServiceDescriptor (core));

  PPluginManager::GetPluginManager().RegisterService ("EKIGA", "PSoundChannel",
						      audio.get ());
  PPluginManager::GetPluginManager().RegisterService ("EKIGA", "PVideoInputDevice",
						      videoinput.get ());
  PPluginManager::GetPluginManager().RegisterService ("EKIGA", "PVideoOutputDevice",
						      videooutput.get ());
  */
}
