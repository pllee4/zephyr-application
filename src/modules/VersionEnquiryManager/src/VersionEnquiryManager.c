/*
 * VersionEnquiryManager.c
 * Created on: Aug 22, 2021 21:21
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#include <stddef.h>
#include <stdio.h>

#include "VersionEnquiryManager/VersionEnquiryManager.h"

#define MAX_VERSION_TYPE 5

// private
typedef struct {
  VersionReplyFunc version_reply_func;
  VersionInfo version_info[MAX_VERSION_TYPE];
} VersionEnquiryManagerInstance;

// singleton
static VersionEnquiryManagerInstance instance;
static bool is_instance_initialized = false;

// private function
void DefaultVersionReplyFunc(const VersionType version_type,
                             const VersionInfo version_info) {
  printf("Default VersionReplyFunc, please init your singleton instance");
}

void ClearVersionInfo() {
  for (int i = 0; i < MAX_VERSION_TYPE; i++) {
    instance.version_info[i].version[0] = 0;
    instance.version_info[i].version[1] = 0;
    instance.version_info[i].version[2] = 0;
  }
}

// public function
bool InitVersionEnquiryManager(VersionReplyFunc version_reply_func) {
  if (!is_instance_initialized) {
    is_instance_initialized = true;
    if (version_reply_func != NULL)
      instance.version_reply_func = version_reply_func;
    else
      instance.version_reply_func = DefaultVersionReplyFunc;
    ClearVersionInfo();
    return true;
  } else {
    // only allow single_instance
    return false;
  }
}

bool SetVersionInfo(VersionType version_type, VersionInfo version_info) {
  if (version_type < MAX_VERSION_TYPE)
    instance.version_info[version_type] = version_info;
  else
    return false;
  return is_instance_initialized;
}

void AskReplyFromVersionEnquiryManager(VersionType version_type) {
  if (is_instance_initialized)
    instance.version_reply_func(version_type,
                                instance.version_info[version_type]);
}