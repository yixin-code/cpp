#ifndef __NGX_CONF_H__
#define __NGX_CONF_H__

#include <vector>
#include "ngx_global.h"

// 单利模式
class CConfig {
private:
    CConfig() = default;
    CConfig(const CConfig& cconfig) = default;
    CConfig& operator=(const CConfig& CConfig) = default;

private:
    static CConfig *m_s_p_instance;

public:
    ~CConfig();

public:
    class CConfigRelease { // 用于释放CConfig对象，m_s_pinstance是堆空间不会自动释放
    public:
        ~CConfigRelease() {
            if (m_s_p_instance != nullptr) {
                delete m_s_p_instance;
                m_s_p_instance = nullptr;
            }
        }
    };

public:
    static CConfig* get_instance() {
        if (m_s_p_instance == nullptr) { // 多线程中需要双重判断，第二次判断时加锁
            m_s_p_instance = new CConfig{};
            static CConfigRelease cr; // 程序结束会调用CConfigRelease的析构函数
        }

        return m_s_p_instance;
    }

public:
    // 加载配置文件
    bool load_config(const char* p_path_name);
    // 得到配置文件中的字符串
    const char* get_string(const char* p_item_name);
    // 得到配置文件中的数字 如未配置def为缺省值
    int get_int_default(const char* p_item_name, const int def);

public:
    std::vector<ConfigItem*> m_config_item_list; // 配置信息列表
};

#endif