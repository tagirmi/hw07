#include <iostream>

#include "bulk_processor.h"

void hw7::BulkProcessor::update(const BulkTime&, const Bulk& bulk)
{
  std::cout << bulk << std::endl;
}
