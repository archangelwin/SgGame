@echo off
set path_proto_c#=%cd%/../Proto_c#
set out_dir=%cd%/../../Client/SgUnity/Assets/Code/Protocol/NetMessages
set path_protocol=.

for %%i in (%path_protocol%/SgMsg.proto %path_protocol%/SgMsgId.proto) do (
%path_proto_c#%/protogen -i:%%i -o:%out_dir%/%%~ni.cs
)