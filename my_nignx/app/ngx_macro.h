#ifndef __NGX_MACRO_H__
#define __NGX_MACRO_H__

#define MAX_ERR_INFO_LEN 2048 // 错误信息最大长度
#define NGX_MEMCPY_RET_CUR(dest, src, len) ((u_char*)memcpy(dest, src, len) + (len)) // 内存拷贝够返回指针到拷贝的下一位置

#define MAX_INT64_LEN (sizeof("-9223372036854775808") - 1) // 64位整数最长字符, -1除去\0
#define MAX_UINT32 (u_int32_t)0xffffffff // 32位无符号最大整数

#endif