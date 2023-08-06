#pragma once

namespace minicc {
class Noncopyable {
public:
  Noncopyable(const Noncopyable &) = delete;
  Noncopyable &operator=(const Noncopyable &) = delete;

protected:
  Noncopyable() = default;
  ~Noncopyable() = default;
};
} // namespace minicc
