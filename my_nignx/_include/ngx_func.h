#ifndef __NGX_FUNC_H__
#define __NGX_FUNC_H__
#include <iostream>

// 清除字符串左边空格
void left_space(char *str);
// 清除字符串右边空格
void right_space(char *str);

// 保存全局变量
void save_environ();
// 设置进程标题
void set_process_title(const char* title_name);

// 紧急信息直接显示到屏幕
void ngx_log_stderr(int error_num, const char* format, ...);
// 格式化输出
u_char* format_printf(u_char* p_cur, u_char* p_end, const char* format, va_list ap);
// 显示错误代码和信息
u_char* display_errno_info(u_char* p_cur, u_char* p_end, int err_num);

#endif