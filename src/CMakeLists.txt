#aux_source_directory(. SRC_LIST)
set(SRC_LIST 
    rpcapplication.cpp
    rpcconfig.cpp
    rpcheader.pb.cpp
    rpcprovider.cpp
    rpcchannel.cpp
    rpccontroller.cpp
    logger.cpp
    zookeeperutil.cpp)
add_library(toy_rpc ${SRC_LIST})
target_link_libraries(toy_rpc muduo_net muduo_base pthread zookeeper_mt)