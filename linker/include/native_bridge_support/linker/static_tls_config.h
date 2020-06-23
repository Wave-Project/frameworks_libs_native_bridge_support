// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef NATIVE_BRIDGE_SUPPORT_LINKER_STATIC_TLS_CONFIG_H_
#define NATIVE_BRIDGE_SUPPORT_LINKER_STATIC_TLS_CONFIG_H_

#include <stdlib.h>

struct NativeBridgeStaticTlsConfig {
  // The size will be a multiple of the static TLS memory's alignment, which is
  // at most one page.
  size_t size;

  // The offset from the start of static TLS to the thread pointer.
  size_t tpoff;

  // Image to initialize the static TLS with. This image covers the entire area.
  const void* init_img;

  // The guest's value for TLS_SLOT_THREAD_ID.
  int tls_slot_thread_id;

  // The guest's value for TLS_SLOT_BIONIC_TLS.
  int tls_slot_bionic_tls;
};

#endif  // NATIVE_BRIDGE_SUPPORT_LINKER_STATIC_TLS_CONFIG_H_
