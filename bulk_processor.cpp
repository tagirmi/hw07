#include <iostream>

#include "bulk_processor.h"

void hw7::BulkProcessor::update(const std::tuple<BulkTime, Bulk>& bulk)
{
  std::cout << std::get<1>(bulk);
}
