#pragma once

#include <vector>

#include "bulk.h"

namespace hw7 {

class BulkReader
{
  public:
    explicit BulkReader(int bulkSize);

    void subscribe(BulkObserver*);

    void read();

  private:
    void notify(const BulkTime&, const Bulk&);

    int m_bulkSize;
    std::vector<BulkObserver*> m_observers;
};

} // hw7
