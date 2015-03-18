set out_dir=../Server/GameServer/GameServer/protocol/message
.\protoc ./SgMsg.Proto ./SgMsgId.proto --cpp_out=%out_dir%
pause