/*
 * VersionEnquiryManagerTest.c
 * Created on: Aug 22, 2021 21:45
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#include <zephyr.h>
#include <ztest.h>

#include "VersionEnquiryManager/VersionEnquiryManager.h"

static VersionType test_version_type;
static VersionInfo test_version_info;
static bool enter_version_reply_func = false;

void TestVersionReplyFunc(const VersionType version_type,
                          const VersionInfo version_info) {
  zassert_equal(version_type, test_version_type, "Version type not equal");
  zassert_equal(version_info.version[0], test_version_info.version[0],
                "Version info[0] not equal");
  zassert_equal(version_info.version[1], test_version_info.version[1],
                "Version info[1] not equal");
  zassert_equal(version_info.version[2], test_version_info.version[2],
                "Version info[2] not equal");
  enter_version_reply_func = true;
}

static void test_version_enquiry_manager_init(void) {
  VersionInfo version_info;
  zassert_false(SetVersionInfo(BOARD_TYPE, version_info),
                "Unexpected true for setting version");
  AskReplyFromVersionEnquiryManager(BOARD_TYPE);
  zassert_false(enter_version_reply_func,
                "Unexpected true for entering version reply func");
  zassert_true(InitVersionEnquiryManager(TestVersionReplyFunc),
               "Unexpected false for normal initialization");
  zassert_false(InitVersionEnquiryManager(TestVersionReplyFunc),
                "Unexpected true for initialization more than once");
}

static void test_version_enquiry_manager_singleton_invalid_set_version(void) {
  VersionInfo version_info;
  zassert_false(SetVersionInfo((VersionType)6, version_info),
                "Unexpected true for setting invalid version");
}

static void test_version_enquiry_manager_set_version(void) {
  test_version_type = FIRMWARE_TYPE;
  test_version_info.valueof.major = 1;
  test_version_info.valueof.minor = 2;
  test_version_info.valueof.patch = 3;
  zassert_true(SetVersionInfo(test_version_type, test_version_info),
               "Unexpected false for setting FIRMWARE_TYPE");

  test_version_type = BOARD_TYPE;
  zassert_true(SetVersionInfo(test_version_type, test_version_info),
               "Unexpected false for setting BOARD_TYPE");

  test_version_type = ROBOT_TYPE;
  zassert_true(SetVersionInfo(test_version_type, test_version_info),
               "Unexpected false for setting ROBOT_TYPE");
}

static void test_version_enquiry_manager_ask_reply(void) {
  test_version_type = FIRMWARE_TYPE;
  test_version_info.valueof.major = 1;
  test_version_info.valueof.minor = 2;
  test_version_info.valueof.patch = 3;
  zassert_true(SetVersionInfo(test_version_type, test_version_info),
               "Unexpected false for setting version");
  AskReplyFromVersionEnquiryManager(test_version_type);
  zassert_true(enter_version_reply_func, "Failed to enter version_reply_func");
  enter_version_reply_func = false;

  test_version_type = BOARD_TYPE;
  test_version_info.valueof.major = 4;
  test_version_info.valueof.minor = 5;
  test_version_info.valueof.patch = 6;
  zassert_true(SetVersionInfo(test_version_type, test_version_info),
               "Unexpected false for setting version");
  AskReplyFromVersionEnquiryManager(test_version_type);
  zassert_true(enter_version_reply_func, "Failed to enter version_reply_func");
  enter_version_reply_func = false;

  test_version_type = ROBOT_TYPE;
  test_version_info.valueof.major = 7;
  test_version_info.valueof.minor = 8;
  test_version_info.valueof.patch = 9;
  zassert_true(SetVersionInfo(test_version_type, test_version_info),
               "Unexpected false for setting version");
  AskReplyFromVersionEnquiryManager(test_version_type);
  zassert_true(enter_version_reply_func, "Failed to enter version_reply_func");
  enter_version_reply_func = false;
}

void test_main(void) {
  ztest_test_suite(
      test_version_enquiry_manager,
      ztest_unit_test(test_version_enquiry_manager_init),
      ztest_unit_test(
          test_version_enquiry_manager_singleton_invalid_set_version),
      ztest_unit_test(test_version_enquiry_manager_set_version),
      ztest_unit_test(test_version_enquiry_manager_ask_reply));
  ztest_run_test_suite(test_version_enquiry_manager);
}