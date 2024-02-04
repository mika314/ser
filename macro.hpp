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

#define SER_COUNT_ARGS_IMPL(x, _1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define SER_COUNT_ARGS_HELPER(...) \
  SER_EXPAND(SER_COUNT_ARGS_IMPL(0, ##__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0))
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
