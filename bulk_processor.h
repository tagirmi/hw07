#pragma once

#include "bulk.h"

namespace hw7 {

class BulkProcessor : public BulkObserver
{
public:
  BulkProcessor() = default;
  ~BulkProcessor() = default;

  void update(const BulkTime&, const Bulk&) override;
};

} // hw7

