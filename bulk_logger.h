#pragma once

#include "bulk.h"

namespace hw7 {

class BulkLogger : public BulkObserver
{
  public:
    void update(const BulkTime&, const Bulk&) override;
};

} // hw7
