/*
  Copyright (C) 2013-2014 Yubico AB

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INTERNAL_H
#define INTERNAL_H

#include <u2f-host/u2f-host.h>
#include <hidapi.h>
#include <stdio.h>

#include "inc/u2f.h"
#include "inc/u2f_hid.h"

struct u2fdevice
{
  hid_device *devh;
  uint32_t cid;
  char *device_string;
  char *device_path;
  int is_alive;
};

struct u2fh_devs
{
  int num_devices;
  struct u2fdevice *devs;
};

extern int debug;

#define MAXDATASIZE 1024

#define MAXFIXEDLEN 1024

#define REGISTER_TYP "navigator.id.finishEnrollment"
#define AUTHENTICATE_TYP "navigator.id.getAssertion"

int prepare_browserdata (const char *challenge, const char *origin,
			 const char *typstr, char *out, size_t * outlen);
int prepare_origin (const char *origin, unsigned char *p);
u2fh_rc send_apdu (u2fh_devs * devs, int index, int cmd,
		   const unsigned char *d, size_t dlen, int p1,
		   unsigned char *out, size_t * outlen);
int get_fixed_json_data (const char *jsonstr, const char *key, char *p,
			 size_t * len);
int hash_data (const char *in, size_t len, unsigned char *out);

#endif
