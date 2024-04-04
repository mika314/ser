#pragma once

// obsolete way to define structures

#define SER_PROP(property) arch(#property, property)

#define SER_DEF_PROPS()         \
  enum { IsSerializableClass }; \
  template <typename Arch>      \
  void ser(Arch &arch) const    \
  {                             \
    (void)arch;                 \
    SER_PROP_LIST               \
  }                             \
  template <typename Arch>      \
  void deser(Arch &arch)        \
  {                             \
    (void)arch;                 \
    SER_PROP_LIST               \
  }

#define SER_DEF_SUPER(className) \
  template <typename Arch>       \
  void super(Arch &arch) const   \
  {                              \
    className::ser(arch);        \
  }                              \
  template <typename Arch>       \
  void super(Arch &arch)         \
  {                              \
    className::deser(arch);      \
  }

// a better way to define structures
#define SER_STRUCT(name) \
  struct name            \
  {                      \
    static constexpr const char *className = #name;

#define SER_EXPAND(x) x
#define SER_FOR_EACH_0(x) (void)arch;
#define SER_FOR_EACH_1(x, ...) arch(#x, x);
#define SER_FOR_EACH_2(x, ...) \
  arch(#x, x);                 \
  SER_EXPAND(SER_FOR_EACH_1(__VA_ARGS__))
#define SER_FOR_EACH_3(x, ...) \
  arch(#x, x);                 \
  SER_EXPAND(SER_FOR_EACH_2(__VA_ARGS__))
#define SER_FOR_EACH_4(x, ...) \
  arch(#x, x);                 \
  SER_EXPAND(SER_FOR_EACH_3(__VA_ARGS__))
#define SER_FOR_EACH_5(x, ...) \
  arch(#x, x);                 \
  SER_EXPAND(SER_FOR_EACH_4(__VA_ARGS__))
#define SER_FOR_EACH_6(x, ...) \
  arch(#x, x);                 \
  SER_EXPAND(SER_FOR_EACH_5(__VA_ARGS__))
#define SER_FOR_EACH_7(x, ...) \
  arch(#x, x);                 \
  SER_EXPAND(SER_FOR_EACH_6(__VA_ARGS__))
#define SER_FOR_EACH_8(x, ...) \
  arch(#x, x);                 \
  SER_EXPAND(SER_FOR_EACH_7(__VA_ARGS__))
#define SER_FOR_EACH_9(x, ...) \
  arch(#x, x);                 \
  SER_EXPAND(SER_FOR_EACH_8(__VA_ARGS__))
#define SER_FOR_EACH_10(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_9(__VA_ARGS__))
#define SER_FOR_EACH_11(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_10(__VA_ARGS__))
#define SER_FOR_EACH_12(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_11(__VA_ARGS__))
#define SER_FOR_EACH_13(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_12(__VA_ARGS__))
#define SER_FOR_EACH_14(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_13(__VA_ARGS__))
#define SER_FOR_EACH_15(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_14(__VA_ARGS__))
#define SER_FOR_EACH_16(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_15(__VA_ARGS__))
#define SER_FOR_EACH_17(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_16(__VA_ARGS__))
#define SER_FOR_EACH_18(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_17(__VA_ARGS__))
#define SER_FOR_EACH_19(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_18(__VA_ARGS__))
#define SER_FOR_EACH_20(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_19(__VA_ARGS__))
#define SER_FOR_EACH_21(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_20(__VA_ARGS__))
#define SER_FOR_EACH_22(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_21(__VA_ARGS__))
#define SER_FOR_EACH_23(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_22(__VA_ARGS__))
#define SER_FOR_EACH_24(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_23(__VA_ARGS__))
#define SER_FOR_EACH_25(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_24(__VA_ARGS__))
#define SER_FOR_EACH_26(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_25(__VA_ARGS__))
#define SER_FOR_EACH_27(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_26(__VA_ARGS__))
#define SER_FOR_EACH_28(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_27(__VA_ARGS__))
#define SER_FOR_EACH_29(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_28(__VA_ARGS__))
#define SER_FOR_EACH_30(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_29(__VA_ARGS__))
#define SER_FOR_EACH_31(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_30(__VA_ARGS__))
#define SER_FOR_EACH_32(x, ...) \
  arch(#x, x);                  \
  SER_EXPAND(SER_FOR_EACH_31(__VA_ARGS__))

#define SER_COUNT_ARGS_IMPL(x,   \
                            _1,  \
                            _2,  \
                            _3,  \
                            _4,  \
                            _5,  \
                            _6,  \
                            _7,  \
                            _8,  \
                            _9,  \
                            _10, \
                            _11, \
                            _12, \
                            _13, \
                            _14, \
                            _15, \
                            _16, \
                            _17, \
                            _18, \
                            _19, \
                            _20, \
                            _21, \
                            _22, \
                            _23, \
                            _24, \
                            _25, \
                            _26, \
                            _27, \
                            _28, \
                            _29, \
                            _30, \
                            _31, \
                            _32, \
                            N,   \
                            ...) \
  N
#define SER_COUNT_ARGS_HELPER(...)              \
  SER_EXPAND(SER_COUNT_ARGS_IMPL(0,             \
                                 ##__VA_ARGS__, \
                                 32,            \
                                 31,            \
                                 30,            \
                                 29,            \
                                 28,            \
                                 27,            \
                                 26,            \
                                 25,            \
                                 24,            \
                                 23,            \
                                 22,            \
                                 21,            \
                                 20,            \
                                 19,            \
                                 18,            \
                                 17,            \
                                 16,            \
                                 15,            \
                                 14,            \
                                 13,            \
                                 12,            \
                                 11,            \
                                 10,            \
                                 9,             \
                                 8,             \
                                 7,             \
                                 6,             \
                                 5,             \
                                 4,             \
                                 3,             \
                                 2,             \
                                 1,             \
                                 0))
#define SER_COUNT_ARGS(...) SER_COUNT_ARGS_HELPER(__VA_ARGS__)

#define SER_FOR_EACH_N(N, ...) SER_EXPAND(SER_CONCAT(SER_FOR_EACH_, N)(__VA_ARGS__))
#define SER_CONCAT_IMPL(a, b) a##b
#define SER_CONCAT(a, b) SER_CONCAT_IMPL(a, b)

#define SER_PROPS(...)                                       \
  enum { IsSerializableClass };                              \
  void ser(auto &arch) const                                 \
  {                                                          \
    SER_FOR_EACH_N(SER_COUNT_ARGS(__VA_ARGS__), __VA_ARGS__) \
  }                                                          \
  void deser(auto &arch)                                     \
  {                                                          \
    SER_FOR_EACH_N(SER_COUNT_ARGS(__VA_ARGS__), __VA_ARGS__) \
  }

#define SER_EMPTY_PROPS()       \
  enum { IsSerializableClass }; \
  void ser(auto &) const {}     \
  void deser(auto &) {}

#define SER_END }
