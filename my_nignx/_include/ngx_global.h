#ifndef __NGX_GLOBAL_H__
#define __NGX_GLOBAL_H__

#include <string.h>
#include <iostream>

struct ConfigItem {
    char m_item_name[40]; // 配置名
    char m_item_content[400]; // 配置内容

    ConfigItem() {
        memset(this->m_item_content, 0, sizeof(this->m_item_content));
        memset(this->m_item_name, 0, sizeof(this->m_item_name));
    }
};

#endif