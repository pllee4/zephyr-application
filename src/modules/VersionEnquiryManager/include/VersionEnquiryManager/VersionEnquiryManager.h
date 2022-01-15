/*
 * VersionEnquiryManager.h
 * Created on: Aug 22, 2021 21:21
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#ifndef VERSIONENQUIRYMANAGER_H
#define VERSIONENQUIRYMANAGER_H

// Description:
// Singleton pattern, only once instance, but could be extended

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef enum {
  FIRMWARE_TYPE = 0,
  BOARD_TYPE = 1,
  ROBOT_TYPE = 2,
} VersionType;

// No padding in the struct
#pragma pack(push, 1)

typedef union {
  struct {
    uint8_t major;
    uint8_t minor;
    uint8_t patch;
  } valueof;

  uint8_t version[3];
} VersionInfo;

#pragma pack(pop)

typedef void (*VersionReplyFunc)(const VersionType version_type,
                                 const VersionInfo version_info);

bool InitVersionEnquiryManager(VersionReplyFunc version_reply_func);
bool SetVersionInfo(VersionType version_type, VersionInfo version_info);
void AskReplyFromVersionEnquiryManager(VersionType version_type);

#ifdef __cplusplus
}
#endif

#endif /* VERSIONENQUIRYMANAGER_H */
