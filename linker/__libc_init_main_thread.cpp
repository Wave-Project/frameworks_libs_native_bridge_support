// Copyright (c) 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <async_safe/log.h>

#include "bionic/pthread_internal.h"
#include "native_bridge_support/linker/static_tls_config.h"
#include "private/KernelArgumentBlock.h"
#include "private/bionic_arc4random.h"
#include "private/bionic_elf_tls.h"
#include "private/bionic_globals.h"
#include "private/bionic_ssp.h"
#include "private/bionic_tls.h"

// Once the loader has calculated the size of static TLS, report the information
// to the host so it can allocate the static TLS of future threads.
extern "C" void __native_bridge_config_static_tls(const NativeBridgeStaticTlsConfig* config);

// Get the current thread's host pthread_internal_t.
extern "C" pthread_t __native_bridge_get_host_pthread();

// The host has already initialized the thread and created its
// pthread_internal_t object. The guest needs to initialize its globals and the
// main thread's guest static TLS memory.
extern "C" void __libc_init_main_thread_early(const KernelArgumentBlock& args,
                                              bionic_tcb* temp_tcb) {
  __libc_shared_globals()->auxv = args.auxv;
#if defined(__i386__)
  __libc_init_sysinfo();
#endif
  // TCB layout is different between host and guest, so initialize the guest
  // TCB. Reuse the host's pthread_internal_t and bionic_tls objects.
  auto host_thread = reinterpret_cast<pthread_internal_t*>(__native_bridge_get_host_pthread());
  __init_tcb(temp_tcb, host_thread);
  __set_tls(&temp_tcb->tls_slot(0));
}

extern "C" void __libc_init_main_thread_late() {
  // Reuse the host's bionic_tls structure.
  __get_tls()[TLS_SLOT_BIONIC_TLS] = __get_thread()->bionic_tls;

  // There's currently no way for the guest to query the host's stack guard
  // cookie, so just generate a new one.
  __libc_safe_arc4random_buf(&__stack_chk_guard, sizeof(__stack_chk_guard));
  __init_tcb_stack_guard(__get_bionic_tcb());
}

extern "C" void __libc_init_main_thread_final() {
  const StaticTlsLayout& layout = __libc_shared_globals()->static_tls_layout;

  // Prepare the initialization image for the host.
  char* init_img = new char[layout.size()]{};
  __init_static_tls(init_img);
  bionic_tcb img_tcb = {};
  __init_tcb_dtv(&img_tcb);
  __init_tcb_stack_guard(&img_tcb);
  memcpy(init_img + layout.offset_bionic_tcb(), &img_tcb, sizeof(img_tcb));

  // Configure the host to create guest static TLS memory for new threads. The
  // host will replace the guest main thread's static TLS with memory it
  // allocates.
  NativeBridgeStaticTlsConfig config{};
  config.size = layout.size();
  config.tpoff = layout.offset_thread_pointer();
  config.tls_slot_thread_id = TLS_SLOT_THREAD_ID;
  config.tls_slot_bionic_tls = TLS_SLOT_BIONIC_TLS;
  config.init_img = init_img;
  __native_bridge_config_static_tls(&config);
}
