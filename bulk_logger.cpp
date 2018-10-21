#include <fstream>
#include <sstream>

#include "bulk_logger.h"

namespace {

std::string getBulkLogName(const hw7::BulkTime& time)
{
  std::stringstream ss;
  ss << "bulk" << time.time_since_epoch().count() << ".log";
  return ss.str();
}

}

void hw7::BulkLogger::update(const BulkTime& time, const Bulk& bulk)
{
  std::ofstream fs{getBulkLogName(time)};

  fs << bulk;

  fs.close();
}
