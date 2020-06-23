extern char __gnu_ldivmod_helper;
extern char __gnu_uldivmod_helper;
extern char __udivdi3;

void* __more_bionic_libgcc_compat_symbols[] = {
    &__gnu_ldivmod_helper,
    &__gnu_uldivmod_helper,
    &__udivdi3,
};
