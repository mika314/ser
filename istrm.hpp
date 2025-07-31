#pragma once
#include <algorithm>
#include <cstdint>
#include <cstring>

class IStrm
{
public:
  constexpr IStrm(const char *aB, const char *aE) noexcept : b(aB), e(aE) {}
  constexpr auto read(char *buff, const std::size_t sz) noexcept -> size_t
  {
    auto cnt = sz;
    for (; b != e && cnt > 0; ++b, --cnt, ++buff)
      *buff = *b;
    return sz - cnt;
  }

private:
  const char *b;
  const char *e;
};
