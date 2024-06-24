#include "ngx_func.h"
#include "ngx_global.h"
#include <unistd.h>
#include <string.h>

// 保存环境变量 环境变量在命令行参数后，为避免覆盖环境变量
    // 环境变量是一个二级指针 char **environ
void save_environ_arg() {
    for (int i = 0; g_p_argv[i] != nullptr; ++i) { // 命令行参数总长度
        g_argv_len += strlen(g_p_argv[i]) + 1;
    }

    for (int i = 0; environ[i]; ++i) { // 拿到环境变量长度
        g_environ_len += strlen(environ[i]) + 1; // 结尾的'\0'需要加上
    }

    g_p_environ = new char[g_environ_len]{0};

    char *p_temp = g_p_environ;

    for (int i = 0; environ[i]; ++i) {
        strcpy(p_temp, environ[i]);
        int temp_len = strlen(environ[i]) + 1;
        environ[i] = p_temp; // 改变原环境变量指向
        p_temp += temp_len; // 指针移动到下一个环境变量位置
    }

    return;
}

// 设置进程标题
void set_process_title(const char* title_name) {
    int temp_total_len = g_argv_len + g_environ_len; // 命令行参数和环境变量总长度
    if (strlen(title_name) >= temp_total_len) {
        perror("title name set fail");
        exit(1);
    }

    g_p_argv[1] = nullptr; // 便于使用 argv[] == nullptr 作判断

    char *temp_p = g_p_argv[0];
    strcpy(temp_p, title_name);
    temp_p += strlen(title_name);

    int temp_len = temp_total_len - strlen(title_name);
    memset(temp_p, 0, temp_len);
}