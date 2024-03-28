#include <iostream>
#include "ngx_conf.h"

int main() {
    CConfig *p_config = CConfig::get_instance();
    if (p_config->load_config("./nginx.conf") == false) {
        perror("7, load error");
        exit(1);
    }

    if (const char *p_temp = p_config->get_string("dbinfo")) {
        std::cout << p_temp << '\n';
    }

    if (int temp = p_config->get_int_default("listenport", 1111)) {
        std::cout << temp << '\n';
    }

    // for (auto it = p->m_config_item_list.begin(); it != p->m_config_item_list.end(); ++it) {
    //     std::cout << (*it)->m_item_name << " " << (*it)->m_item_content << "\n";
    // }

    return 0;
}