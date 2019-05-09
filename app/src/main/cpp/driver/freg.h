//
// Created by wanghaihui on 2019/3/31.
//
#ifndef _FAKE_REG_H
#define _FAKE_REG_H

#include <linux/cdev.h>
#include <linux/semaphore.h>

// 虚拟硬件设备freg在设备文件系统中的名称
#define FREG_DEVICE_NODE_NAME "freg"
#define FREG_DEVICE_FILE_NAME "freg"
#define FREG_DEVICE_PROC_NAME "freg"
#define FREG_DEVICE_CLASS_NAME "freg"

// 虚拟硬件设备freg
struct fake_reg_dev {
    // 虚拟寄存器
    int val;
    // 信号量--同步访问虚拟寄存器val
    struct semaphore sem;
    // 标准的Linux字符设备结构体变量
    struct cdev dev;
};
#endif
