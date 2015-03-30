//  [3/30/2015 wuliangyu]

#ifndef RegisterNetMessage_h__
#define RegisterNetMessage_h__

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MESSAGE_ID_FILE "SgMsgId.proto"

enum MessageType
{
	Client2Server=0,
	Server2Client,
};

class NetMessageItem
{
public:
	string messageName;
	MessageType messageType;
};

void trim(string& str, char chr)
{
	string::size_type pos = str.find_first_of(chr);
	while (pos != string::npos)
	{
		str.erase(pos, 1);
		pos = str.find_first_of(chr);
	}
}

NetMessageItem* parserString2NetMessageItem(string& str)
{
	trim(str, '\t');
	trim(str, '\n');
	trim(str, ' ');

	NetMessageItem* pNetMsgItem = NULL;
	string::size_type posCS = str.find_first_of("CS_");
	string::size_type posSC = str.find_first_of("SC_");
	string::size_type posEqual = str.find_first_of('=');

	if (posEqual != string::npos)
	{
		if ((posCS != string::npos) && (posCS+3 < posEqual))
		{
			pNetMsgItem = new NetMessageItem();
			pNetMsgItem->messageType = MessageType::Client2Server;
			pNetMsgItem->messageName = str.substr(posCS + 3, posEqual - posCS-3);
		}
		else if ((posSC != string::npos) && (posSC+3 < posEqual))
		{
			pNetMsgItem = new NetMessageItem();
			pNetMsgItem->messageType = MessageType::Server2Client;
			pNetMsgItem->messageName = str.substr(posSC + 3, posEqual - posSC-3);
		}
	}

	return pNetMsgItem;
}

int main(int argc, char** args)
{
	//if (argc < 2)
	//{
	//	cout << "usage :" << args[0] << " msgIdDefineFile" << endl;
	//	return 0;
	//}

	ifstream iFile("SgMsgId.proto");

	string str;
	NetMessageItem* messageItem;
	while (getline(iFile, str))
	{
		messageItem = parserString2NetMessageItem(str);

		if (messageItem != NULL)
		{
			cout << "messageItem :" << messageItem->messageType <<" "<< messageItem->messageName << endl;
		}
	}

	return 0;
}

#endif // RegisterNetMessage_h__