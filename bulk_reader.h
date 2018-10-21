#pragma once

#include <list>
#include <memory>

#include "bulk.h"

namespace hw7 {

namespace details {

class BulkCollector;

} // details

class BulkReader
{
public:
  explicit BulkReader(size_t bulkSize);
  ~BulkReader();

  void subscribe(const std::shared_ptr<BulkObserver>&);
  void read();

private:
  void notify(const BulkTime&, const Bulk&);

  std::list<std::weak_ptr<BulkObserver>> m_observers;
  std::unique_ptr<details::BulkCollector> m_bulkCollector;
};

} // hw7
