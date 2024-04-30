#include <iostream>
#include "rpcapplication.h"
#include "friend.pb.h"


int main(int argc, char **argv) {
    RpcApplication::Init(argc, argv);

    fixbug::FiendServiceRpc_Stub stub(new RpcChannel());
    
    // prepare rpc request payload.
    fixbug::GetFriendsListRequest request;
    request.set_userid(1000);

    fixbug::GetFriendsListResponse response;

    // caller doesn't have callback function after receive response.
    RpcController controller;
    // the rpc method specified by `.proto` file is invoked with the function with same name.
    // in depth it calls `CallMethod` virtual function with `channel_` member.
    // we assign the `base class` pointer with a `derived class` instance address, and overwrite virtual function.
    stub.GetFriendsList(&controller, &request, &response, nullptr);

    if (controller.Failed()) {
        std::cout << controller.ErrorText() << std::endl;
    } else {
        if (0 == response.result().errcode()) {
            std::cout << "rpc GetFriendsList response success!" << std::endl;
            int size = response.friends_size();
            for (int i = 0; i < size; ++i) {
                std::cout << "index:" << (i + 1) << " name:" << response.friends(i) << std::endl;
            }
        } else {
            std::cout << "rpc GetFriendsList response error : " << response.result().errmsg() << std::endl;
        }
    }

    return 0;
}