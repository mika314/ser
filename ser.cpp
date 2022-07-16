#include "ser.hpp"

namespace Internal
{
  auto serVal(OStrm &strm, const std::string &value) noexcept -> void
  {
    auto sz{static_cast<int32_t>(value.size())};
    strm.write(reinterpret_cast<const char *>(&sz), sizeof(sz));
    strm.write(reinterpret_cast<const char *>(value.data()), sz);
  }

  auto deserVal(IStrm &strm, std::string &value) noexcept -> void
  {
    int32_t sz{};
    strm.read(reinterpret_cast<char *>(&sz), sizeof(sz));
    value.resize(sz);
    strm.read(reinterpret_cast<char *>(value.data()), sz);
  }
} // namespace Internal
