# set(SRC_LIST userservice.cc ../user.pb.cc)
set(SRC_LIST friendservice.cpp ../friend.pb.cc)

add_executable(provider ${SRC_LIST})
target_link_libraries(provider toy_rpc protobuf)