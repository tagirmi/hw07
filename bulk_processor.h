#pragma once

#include "bulk.h"

namespace hw7 {

class BulkProcessor : public BulkObserver
{
  public:
    BulkProcessor() = default;
    ~BulkProcessor() = default;

    void update(const std::tuple<BulkTime, Bulk>&) override;
};

} // hw7

