#include <iostream>
#include "rpcapplication.h"
#include "user.pb.h"
#include "rpcchannel.h"


int main(int argc, char **argv) {
    RpcApplication::Init(argc, argv);

    fixbug::UserServiceRpc_Stub stub(new RpcChannel());

    // prepare rpc request payload.
    // method `login`.
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");

    fixbug::LoginResponse response;

    RpcController controller;
    stub.Login(&controller, &request, &response, nullptr);

    if (controller.Failed()) {
        std::cout << controller.ErrorText() << std::endl;
    } else {
        if (0 == response.result().errcode()) {
            std::cout << "rpc login response success:" << response.sucess() << std::endl;
        } else {
            std::cout << "rpc login response error: " << response.result().errmsg() << std::endl;
        }
    }

    // method `register`.
    fixbug::RegisterRequest req;
    req.set_id(2000);
    req.set_name("mprpc");
    req.set_pwd("666666");

    fixbug::RegisterResponse rsp;

    stub.Register(&controller, &req, &rsp, nullptr); 

    if (controller.Failed()) {
        std::cout << controller.ErrorText() << std::endl;
    } else {
        if (0 == rsp.result().errcode()) {
            std::cout << "rpc register response success:" << rsp.sucess() << std::endl;
        } else {
            std::cout << "rpc register response error: " << rsp.result().errmsg() << std::endl;
        }
    }

    return 0;
}