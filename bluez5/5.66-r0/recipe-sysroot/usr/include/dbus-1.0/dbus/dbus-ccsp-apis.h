/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/* dbus-ccsp-apis.h
 *
 * Copyright (C) 2003  Red Hat, Inc.
 *
 * Licensed under the Academic Free License version 2.1
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#if !defined (DBUS_INSIDE_DBUS_H) && !defined (DBUS_COMPILATION)
#error "Only <dbus/dbus.h> can be included directly, this file may disappear or change contents."
#endif

#ifndef DBUS_CCSP_APIS_H
#define DBUS_CCSP_APIS_H

#include <dbus/dbus.h>
#include <stdarg.h>

typedef struct DBusLoop DBusLoop;

DBUS_BEGIN_DECLS

/**
 * @addtogroup DBusCcspApis
 * @{
 */

/* From dbus-mainloop */
DBUS_EXPORT
DBusLoop*   dbus_loop_new            (void);

DBUS_EXPORT
DBusLoop*   dbus_loop_ref            (DBusLoop            *loop);

DBUS_EXPORT
void        dbus_loop_unref          (DBusLoop            *loop);

DBUS_EXPORT
dbus_bool_t dbus_loop_add_watch      (DBusLoop            *loop,
                                      DBusWatch           *watch);

DBUS_EXPORT
void        dbus_loop_remove_watch   (DBusLoop            *loop,
                                      DBusWatch           *watch);
DBUS_EXPORT
void        dbus_loop_toggle_watch   (DBusLoop            *loop,
                                      DBusWatch           *watch);
DBUS_EXPORT
dbus_bool_t dbus_loop_add_timeout    (DBusLoop            *loop,
                                      DBusTimeout         *timeout);

DBUS_EXPORT
void        dbus_loop_remove_timeout (DBusLoop            *loop,
                                      DBusTimeout         *timeout);

DBUS_EXPORT
dbus_bool_t dbus_loop_queue_dispatch (DBusLoop            *loop,
                                      DBusConnection      *connection);

DBUS_EXPORT
void        dbus_loop_run            (DBusLoop            *loop);

DBUS_EXPORT
void        dbus_loop_quit           (DBusLoop            *loop);

DBUS_EXPORT
dbus_bool_t dbus_loop_iterate        (DBusLoop            *loop,
                                      dbus_bool_t          block);

DBUS_EXPORT
dbus_bool_t dbus_loop_dispatch       (DBusLoop            *loop);

DBUS_EXPORT
void dbus_wait_for_memory(void);

DBUS_EXPORT
int dbus_get_oom_wait(void);

/* From dbus-connection */
DBUS_EXPORT
void dbus_connection_lock(DBusConnection *connection);

DBUS_EXPORT
void dbus_connection_unlock(DBusConnection *connection);

DBUS_EXPORT
dbus_bool_t dbus_loop_add_wake       (DBusLoop            *loop,
                                      int                 fd);

DBUS_EXPORT
void dbus_loop_remove_wake           (DBusLoop            *loop);

/** @} */

DBUS_END_DECLS

#endif /* DBUS_CCSP_APIS_H */

