#ifndef UTIL_LOGGER_H
#define UTIL_LOGGER_H
#include <format>

namespace util {

template <typename... Args>
void debug(const std::string_view& str, Args&&... args) {
#if DEBUG
  std::cout << std::vformat(str, std::make_format_args(args...));
#endif
}
}  // namespace util
#endif  // UTIL_LOGGER_H