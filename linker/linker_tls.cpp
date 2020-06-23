// Copyright (c) 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "private/linker_native_bridge.h"

// Avoid allocating a bionic_tls in the guest's static TLS, because the guest
// uses the host's object.
extern "C" void __linker_reserve_bionic_tls_in_static_tls() {}
