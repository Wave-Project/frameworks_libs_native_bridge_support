// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "native_bridge_support/vdso/vdso.h"

int main() {
  // Let the runtime know that app_process has successfully started
  native_bridge_post_init();
}
