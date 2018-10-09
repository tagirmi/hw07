#pragma once

#include <chrono>
#include <ostream>
#include <string>
#include <vector>
#include <tuple>


namespace hw7 {

using Bulk = std::vector<std::string>;
using BulkTime = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>;

struct BulkObserver
{
  virtual void update(const std::tuple<BulkTime, Bulk>&) = 0;
  virtual ~BulkObserver() = default;
};

} // hw7

inline std::ostream& operator<<(std::ostream& os, const hw7::Bulk& bulk)
{
  os << "bulk: ";
  for (auto i = bulk.cbegin(); i != bulk.cend(); ++i) {
    if (i != bulk.cbegin())
      os << ", ";
    os << *i;
  }
  return os;
}

