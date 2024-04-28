#include "rpcapplication.h"
#include <iostream>
#include <unistd.h>
#include <string>

// Singleton Pattern.
RpcConfig RpcApplication::m_config;


void ShowArgsHelp() {
    std::cout << "format: command -i <configfile>" << std::endl;
}

void RpcApplication::Init(int argc, char **argv) {
    if (argc < 2) {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;
    while((c = getopt(argc, argv, "i:")) != -1) {
        switch (c) {
            case 'i':
                config_file = optarg;
                break;
            case '?':
                ShowArgsHelp();
                exit(EXIT_FAILURE);
            case ':':
                ShowArgsHelp();
                exit(EXIT_FAILURE);
            default:
                break;
        }
    }

    m_config.LoadConfigFile(config_file.c_str());

}

RpcApplication& RpcApplication::GetInstance() {
    static RpcApplication app;
    return app;
}

RpcConfig& RpcApplication::GetConfig() {
    return m_config;
}