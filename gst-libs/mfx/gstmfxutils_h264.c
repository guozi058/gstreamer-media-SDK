/*
 *  Copyright (C) 2011-2014 Intel Corporation
 *    Author: Gwenole Beauchesne <gwenole.beauchesne@intel.com>
 *  Copyright (C) 2016 Intel Corporation
 *    Author: Ishmael Visayana Sameen <ishmael.visayana.sameen@intel.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1
 *  of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301 USA
 */

#include "sysdeps.h"
#include "gstmfxutils_h264.h"

struct map
{
  guint value;
  const gchar *name;
};

/* Profile string map */
static const struct map gst_mfx_h264_profile_map[] = {
  {MFX_PROFILE_AVC_CONSTRAINED_BASELINE, "constrained-baseline"},
  {MFX_PROFILE_AVC_BASELINE, "baseline"},
  {MFX_PROFILE_AVC_MAIN, "main"},
  {MFX_PROFILE_AVC_EXTENDED, "extended"},
  {MFX_PROFILE_AVC_HIGH, "high"},
  {MFX_PROFILE_AVC_HIGH_422, "high-4:2:2"},
  {0, NULL}
};

/* Lookup value in map */
static const struct map *
map_lookup_value (const struct map *m, guint value)
{
  g_return_val_if_fail (m != NULL, NULL);

  for (; m->name != NULL; m++) {
    if (m->value == value)
      return m;
  }
  return NULL;
}

/* Lookup name in map */
static const struct map *
map_lookup_name (const struct map *m, const gchar * name)
{
  g_return_val_if_fail (m != NULL, NULL);

  if (!name)
    return NULL;

  for (; m->name != NULL; m++) {
    if (strcmp (m->name, name) == 0)
      return m;
  }
  return NULL;
}

/** Returns a relative score for the supplied MFX profile */
guint
gst_mfx_utils_h264_get_profile_score (mfxU16 profile)
{
  const struct map *const m =
      map_lookup_value (gst_mfx_h264_profile_map, profile);

  return m ? 1 + (m - gst_mfx_h264_profile_map) : 0;
}

/** Returns MFX profile from a string representation */
mfxU16
gst_mfx_utils_h264_get_profile_from_string (const gchar * str)
{
  const struct map *const m = map_lookup_name (gst_mfx_h264_profile_map, str);

  return m ? m->value : MFX_PROFILE_UNKNOWN;
}

/** Returns a string representation for the supplied H.264 profile */
const gchar *
gst_mfx_utils_h264_get_profile_string (mfxU16 profile)
{
  const struct map *const m =
      map_lookup_value (gst_mfx_h264_profile_map, profile);

  return m ? m->name : NULL;
}
