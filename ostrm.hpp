#pragma once
#include <string>

class OStrm
{
public:
  OStrm(char *beg, const char *const end) : beg(beg), p(beg), end(end) {}
  OStrm(const OStrm &) = delete;
  OStrm &operator=(const OStrm &) = delete;
  constexpr auto write(const char *b, size_t sz) noexcept -> void
  {
    for (; sz > 0 && p != end; --sz, ++b, ++p)
      *p = *b;
  }
  constexpr auto size() const -> size_t { return p - beg; }
  constexpr auto clear() -> void { p = beg; }

private:
  char *beg;
  char *p;
  const char *const end;
};
