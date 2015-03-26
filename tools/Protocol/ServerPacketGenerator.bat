@echo off
set path_proto_cpp=%cd%/../Proto_cpp
set out_dir=%cd%/../../Server/GameServer/GameServer/protocol/message/
set path_protocol=.

for %%i in (%path_protocol%/SgMsg.proto %path_protocol%/SgMsgId.proto) do (
%path_proto_cpp%/protoc --proto_path=%path_protocol% %%i --cpp_out=%out_dir%
)