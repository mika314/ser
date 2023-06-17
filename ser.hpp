#pragma once
#include "is_serializable.hpp"
#include "istrm.hpp"
#include "ostrm.hpp"

#include <array>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace Internal
{
  template <typename T>
  constexpr auto serVal(OStrm &strm, const T &value) noexcept
    -> std::enable_if_t<std::is_arithmetic_v<T> || std::is_enum_v<T>>;

  auto serVal(OStrm &strm, const std::string &value) noexcept -> void;

  template <typename T>
  constexpr auto serVal(OStrm &strm, const std::vector<T> &value) -> void;

  template <typename T>
  constexpr auto serVal(OStrm &strm, const std::unique_ptr<T> &value) -> void;

  template <typename T>
  constexpr auto serVal(OStrm &strm, const std::optional<T> &value) -> void;

  template <typename T, typename U>
  constexpr auto serVal(OStrm &strm, const std::unordered_map<T, U> &value) -> void;

  template <typename T, typename U>
  constexpr auto serVal(OStrm &strm, const std::map<T, U> &value) -> void;

  template <typename T, typename U>
  constexpr auto serVal(OStrm &strm, const std::pair<T, U> &value) -> void;

  template <typename... T>
  constexpr auto serVal(OStrm &strm, const std::variant<T...> &value) -> void;

  template <typename T, size_t N>
  constexpr auto serVal(OStrm &strm, const std::array<T, N> &value) -> void;

  template <typename T>
  constexpr auto deserVal(IStrm &strm, T &value) noexcept
    -> std::enable_if_t<std::is_arithmetic_v<T> || std::is_enum_v<T>>;

  auto deserVal(IStrm &strm, std::string &value) noexcept -> void;

  template <typename T>
  constexpr auto deserVal(IStrm &strm, std::vector<T> &value) -> void;

  template <typename T>
  constexpr auto deserVal(IStrm &strm, std::unique_ptr<T> &value) -> void;

  template <typename T>
  constexpr auto deserVal(IStrm &strm, std::optional<T> &value) -> void;

  template <typename T, typename U>
  constexpr auto deserVal(IStrm &strm, std::unordered_map<T, U> &value) -> void;

  template <typename T, typename U>
  constexpr auto deserVal(IStrm &strm, std::map<T, U> &value) -> void;

  template <typename T, typename U>
  constexpr auto deserVal(IStrm &strm, std::pair<T, U> &value) -> void;

  template <typename T, size_t N>
  constexpr auto deserVal(IStrm &strm, std::array<T, N> &value) -> void;

  template <int32_t TypeIdx, typename... T>
  constexpr auto readVariant(IStrm &strm, int32_t type, std::variant<T...> &value) -> void;

  template <typename... T>
  constexpr auto deserVal(IStrm &strm, std::variant<T...> &value) -> void;
} // namespace Internal

class Ser
{
public:
  constexpr Ser(OStrm &strm) : strm(strm) {}
  template <typename T>
  constexpr auto operator()(const char *, const T &value) -> void
  {
    if constexpr (Internal::IsSerializableClassV<T>)
    {
      Ser s(strm);
      value.ser(s);
    }
    else
      Internal::serVal(strm, value);
  }

private:
  OStrm &strm;
};

class Deser
{
public:
  constexpr Deser(IStrm &strm) : strm(strm) {}
  template <typename T>
  constexpr auto operator()(const char *, T &value) -> void
  {
    if constexpr (Internal::IsSerializableClassV<T>)
    {
      Deser s(strm);
      value.deser(s);
    }
    else
      Internal::deserVal(strm, value);
  }

private:
  IStrm &strm;
};

namespace Internal
{
  template <typename T>
  constexpr auto serVal(OStrm &strm, const T &value) noexcept
    -> std::enable_if_t<std::is_arithmetic_v<T> || std::is_enum_v<T>>
  {
    strm.write(reinterpret_cast<const char *>(&value), sizeof(value));
  }

  auto serVal(OStrm &strm, const std::string &value) noexcept -> void;

  template <typename T>
  constexpr auto serVal(OStrm &strm, const std::vector<T> &value) -> void
  {
    const auto sz = static_cast<int32_t>(value.size());
    Ser{strm}("sz", sz);
    for (auto &&v : value)
      Ser{strm}("v", v);
  }

  template <typename T>
  constexpr auto serVal(OStrm &strm, const std::unique_ptr<T> &value) -> void
  {
    int32_t isNull = value ? 0 : 1;
    Ser{strm}("isNull", isNull);
    if (value)
      Ser{strm}("*value", *value);
  }

  template <typename T>
  constexpr auto serVal(OStrm &strm, const std::optional<T> &value) -> void
  {
    int32_t isNull = value ? 0 : 1;
    Ser{strm}("isNull", isNull);
    if (value)
      Ser{strm}("*value", *value);
  }

  template <typename T, typename U>
  constexpr auto serVal(OStrm &strm, const std::unordered_map<T, U> &value) -> void
  {
    const auto sz = static_cast<int32_t>(value.size());
    Ser{strm}("sz", sz);
    for (auto &&v : value)
    {
      Ser{strm}("key", v.first);
      Ser{strm}("val", v.second);
    }
  }

