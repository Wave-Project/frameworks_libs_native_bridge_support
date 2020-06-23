/*
 * Copyright (C) 2020 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "linker_translate_path.h"
#include "linker.h"

#include <android/api-level.h>

#include <string>

#if defined(__arm__)
#define SYSTEM_LIB(name) \
  { "/system/lib/" name, "/system/lib/arm/" name }
#elif defined(__aarch64__)
#define SYSTEM_LIB(name) \
  { "/system/lib64/" name, "/system/lib64/arm64/" name }
#else
#error "Unknown guest arch"
#endif

// Workaround for dlopen(/system/lib(64)/<soname>) when .so is in /apex. http://b/121248172
/**
 * Translate /system path to /apex path if needed
 * The workaround should work only when targetSdkVersion < Q.
 *
 * param out_name_to_apex pointing to /apex path
 * return true if translation is needed
 */
bool translateSystemPathToApexPath(const char* name, std::string* out_name_to_apex) {
  static constexpr const char* kPathTranslation[][2] = {
      SYSTEM_LIB("libEGL.so"),
      SYSTEM_LIB("libGLESv1_CM.so"),
      SYSTEM_LIB("libGLESv2.so"),
      SYSTEM_LIB("libGLESv3.so"),
      SYSTEM_LIB("libOpenMAXAL.so"),
      SYSTEM_LIB("libOpenSLES.so"),
      SYSTEM_LIB("libRS.so"),
      SYSTEM_LIB("libaaudio.so"),
      SYSTEM_LIB("libamidi.so"),
      SYSTEM_LIB("libandroid.so"),
      SYSTEM_LIB("libbinder_ndk.so"),
      SYSTEM_LIB("libc.so"),
      SYSTEM_LIB("libcamera2ndk.so"),
      SYSTEM_LIB("libdl.so"),
      SYSTEM_LIB("libjnigraphics.so"),
      SYSTEM_LIB("liblog.so"),
      SYSTEM_LIB("libm.so"),
      SYSTEM_LIB("libmediandk.so"),
      SYSTEM_LIB("libnativewindow.so"),
      SYSTEM_LIB("libstdc++.so"),
      SYSTEM_LIB("libsync.so"),
      SYSTEM_LIB("libvulkan.so"),
      SYSTEM_LIB("libwebviewchromium_plat_support.so"),
      SYSTEM_LIB("libz.so")};

  static constexpr const char* kPathTranslationQ[][2] = {
      SYSTEM_LIB("libicui18n.so"), SYSTEM_LIB("libicuuc.so"), SYSTEM_LIB("libneuralnetworks.so")};

  // Libraries from greylist.  Only convert these for apps targeting N or below.
  static constexpr const char* kPathTranslationN[][2] = {SYSTEM_LIB("libandroid_runtime.so"),
                                                         SYSTEM_LIB("libbinder.so"),
                                                         SYSTEM_LIB("libcrypto.so"),
                                                         SYSTEM_LIB("libcutils.so"),
                                                         SYSTEM_LIB("libexpat.so"),
                                                         SYSTEM_LIB("libgui.so"),
                                                         SYSTEM_LIB("libmedia.so"),
                                                         SYSTEM_LIB("libnativehelper.so"),
                                                         SYSTEM_LIB("libssl.so"),
                                                         SYSTEM_LIB("libstagefright.so"),
                                                         SYSTEM_LIB("libsqlite.so"),
                                                         SYSTEM_LIB("libui.so"),
                                                         SYSTEM_LIB("libutils.so"),
                                                         SYSTEM_LIB("libvorbisidec.so")};

  if (name == nullptr) {
    return false;
  }

  auto comparator = [name](auto p) { return strcmp(name, p[0]) == 0; };

  if (auto it = std::find_if(std::begin(kPathTranslation), std::end(kPathTranslation), comparator);
      it != std::end(kPathTranslation)) {
    *out_name_to_apex = (*it)[1];
    return true;
  }

  if (get_application_target_sdk_version() < __ANDROID_API_Q__) {
    if (auto it =
            std::find_if(std::begin(kPathTranslationQ), std::end(kPathTranslationQ), comparator);
        it != std::end(kPathTranslationQ)) {
      *out_name_to_apex = (*it)[1];
      return (*it)[1];
      return true;
    }
  }

  if (get_application_target_sdk_version() < __ANDROID_API_N__) {
    if (auto it =
            std::find_if(std::begin(kPathTranslationN), std::end(kPathTranslationN), comparator);
        it != std::end(kPathTranslationN)) {
      *out_name_to_apex = (*it)[1];
      return true;
    }
  }

  return false;
}
// End Workaround for dlopen(/system/lib/<soname>) when .so is in /apex.
