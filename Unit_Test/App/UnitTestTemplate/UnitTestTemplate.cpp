//*****************************************************************************************
//COPYRIGHT 2020: Valmont Industries, Inc
//                All rights reserved.
//                This software and/or material is the property of Valmont Industries Inc.
//                All use, disclosure, and/or reproduction not specifically authorized in
//                writing by Valmont Industries Inc is prohibited.
//*****************************************************************************************
#include "gtest/gtest.h"
#include "fff.h"

DEFINE_FFF_GLOBALS;

/// Test runner
class UnitTestTemplate : public ::testing::Test
{
   protected:
      virtual void SetUp()
      {
         // Insert initialization here
      }

      virtual void TearDown()
      {
         // Insert clean up here
      }
};

TEST_F(UnitTestTemplate, DescriptiveTestName)
{
   // TEMPLATE test
}
