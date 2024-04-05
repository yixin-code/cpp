#ifndef __NGX_FUNC_H__
#define __NGX_FUNC_H__

// 清除字符串左边空格
void left_space(char *str);
// 清除字符串右边空格
void right_space(char *str);

// 保存全局变量
void save_environ();
// 设置进程标题
void set_process_title(const char* title_name);

#endif