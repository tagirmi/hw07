#include <cassert>
#include <functional>
#include <iostream>

#include "bulk_reader.h"
#include "bulk_collector.h"

hw7::BulkReader::BulkReader(size_t bulkSize)
  : m_observers{}
{
  using namespace std::placeholders;
  m_bulkCollector = std::make_unique<details::BulkCollector>(bulkSize, std::bind(&BulkReader::notify, this, _1, _2));
}

hw7::BulkReader::~BulkReader()
{
}

void hw7::BulkReader::subscribe(const std::shared_ptr<BulkObserver>& observer)
{
  assert(observer);

  m_observers.emplace_back(observer);
}

void hw7::BulkReader::read()
{
  for (std::string cmd; std::getline(std::cin, cmd);)
    m_bulkCollector->add(cmd);

  m_bulkCollector->endData();
}

void hw7::BulkReader::notify(const BulkTime& bulkTime, const Bulk& bulk)
{
  for (auto& i : m_observers) {
    auto p = i.lock();
    if (p)
      p->update(bulkTime, bulk);
  }
}
