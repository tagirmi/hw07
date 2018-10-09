#pragma once

#include "bulk.h"

namespace hw7 {

class BulkLogger : public BulkObserver
{
  public:
    void update(const std::tuple<BulkTime, Bulk>&) override;
};

} // hw7
