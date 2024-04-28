#include "rpcconfig.h"

#include <iostream>
#include <string>


void RpcConfig::LoadConfigFile(const char *config_file) {
    FILE *pf = fopen(config_file, "r");
    if (pf == nullptr) {
        std::cout << config_file << " is note exist!" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        std::cout << "open configure file `" << config_file << "` with success!" << std::endl;
    }
 
    while(!feof(pf)) {
        char buf[512] = {0};
        fgets(buf, 512, pf);

        std::string read_buf(buf);
        Trim(read_buf);

        if (read_buf[0] == '#' || read_buf.empty()) {
            continue;
        }

        int idx = read_buf.find('=');
        // a legal config entry must have a `=` to split K/V.
        if (idx == -1) {
            continue;
        }

        std::string key;
        std::string value;
        key = read_buf.substr(0, idx);
        Trim(key);
        int endidx = read_buf.find('\n', idx);
        value = read_buf.substr(idx + 1, endidx - (idx + 1));
        Trim(value);

        m_configMap.insert({key, value});
    }

    fclose(pf);
}

std::string RpcConfig::Load(const std::string &key) {
    auto it = m_configMap.find(key);
    if (it == m_configMap.end()) {
        return "";
    }
    return it->second;
}

// `trim` space for a string.
void RpcConfig::Trim(std::string &src_buf) {
    // [0, idx) is ' '.
    int idx = src_buf.find_first_not_of(' ');
    if (idx != -1) {
        src_buf = src_buf.substr(idx, src_buf.size() - idx);
    }

    // [idx + 1, +∞) is ' '.
    idx = src_buf.find_last_not_of(' ');
    if (idx != -1) {
        src_buf = src_buf.substr(0, idx + 1);
    }
}