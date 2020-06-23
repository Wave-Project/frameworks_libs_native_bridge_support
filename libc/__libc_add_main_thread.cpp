// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Guest libc should not insert main thread into thread list, as it was already done by host libc.
void __libc_add_main_thread() {}
