#pragma once

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
  enum { IsSerializableClass };  \
  template <typename Arch>       \
  void ser(Arch &arch) const     \
  {                              \
    className::ser(arch);        \
    SER_PROP_LIST                \
  }                              \
  template <typename Arch>       \
  void deser(Arch &arch)         \
  {                              \
    className::deser(arch);      \
    SER_PROP_LIST                \
  }
