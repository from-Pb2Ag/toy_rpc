#pragma once

#include "rpcconfig.h"
#include "rpcchannel.h"
#include "rpccontroller.h"


class RpcApplication {
    public:
        // load configuration with path as hashmap.
        static void Init(int argc, char **argv);
        static RpcApplication& GetInstance();
        static RpcConfig& GetConfig();
    private:
        static RpcConfig m_config;
        // for Singleton Pattern, we make construction function unavailable,
        // and ban the copy/move assignment function/operator.

        RpcApplication(){}
        RpcApplication(const RpcApplication&) = delete;
        RpcApplication(RpcApplication&&) = delete;
};