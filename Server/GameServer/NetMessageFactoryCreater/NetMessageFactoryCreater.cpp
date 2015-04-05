//  [3/30/2015 wuliangyu]

#ifndef RegisterNetMessage_h__
#define RegisterNetMessage_h__

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "NetMessageInfo.h"

using namespace std;

int main(int argc, char** args)
{
	if (argc < 4)
	{
		cout << "usage :" << args[0] << " neMmsgIdDefineFile"<< "cppNetMessageFactoryFile"<< "csharpNetMessageFactoryFile" << endl;
		system("pause");
		return 0;
	}

	string cppOutFileName = args[2];
	string csharpOutFileName = args[3];

	ifstream iFile(args[1]);
	vector<NetMessageItem*> pNetMessageList;

	string str;
	NetMessageItem* pMessageItem;
	while (getline(iFile, str))
	{
		pMessageItem = NetMessageItem::parserString2NetMessageItem(str);

		if (pMessageItem != NULL)
		{
			cout << "messageItem :" << pMessageItem->messageType << " " << pMessageItem->messageName << endl;
			pNetMessageList.push_back(pMessageItem);
		}
	}

	NetMessageFactoryCreater::createCppNetMessageFactory(cppOutFileName, pNetMessageList);
	NetMessageFactoryCreater::createCSharpNetMessageFactory(csharpOutFileName, pNetMessageList);

	vector<NetMessageItem*>::iterator it;
	for (it = pNetMessageList.begin(); it != pNetMessageList.end(); it++)
	{
		delete *it;
	}

	return 0;
}

#endif // RegisterNetMessage_h__