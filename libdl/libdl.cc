// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <string.h>
#include <sys/types.h>

#include <android/dlext.h>

#include "native_bridge_support/vdso/vdso.h"

__attribute__((__weak__, visibility("default"))) extern "C" void*
__loader_dlopen(const char* filename, int flags, const void* caller_addr);

__attribute__((__weak__, visibility("default"))) extern "C" void* __loader_android_dlopen_ext(
    const char* filename,
    int flag,
    const android_dlextinfo* extinfo,
    const void* caller_addr);

extern "C" void* dlopen(const char* filename, int flag) {
  const void* caller_addr = __builtin_return_address(0);
  return __loader_dlopen(filename, flag, caller_addr);
}

extern "C" void* android_dlopen_ext(const char* filename,
                                    int flag,
                                    const android_dlextinfo* extinfo) {
  const void* caller_addr = __builtin_return_address(0);
  return __loader_android_dlopen_ext(filename, flag, extinfo, caller_addr);
}
