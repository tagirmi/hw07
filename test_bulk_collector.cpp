#include <gtest/gtest.h>

#include "bulk_collector.h"

using BulkCollector = hw7::details::BulkCollector;

namespace {

std::string toString(const hw7::Bulk& bulk)
{
  std::string result;
  for (const auto& i : bulk)
    result += i;
  return result;
}

}

TEST(TestBulkCollector, AddOneCommand)
{
  hw7::Bulk bulk;
  auto process = [&bulk](const hw7::BulkTime&, const hw7::Bulk& b){ bulk = b; };
  BulkCollector collector{3, process};

  collector.add("cmd1");

  EXPECT_TRUE(bulk.empty());
}

TEST(TestBulkCollector, AddTwoCommands)
{
  hw7::Bulk bulk;
  auto process = [&bulk](const hw7::BulkTime&, const hw7::Bulk& b){ bulk = b; };
  BulkCollector collector{3, process};

  collector.add("cmd1");
  collector.add("cmd2");

  EXPECT_TRUE(bulk.empty());
}

TEST(TestBulkCollector, AddThreeCommands)
{
  hw7::Bulk bulk;
  auto process = [&bulk](const hw7::BulkTime&, const hw7::Bulk& b){ bulk = b; };
  BulkCollector collector{3, process};

  collector.add("cmd1");
  collector.add("cmd2");
  collector.add("cmd3");

  EXPECT_FALSE(bulk.empty());
  EXPECT_EQ(toString(bulk), "cmd1cmd2cmd3");
}

TEST(TestBulkCollector, EndData)
{
  hw7::Bulk bulk;
  auto process = [&bulk](const hw7::BulkTime&, const hw7::Bulk& b){ bulk = b; };
  BulkCollector collector{3, process};

  collector.add("cmd1");
  collector.endData();

  EXPECT_FALSE(bulk.empty());
  EXPECT_EQ(toString(bulk), "cmd1");
}

TEST(TestBulkCollector, JumpToDynamicBulk)
{
  hw7::Bulk bulk;
  auto process = [&bulk](const hw7::BulkTime&, const hw7::Bulk& b){ bulk = b; };
  BulkCollector collector{3, process};

  collector.add("cmd1");
  collector.add("cmd2");
  collector.add("{");

  EXPECT_FALSE(bulk.empty());
  EXPECT_EQ(toString(bulk), "cmd1cmd2");
}

TEST(TestBulkCollector, DynamicBulk)
{
  hw7::Bulk bulk;
  auto process = [&bulk](const hw7::BulkTime&, const hw7::Bulk& b){ bulk = b; };
  BulkCollector collector{3, process};

  collector.add("{");
  collector.add("cmd1");
  collector.add("cmd2");
  collector.add("cmd3");

  EXPECT_TRUE(bulk.empty());
}

TEST(TestBulkCollector, FinishDynamicBulk)
{
  hw7::Bulk bulk;
  auto process = [&bulk](const hw7::BulkTime&, const hw7::Bulk& b){ bulk = b; };
  BulkCollector collector{3, process};

  collector.add("{");
  collector.add("cmd1");
  collector.add("cmd2");
  collector.add("cmd3");
  collector.add("cmd4");
  collector.add("cmd5");
  collector.add("}");

  EXPECT_FALSE(bulk.empty());
  EXPECT_EQ(toString(bulk), "cmd1cmd2cmd3cmd4cmd5");
}

TEST(TestBulkCollector, NestedBracketsInDynamicBulk)
{
  hw7::Bulk bulk;
  auto process = [&bulk](const hw7::BulkTime&, const hw7::Bulk& b){ bulk = b; };
  BulkCollector collector{3, process};

  collector.add("{");
  collector.add("cmd1");
  collector.add("{");
  collector.add("cmd2");
  collector.add("}");
  collector.add("cmd3");
  collector.add("{");
  collector.add("cmd4");
  collector.add("cmd5");
  collector.add("}");
  collector.add("}");

  EXPECT_FALSE(bulk.empty());
  EXPECT_EQ(toString(bulk), "cmd1cmd2cmd3cmd4cmd5");
}

TEST(TestBulkCollector, EndDataDynamicBulk)
{
  hw7::Bulk bulk;
  auto process = [&bulk](const hw7::BulkTime&, const hw7::Bulk& b){ bulk = b; };
  BulkCollector collector{3, process};

  collector.add("{");
  collector.add("cmd1");
  collector.add("cmd2");
  collector.add("cmd3");
  collector.add("cmd4");
  collector.add("cmd5");
  collector.endData();

  EXPECT_FALSE(bulk.empty());
  EXPECT_EQ(toString(bulk), "cmd1cmd2cmd3cmd4cmd5");
}

TEST(TestBulkCollector, CommonBulkAfterDynamicBulk)
{
  std::vector<hw7::Bulk> bulks;
  auto process = [&bulks](const hw7::BulkTime&, const hw7::Bulk& b){ bulks.emplace_back(b); };
  BulkCollector collector{3, process};

  collector.add("{");
  collector.add("cmd1");
  collector.add("cmd2");
  collector.add("cmd3");
  collector.add("cmd4");
  collector.add("cmd5");
  collector.add("}");
  collector.add("cmd6");
  collector.add("cmd7");
  collector.add("cmd8");


  EXPECT_EQ(bulks.size(), 2);
  EXPECT_EQ(toString(bulks[0]), "cmd1cmd2cmd3cmd4cmd5");
  EXPECT_EQ(toString(bulks[1]), "cmd6cmd7cmd8");
}
