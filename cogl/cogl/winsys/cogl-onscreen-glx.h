/*
 * Copyright (C) 2007,2008,2009,2010,2011,2013 Intel Corporation.
 * Copyright (C) 2020 Red Hat
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef COGL_ONSCREEN_GLX_H
#define COGL_ONSCREEN_GLX_H

#include <GL/glx.h>
#include <X11/Xlib.h>

#include "cogl-onscreen.h"

#define COGL_TYPE_ONSCREEN_GLX (cogl_onscreen_glx_get_type ())
G_DECLARE_FINAL_TYPE (CoglOnscreenGlx, cogl_onscreen_glx,
                      COGL, ONSCREEN_GLX,
                      CoglOnscreen)

COGL_EXPORT CoglOnscreenGlx *
cogl_onscreen_glx_new (CoglContext *context,
                       int          width,
                       int          height);

gboolean
_cogl_winsys_onscreen_glx_init (CoglOnscreen  *onscreen,
                                GError       **error);

void
_cogl_winsys_onscreen_glx_deinit (CoglOnscreen *onscreen);

void
_cogl_winsys_onscreen_glx_bind (CoglOnscreen *onscreen);

int
_cogl_winsys_onscreen_glx_get_buffer_age (CoglOnscreen *onscreen);

void
_cogl_winsys_onscreen_glx_swap_region (CoglOnscreen  *onscreen,
                                       const int     *user_rectangles,
                                       int            n_rectangles,
                                       CoglFrameInfo *info,
                                       gpointer       user_data);

void
_cogl_winsys_onscreen_glx_swap_buffers_with_damage (CoglOnscreen  *onscreen,
                                                    const int     *rectangles,
                                                    int            n_rectangles,
                                                    CoglFrameInfo *info,
                                                    gpointer       user_data);

uint32_t
_cogl_winsys_onscreen_glx_get_window_xid (CoglOnscreen *onscreen);

void
_cogl_winsys_onscreen_glx_set_visibility (CoglOnscreen *onscreen,
                                          gboolean      visibility);

void
_cogl_winsys_onscreen_glx_set_resizable (CoglOnscreen *onscreen,
                                         gboolean      resizable);

void
cogl_onscreen_glx_resize (CoglOnscreen    *onscreen,
                          XConfigureEvent *configure_event);

void
cogl_onscreen_glx_update_output (CoglOnscreen *onscreen);

void
cogl_onscreen_glx_notify_swap_buffers (CoglOnscreen          *onscreen,
                                       GLXBufferSwapComplete *swap_event);

gboolean
cogl_onscreen_glx_is_for_window (CoglOnscreen *onscreen,
                                 Window        window);

#endif /* COGL_ONSCREEN_GLX_H */