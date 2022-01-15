/*
 * main.c
 * Created on: Jan 13, 2022 21:18
 * Description:
 *
 * Copyright (c) 2022 Pin Loon Lee (pllee4)
 */

#include <zephyr.h>

#include "app_version.h"

void main(void) {
  printk("App version major: %d\n", APP_VERSION_MAJOR);
  printk("App version minor: %d\n", APP_VERSION_MINOR);
  printk("App version patch: %d\n", APP_VERSION_PATCH);
  printk("App version: %s\n", APP_VERSION_STR);
  while (1) {
    printk("Running app1 \n");
    k_sleep(K_MSEC(1000));
  }
}
