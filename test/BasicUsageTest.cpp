
#include "typegrind/logger/demo_cout.h"
#include "gtest/gtest.h"

class LoggerDemoCoutTest : public ::testing::Test {
  protected:

    virtual void SetUp() {
      // make sure the logger is initialized before the first capture
      typegrind::logger::demo_cout::get();
    }
};

TEST_F(LoggerDemoCoutTest, LoggingNew)
{
  int* ip = nullptr;
  testing::internal::CaptureStdout();
  EXPECT_EQ(TYPEGRIND_LOG_NEW("typeName", "file:13", 137, ip), ip);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "allocation at:file:13 type:typeName type_size:137 total_size:0 addr:0\n");
}

TEST_F(LoggerDemoCoutTest, LoggingDelete)
{
  int* ip = nullptr;
  testing::internal::CaptureStdout();
  EXPECT_EQ(TYPEGRIND_LOG_DELETE("typeName", "canonicalName", "file:13", ip), ip);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "free at:file:13 type:typeName canonical:canonicalName addr:0\n");
}
