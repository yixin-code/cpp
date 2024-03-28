#include "ngx_conf.h"
#include <iostream>
#include <string.h>
#include "ngx_func.h"
#include "ngx_global.h"

CConfig *CConfig::m_s_p_instance = nullptr;

CConfig::~CConfig() {
    for (std::vector<ConfigItem*>::iterator it = this->m_config_item_list.begin(); it != this->m_config_item_list.end(); ++it) {
        delete *it;
        *it = nullptr;
    }
    this->m_config_item_list.clear();
}

bool CConfig::load_config(const char *p_path_name) {
    FILE *fp = fopen(p_path_name, "r");
    if (fp == nullptr) {
        perror("13, fopen error");
        return false;
    }

    char buf[1024] = {0};
    while (fgets(buf, sizeof(buf), fp)) {
        if (*buf == 0) { // 空文件 不做处理
            fclose(fp);
            return false;
        }

        if (isspace(*buf) || *buf == '#' || *buf == ';' || *buf == '[') { // 注释 不符合规则的不进行处理
            continue;
        }

        char *temp_p = strchr(buf, '='); // buf中有=时说明符合规格
        if (temp_p != nullptr) {
            ConfigItem *p_conf_item = new ConfigItem();
            strncpy(p_conf_item->m_item_name, buf, temp_p - buf); // 等号前半部分
            strcpy(p_conf_item->m_item_content, temp_p + 1); // 等号后半部分

            // 处理空白字符
            left_space(p_conf_item->m_item_content);
            left_space(p_conf_item->m_item_name);
            right_space(p_conf_item->m_item_content);
            right_space(p_conf_item->m_item_name);

            this->m_config_item_list.push_back(p_conf_item);
        }
    }

    fclose(fp);
    return true;
}

// 得到配置文件中的字符串 配置文件名 得到配置文件内容
const char* CConfig::get_string(const char* p_item_name) {
    for (std::vector<ConfigItem*>::iterator it = this->m_config_item_list.begin(); it != this->m_config_item_list.end(); ++it) {
        if (strcasecmp(p_item_name, (*it)->m_item_name) == 0) {
            return (*it)->m_item_content;
        }
    }
    return nullptr;
}

// 得到配置文件中的数字
int CConfig::get_int_default(const char* p_item_name, const int def) {
    for (std::vector<ConfigItem*>::iterator it = this->m_config_item_list.begin(); it != this->m_config_item_list.end(); ++it) {
        if (strcasecmp(p_item_name, (*it)->m_item_name) == 0) {
            return atoi((*it)->m_item_content);
        }
    }
    return def;
}