#pragma once
#include <string>

class OStrm
{
public:
  OStrm(char *aBeg, const char *const aEnd) : beg(aBeg), p(aBeg), end(aEnd) {}
  OStrm(const OStrm &) = delete;
  OStrm &operator=(const OStrm &) = delete;
  constexpr auto write(const char *b, size_t sz) noexcept -> void
  {
    for (; sz > 0 && p != end; --sz, ++b, ++p)
      *p = *b;
  }
  constexpr auto size() const -> size_t { return static_cast<size_t>(p - beg); }
  constexpr auto clear() -> void { p = beg; }

private:
  char *beg;
  char *p;
  const char *const end;
};
