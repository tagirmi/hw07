#pragma once

#include <list>
#include <memory>

#include "bulk.h"

namespace hw7 {

class BulkReader;

namespace details {

class ReaderState
{
  public:
    explicit ReaderState(BulkReader&);

    virtual void handle(const std::string&);

  protected:
    BulkReader& m_reader;
};

class EmptyBulk : public ReaderState
{
  public:
    void handle(const std::string&) override;
};

class NotReadyBulk : public ReaderState
{
  public:
    void handle(const std::string&) override;
};

class ReadyBulk : public ReaderState
{
  public:
    void handle(const std::string&) override;
};

}

class BulkReader
{
  public:
    explicit BulkReader(int bulkSize);

    void subscribe(BulkObserver*);
    void read();

  private:
    void changeState(std::unique_ptr<details::ReaderState>);
    void notify();
    void createBulk();
    void addCommand(const std::string&);
    bool isBulkReady() const;

    std::list<BulkObserver*> m_observers;
    std::unique_ptr<details::ReaderState> m_currentState;
    int m_bulkSize;
    Bulk m_bulk;
    BulkTime m_bulkTime;

    friend class details::ReaderState;
};

} // hw7
