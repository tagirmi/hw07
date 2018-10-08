#include <cassert>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

const int maxBulkSize = 3; //TODO use boost::program_options

std::string getBulkLogName()
{
  auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
  std::stringstream ss;
  ss << "bulk" << now.time_since_epoch().count() << ".log";
  return ss.str();
}

using Bulk = std::vector<std::string>;

std::ostream& operator<<(std::ostream& os, const Bulk& bulk)
{
  os << "bulk: ";
  for (auto i = bulk.cbegin(); i != bulk.cend(); ++i) {
    if (i != bulk.cbegin())
      os << ", ";
    os << *i;
  }
  return os;
}

void test()
{
  std::cout << getBulkLogName() << std::endl;
  std::cout << Bulk{"cmd1", "cmd3"};
}

} // namespace

struct IBulkObserver
{
  virtual void update(const Bulk&) = 0;
  virtual ~IBulkObserver() = default;
};

class BulkReader
{
  public:
    explicit BulkReader(int bulkSize) : m_bulkSize{bulkSize}, m_observers{}
    {
    }

    void subscribe(IBulkObserver* observer)
    {
      assert(observer);

      m_observers.emplace_back(observer);
    }

    void read()
    {
      Bulk bulk;
      bulk.reserve(bulkSize);

      for(std::string line; std::getline(std::cin, line);) {
        if (bulk.size() < bulkSize) {
          bulk.emplace_back(line);
        }
        else {
          notify(bulk);
          bulk.clear();
        }
      }
    }

  private:
    void notify(const Bulk& bulk)
    {
      for (auto& i : m_observers)
        i->update(bulk);
    }

    int m_bulkSize;
    std::vector<IBulkObserver*> m_observers;
};

class BulkProcessor : IBulkObserver
{
  public:
    explicit BulkProcessor(BulkReader&);

    void update(const Bulk&) override;
};

class BulkLogger : IBulkObserver
{
  public:
    explicit BulkLogger(BulkReader&);

    void update(const Bulk&) override;
};

int main(int argc, char* argv[])
{
  try
  {
    BulkReader reader{maxBulkSize};
    BulkProcessor processor{reader};
    BulkLogger logger{reader};

    reader.read();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
