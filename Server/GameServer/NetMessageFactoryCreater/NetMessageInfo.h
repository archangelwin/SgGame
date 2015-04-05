/*!
 * \file NetMessageInfo.h
 *
 * \author wuly
 * \date ËÄÔÂ 2015
 *
 * 
 */


#ifndef __NETMESSAGEINFO_H__
#define __NETMESSAGEINFO_H__

#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtils.h"

#define MessageName(__x) ((*(__x))->messageName).c_str() 
#define MessageId(__x) ((*(__x))->messageId).c_str()

using namespace std;

enum MessageType
{
	Client2Server = 0,
	Server2Client,
};

class NetMessageItem
{
public:
	string messageId;
	string messageName;
	MessageType messageType;
	static NetMessageItem* parserString2NetMessageItem(string& str);
};

class NetMessageFactoryCreater
{
public:
	static void createCppNetMessageFactory(string fileName, vector<NetMessageItem*> netMessgeList);
	static void createCSharpNetMessageFactory(string fileName, vector<NetMessageItem*> netMessgeList);
};

#endif // __NetMessageInfo_H__
