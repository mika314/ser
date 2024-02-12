#pragma once
#include "istrm.hpp"
#include "ostrm.hpp"
#include "schema.hpp"
#include "ser.hpp"
#include <array>
#include <sstream>

namespace Internal
{
  template <typename X, typename H, typename... T>
  struct IndexOf
  {
    static const int32_t Value = []() {
      if constexpr (std::is_same_v<H, X>)
        return 0;
      else
        return IndexOf<X, T...>::Value + 1;
    }();
  };

#ifndef SER_VERSION
  template <typename H, typename... T>
  struct SerAllDefCtord
  {
  public:
    constexpr auto operator()(OStrm &strm) const -> void
    {
      H h{};
      ::schema(strm, h);
      SerAllDefCtord<T...>{}(strm);
    }
  };

  template <typename H>
  struct SerAllDefCtord<H>
  {
  public:
    constexpr auto operator()(OStrm &strm) const -> void
    {
      H h{};
      ::schema(strm, h);
    }
  };

  auto calcMd5Hash(const char *data, const size_t size) -> uint32_t;
#endif
} // namespace Internal

template <typename... Args>
class Proto
{
public:
  template <typename Msg>
  static constexpr auto ser(OStrm &strm, const Msg &msg) -> void
  {
    auto msgId = Internal::IndexOf<Msg, Args...>::Value;
    ::ser(strm, msgId);
    ::ser(strm, msg);
  }

  template <typename Msg>
  static auto ser(const Msg &msg, char *beg, const char *const end) -> size_t
  {
    auto strm = OStrm{beg, end};
    ser(strm, msg);
    return strm.size();
  }

  template <typename Vis>
  static constexpr auto deser(const IStrm &cstrm, Vis &&vis) -> void
  {
    auto strm = cstrm;
    int32_t msgId{};
    ::deser(strm, msgId);
    deserById(0, strm, std::move(vis), msgId, Args{}...);
  }

  template <typename Vis>
  static constexpr auto deser(const char *b, const char *e, Vis &&vis) -> void
  {
    deser(IStrm{b, e}, std::move(vis));
  }

  static auto version() -> uint32_t
  {
#ifndef SER_VERSION
    static uint32_t version = calcMd5Hash();
#else
    static uint32_t version = SER_VERSION;
#endif
    return version;
  }

private:
  template <typename Arg, typename Vis, typename... Tail>
  static constexpr auto deserById(int32_t idx, IStrm &strm, Vis &&vis, int32_t msgId, Arg, Tail... tail)
    -> void
  {
    if (msgId != idx)
      return deserById(idx + 1, strm, std::move(vis), msgId, tail...);
    Arg m;
    ::deser(strm, m);
    vis(std::move(m));
  }

  template <typename Vis>
  static constexpr auto deserById(int32_t, IStrm &, Vis &&, int32_t msgId) -> void
  {
    // throw std::runtime_error("Unknown msgId: " + std::to_string(msgId));
  }

#ifndef SER_VERSION
  static auto calcMd5Hash() -> uint32_t
  {
    std::array<char, 64 * 1024> buf;
    OStrm strm(buf.data(), buf.data() + buf.size());
    Internal::SerAllDefCtord<Args...>{}(strm);
    return Internal::calcMd5Hash(buf.data(), strm.size());
  }
#endif
};
