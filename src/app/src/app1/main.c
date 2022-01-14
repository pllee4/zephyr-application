/* 
 * main.c
 * Created on: Jan 13, 2022 21:18
 * Description: 
 * 
 * Copyright (c) 2022 Pin Loon Lee (pllee4)
 */ 

#include <zephyr.h>

void main(void) {
  while (1) {
    printk("Running app1 \n");
    k_sleep(K_MSEC(1000));
  }
}
