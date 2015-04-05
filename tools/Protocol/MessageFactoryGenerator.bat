@echo off
set cppOutFile=..\\..\\Server\\GameServer\\GameServer\\protocol\\NetMessageFactory.cpp
set csharpOutFile=..\\..\\Client\\SgUnity\\Assets\\Code\\Protocol\\NetMessageFactory.cs
NetMessageFactoryCreater.exe SgMsgId.proto %cppOutFile% %csharpOutFile%