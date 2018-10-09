#include <iostream>

#include "bulk_reader.h"
#include "bulk_processor.h"
#include "bulk_logger.h"

int main(int argc, char* argv[])
{
  try
  {
    const int maxBulkSize = 3; //TODO use boost::program_options

    hw7::BulkProcessor processor;
    hw7::BulkLogger logger;

    hw7::BulkReader reader{maxBulkSize};

    reader.subscribe(&processor);
    reader.subscribe(&logger);

    reader.read();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
