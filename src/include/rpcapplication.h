#pragma once

#include "rpcconfig.h"
#include "rpcchannel.h"
#include "rpccontroller.h"


class RpcApplication {
    public:
        static void Init(int argc, char **argv);
        static RpcApplication& GetInstance();
        static RpcConfig& GetConfig();
    private:
        static RpcConfig m_config;

        RpcApplication(){}
        RpcApplication(const RpcApplication&) = delete;
        RpcApplication(RpcApplication&&) = delete;
};