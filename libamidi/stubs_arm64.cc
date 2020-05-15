// clang-format off
#include "native_bridge_support/vdso/interceptable_functions.h"

DEFINE_INTERCEPTABLE_STUB_FUNCTION(AMidiDevice_fromJava);
DEFINE_INTERCEPTABLE_STUB_FUNCTION(AMidiDevice_getNumInputPorts);
DEFINE_INTERCEPTABLE_STUB_FUNCTION(AMidiDevice_getNumOutputPorts);
DEFINE_INTERCEPTABLE_STUB_FUNCTION(AMidiDevice_getType);
DEFINE_INTERCEPTABLE_STUB_FUNCTION(AMidiDevice_release);
DEFINE_INTERCEPTABLE_STUB_FUNCTION(AMidiInputPort_close);
DEFINE_INTERCEPTABLE_STUB_FUNCTION(AMidiInputPort_open);
DEFINE_INTERCEPTABLE_STUB_FUNCTION(AMidiInputPort_send);
DEFINE_INTERCEPTABLE_STUB_FUNCTION(AMidiInputPort_sendFlush);
DEFINE_INTERCEPTABLE_STUB_FUNCTION(AMidiInputPort_sendWithTimestamp);
DEFINE_INTERCEPTABLE_STUB_FUNCTION(AMidiOutputPort_close);
DEFINE_INTERCEPTABLE_STUB_FUNCTION(AMidiOutputPort_open);
DEFINE_INTERCEPTABLE_STUB_FUNCTION(AMidiOutputPort_receive);

static void __attribute__((constructor(0))) init_stub_library() {
  INIT_INTERCEPTABLE_STUB_FUNCTION("libamidi.so", AMidiDevice_fromJava);
  INIT_INTERCEPTABLE_STUB_FUNCTION("libamidi.so", AMidiDevice_getNumInputPorts);
  INIT_INTERCEPTABLE_STUB_FUNCTION("libamidi.so", AMidiDevice_getNumOutputPorts);
  INIT_INTERCEPTABLE_STUB_FUNCTION("libamidi.so", AMidiDevice_getType);
  INIT_INTERCEPTABLE_STUB_FUNCTION("libamidi.so", AMidiDevice_release);
  INIT_INTERCEPTABLE_STUB_FUNCTION("libamidi.so", AMidiInputPort_close);
  INIT_INTERCEPTABLE_STUB_FUNCTION("libamidi.so", AMidiInputPort_open);
  INIT_INTERCEPTABLE_STUB_FUNCTION("libamidi.so", AMidiInputPort_send);
  INIT_INTERCEPTABLE_STUB_FUNCTION("libamidi.so", AMidiInputPort_sendFlush);
  INIT_INTERCEPTABLE_STUB_FUNCTION("libamidi.so", AMidiInputPort_sendWithTimestamp);
  INIT_INTERCEPTABLE_STUB_FUNCTION("libamidi.so", AMidiOutputPort_close);
  INIT_INTERCEPTABLE_STUB_FUNCTION("libamidi.so", AMidiOutputPort_open);
  INIT_INTERCEPTABLE_STUB_FUNCTION("libamidi.so", AMidiOutputPort_receive);
}
// clang-format on
