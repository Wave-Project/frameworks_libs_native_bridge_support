// Copyright 2019 (C) The Chromium Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

.text
.globl __native_bridge_config_static_tls
.type __native_bridge_config_static_tls, #function
__native_bridge_config_static_tls:
  ldr r3, =0
  bx r3

.text
.globl __native_bridge_get_host_pthread
.type __native_bridge_get_host_pthread, #function
__native_bridge_get_host_pthread:
  ldr r3, =0
  bx r3
