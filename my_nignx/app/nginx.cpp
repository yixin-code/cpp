#include <iostream>
#include "ngx_conf.h"
#include "ngx_func.h"
#include "ngx_global.h"

char *g_p_environ = nullptr; // 环境变量
int g_environ_len = 0; // 环境变量字节数
char **g_p_argv = nullptr; // 命令行参数

int main(int argc, char *argv[]) {
    g_p_argv = argv;

    CConfig *p_config = CConfig::get_instance();
    if (p_config->load_config("./nginx.conf") == false) {
        perror("7, load error");
        exit(1);
    }

    save_environ();
    set_process_title("nginx: master process");

    if (g_p_environ != nullptr) {
        delete[] g_p_environ;
        g_p_environ = nullptr;
    }

    while(true);

    std::cout << "program exit\n";

    // if (const char *p_temp = p_config->get_string("dbinfo")) {
    //     std::cout << p_temp << '\n';
    // }

    // if (int temp = p_config->get_int_default("listenport", 1111)) {
    //     std::cout << temp << '\n';
    // }

    // for (auto it = p->m_config_item_list.begin(); it != p->m_config_item_list.end(); ++it) {
    //     std::cout << (*it)->m_item_name << " " << (*it)->m_item_content << "\n";
    // }

    return 0;
}