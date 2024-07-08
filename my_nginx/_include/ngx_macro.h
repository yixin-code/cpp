#ifndef __NGX_MACRO_H__
#define __NGX_MACRO_H__

#include <string.h>

#define NGX_MAX_ERR_INFO_LEN 2048 // 错误信息最大长度
#define NGX_MEMCPY_RET_CUR(dest, src, len) ((u_char*)memcpy(dest, src, len) + (len)) // 内存拷贝够返回指针到拷贝的下一位置

#define NGX_MAX_INT64_LEN (sizeof("-9223372036854775808") - 1) // 64位整数最长字符, -1除去\0
#define NGX_MAX_UINT32 (u_int32_t)0xffffffff // 32位无符号最大整数

#define NGX_LOG_NAME_PATH "./logs/ngx.log" // 日志路径名
// 日志级别
#define NGX_LOG_STDERR      0 //控制台错误【stderr】：最高级别日志，日志的内容不再写入log参数指定的文件，而是会直接将日志输出到标准错误设备比如控制台屏幕
#define NGX_LOG_EMERG       1 //紧急 【emerg】
#define NGX_LOG_ALERT       2 //警戒 【alert】
#define NGX_LOG_CRIT        3 //严重 【crit】
#define NGX_LOG_ERR         4 //错误 【error】：属于常用级别
#define NGX_LOG_WARN        5 //警告 【warn】：属于常用级别
#define NGX_LOG_NOTICE      6 //注意 【notice】
#define NGX_LOG_INFO        7 //信息 【info】
#define NGX_LOG_DEBUG       8 //调试 【debug】：最低级别

// 进程标志
#define NGX_PROCESS_FLAG_MASTER  0 // master 管理进程
#define NGX_PROCESS_FLAG_WORKER  1 // worker 工作进程

#endif