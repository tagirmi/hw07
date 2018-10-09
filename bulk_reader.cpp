#include <cassert>
#include <iostream>

#include "bulk_reader.h"

// BulkReaderStates
void hw7::details::EmptyBulk::handle(const std::string& command)
{
  m_reader.createBulk();
  m_reader.addCommand(command);
  if (m_reader.isBulkReady())
    m_reader.changeState(std::make_unique<ReadyBulk>(m_reader));
  else
    m_reader.changeState(std::make_unique<NotReadyBulk>(m_reader));
}

void hw7::details::NotReadyBulk::handle(const std::string& command)
{

}

void hw7::details::ReadyBulk::handle(const std::string&)
{

}

// BulkReader
hw7::BulkReader::BulkReader(int bulkSize)
  : m_observers{}
  , m_currentState{std::make_unique<details::EmptyBulk>}
  , m_bulkSize{bulkSize}
  , m_bulk{}
  , m_bulkTime{}
{
}

void hw7::BulkReader::subscribe(BulkObserver* observer)
{
  assert(observer);

  m_observers.emplace_back(observer);
}

void hw7::BulkReader::read()
{
  for(std::string line; std::getline(std::cin, line);)
    m_currentState->handle(line);
}

void hw7::BulkReader::changeState(std::unique_ptr<details::ReaderState> state)
{
  m_currentState = std::move(state);
}

void hw7::BulkReader::notify() const
{
  for (auto& i : m_observers)
    i->update(m_bulkTime, m_bulk);
}

void hw7::BulkReader::createBulk()
{
  m_bulkTime = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
  m_bulk.clear();
}

void hw7::BulkReader::addCommand(const std::string& command)
{
  m_bulk.emplace_back(command);
}

bool hw7::BulkReader::isBulkReady() const
{
  return !(m_bulk.size() < m_bulkSize);
}