  template <typename T, typename U>
  constexpr auto serVal(OStrm &strm, const std::map<T, U> &value) -> void
  {
    const auto sz = static_cast<int32_t>(value.size());
    Ser{strm}("sz", sz);
    for (auto &&v : value)
    {
      Ser{strm}("key", v.first);
      Ser{strm}("val", v.second);
    }
  }

  template <typename T, typename U>
  constexpr auto serVal(OStrm &strm, const std::pair<T, U> &value) -> void
  {
    Ser{strm}("first", value.first);
    Ser{strm}("second", value.second);
  }

  template <typename T, size_t N>
  constexpr auto serVal(OStrm &strm, const std::array<T, N> &value) -> void
  {
    for (const auto &v : value)
      Ser{strm}("value", v);
  }

  template <typename... T>
  constexpr auto serVal(OStrm &strm, const std::variant<T...> &value) -> void
  {
    Ser{strm}("type", static_cast<int32_t>(value.index()));
    std::visit([&](const auto &val) { Ser{strm}("value", val); }, value);
  }

  template <typename T>
  constexpr auto deserVal(IStrm &strm, T &value) noexcept
    -> std::enable_if_t<std::is_arithmetic_v<T> || std::is_enum_v<T>>
  {
    strm.read(reinterpret_cast<char *>(&value), sizeof(value));
  }

  auto deserVal(IStrm &strm, std::string &value) noexcept -> void;

  template <typename T>
  constexpr auto deserVal(IStrm &strm, std::vector<T> &value) -> void
  {
    value.clear();
    int32_t sz{};
    Deser{strm}("sz", sz);
    value.reserve(sz);
    for (auto i = 0; i < sz; ++i)
    {
      T &v = value.emplace_back();
      Deser{strm}("v", v);
    }
  }

  template <typename T>
  constexpr auto deserVal(IStrm &strm, std::unique_ptr<T> &value) -> void
  {
    int32_t isNull{};
    Deser{strm}("isNull", isNull);
    if (isNull == 1)
    {
      value = nullptr;
      return;
    }

    value = std::make_unique<T>();
    Deser{strm}("*value", *value);
  }

  template <typename T>
  constexpr auto deserVal(IStrm &strm, std::optional<T> &value) -> void
  {
    int32_t isNull{};
    Deser{strm}("isNull", isNull);
    if (isNull == 1)
    {
      value = std::nullopt;
      return;
    }

    value = T{};
    Deser{strm}("*value", *value);
  }

  template <typename T, typename U>
  constexpr auto deserVal(IStrm &strm, std::unordered_map<T, U> &value) -> void
  {
    value.clear();
    int32_t sz{};
    Deser{strm}("sz", sz);
    for (auto i = 0; i < sz; ++i)
    {
      T key;
      Deser{strm}("key", key);
      U val;
      Deser{strm}("val", val);
      value[key] = std::move(val);
    }
  }

  template <typename T, typename U>
  constexpr auto deserVal(IStrm &strm, std::map<T, U> &value) -> void
  {
    value.clear();
    int32_t sz{};
    Deser{strm}("sz", sz);
    for (auto i = 0; i < sz; ++i)
    {
      T key;
      Deser{strm}("key", key);
      U val;
      Deser{strm}("val", val);
      value[key] = std::move(val);
    }
  }

  template <typename T, typename U>
  constexpr auto deserVal(IStrm &strm, std::pair<T, U> &value) -> void
  {
    Deser{strm}("first", value.first);
    Deser{strm}("second", value.second);
  }

  template <typename T, size_t N>
  constexpr auto deserVal(IStrm &strm, std::array<T, N> &value) -> void
  {
    for (auto &v : value)
      Deser{strm}("value", v);
  }

  template <int32_t TypeIdx, typename... T>
  constexpr auto readVariant(IStrm &strm, int32_t type, std::variant<T...> &value) -> void
  {
    using MyVariant = std::variant<T...>;
    if (TypeIdx == type)
    {
      std::variant_alternative_t<TypeIdx, MyVariant> v{};
      Deser{strm}("val", v);
      value = v;
      return;
    }

    if constexpr (TypeIdx > 0)
      readVariant<TypeIdx - 1, T...>(strm, type, value);
  }

  template <typename... T>
  constexpr auto deserVal(IStrm &strm, std::variant<T...> &value) -> void
  {
    using MyVariant = std::variant<T...>;
    int32_t type{};
    Deser{strm}("type", type);
    readVariant<std::variant_size_v<MyVariant> - 1, T...>(strm, type, value);
  }
} // namespace Internal

template <typename T>
constexpr auto ser(OStrm &strm, const T &value) -> void
{
  Ser s(strm);
  if constexpr (Internal::IsSerializableClassV<T>)
    value.ser(s);
  else
    s("value", value);
}

template <typename T>
constexpr auto deser(IStrm &strm, T &value) -> void
{
  Deser s(strm);
  if constexpr (Internal::IsSerializableClassV<T>)
    value.deser(s);
  else
    s("value", value);
}
