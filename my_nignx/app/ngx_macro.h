#ifndef __NGX_MACRO_H__
#define __NGX_MACRO_H__

#define MAX_ERR_INFO_LEN 2048 // 错误信息最大长度
#define NGX_MEMCPY_RET_CUR(dest, src, len) ((u_char*)memcpy(dest, src, len) + (len)) // 内存拷贝够返回指针到拷贝的下一位置

#endif