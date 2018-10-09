#include <cassert>
#include <iostream>

#include "bulk_reader.h"

hw7::BulkReader::BulkReader(int bulkSize) : m_bulkSize{bulkSize}, m_observers{}
{
}

void hw7::BulkReader::subscribe(BulkObserver* observer)
{
  assert(observer);

  m_observers.emplace_back(observer);
}

void hw7::BulkReader::read()
{
  Bulk bulk;
  bulk.reserve(m_bulkSize);

  for(std::string line; std::getline(std::cin, line);) {
    //        if (line == "{") TODO FSM?

    bulk.emplace_back(line);
    if (bulk.size() < m_bulkSize)
      continue;

    notify(std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now()), bulk);
    bulk.clear();
  }
}

void hw7::BulkReader::notify(const BulkTime& time, const hw7::Bulk& bulk)
{
  for (auto& i : m_observers)
    i->update(std::make_tuple(time, bulk));
}
