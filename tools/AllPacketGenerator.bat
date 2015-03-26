@echo off
set path_protocol=./Protocol
cd %path_protocol%
call ServerPacketGenerator.bat 
call ClientPacketGenerator.bat
pause