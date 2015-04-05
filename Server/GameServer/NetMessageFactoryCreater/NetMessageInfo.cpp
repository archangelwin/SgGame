#include "NetMessageInfo.h"

NetMessageItem* NetMessageItem::parserString2NetMessageItem(string& str)
{
	StringUtils::trim(str, '\t');
	StringUtils::trim(str, '\n');
	StringUtils::trim(str, ' ');

	NetMessageItem* pNetMsgItem = NULL;
	string::size_type posCS = str.find_first_of("CS_");
	string::size_type posSC = str.find_first_of("SC_");
	string::size_type posEqual = str.find_first_of('=');

	if (posEqual != string::npos)
	{
		if ((posCS != string::npos) && (posCS + 3 < posEqual))
		{
			pNetMsgItem = new NetMessageItem();
			pNetMsgItem->messageType = MessageType::Client2Server;
			pNetMsgItem->messageId = str.substr(posCS, posEqual - posCS);
			pNetMsgItem->messageName = str.substr(posCS + 3, posEqual - posCS - 3);
		}
		else if ((posSC != string::npos) && (posSC + 3 < posEqual))
		{
			pNetMsgItem = new NetMessageItem();
			pNetMsgItem->messageType = MessageType::Server2Client;
			pNetMsgItem->messageId = str.substr(posSC, posEqual - posCS);
			pNetMsgItem->messageName = str.substr(posSC + 3, posEqual - posSC - 3);
		}
	}

	return pNetMsgItem;
}

void NetMessageFactoryCreater::createCppNetMessageFactory(string fileName, vector<NetMessageItem*> pNetMessgeList)
{
	ofstream oFile(fileName);
	oFile << "#include \"NetMessageFactory.h\"" << endl << endl;
	oFile << "shared_ptr<google::protobuf::Message> NetMessageFactory::createNetMessage(NetMsgId messageId)" << endl;
	oFile << "{" << endl;
	oFile << "\tshared_ptr<google::protobuf::Message> netMessage(NULL);" << endl;
	oFile << "\tswitch (messageId)" << endl;
	oFile << "\t{" << endl;

	vector<NetMessageItem*>::iterator it;
	for (it = pNetMessgeList.begin(); it != pNetMessgeList.end(); it++)
	{
		oFile << "\t\tcase " << MessageId(it)<< ":" << endl;
		oFile << "\t\t\tnetMessage = shared_ptr<" << ((*it)->messageName).c_str() << "\>(new " << MessageName(it)<<"()); " << endl;
		oFile << "\t\t\tbreak;" << endl;
	}

	oFile << "\t\tdefault:" << endl;
	oFile << "\t\t\tbreak;" << endl;
	oFile << "\t};" << endl;
	oFile << endl;
	oFile << "\treturn netMessage;" << endl;
	oFile << "}"<<endl;

	oFile.close();

}

void NetMessageFactoryCreater::createCSharpNetMessageFactory(string fileName, vector<NetMessageItem*> pNetMessgeList)
{
	ofstream oFile(fileName);
	oFile << "using SgMsg;" << endl;
	oFile << "using SgMsgId;" << endl;
	oFile << "using ProtoBuf;" << endl;
	oFile << endl;

	vector<NetMessageItem*>::iterator it;
	for (it = pNetMessgeList.begin(); it != pNetMessgeList.end(); it++)
	{
		oFile << "class " << MessageName(it) << "NetMessage : NetMessage" << endl;
		oFile << "{" << endl;
		oFile << "\tpublic " << MessageName(it) << "NetMessage()" << endl;
		oFile << "\t{" << endl;
		oFile << "\t\t_msgId = NetMsgId." << MessageId(it) << ";" << endl;
		oFile << "\t\t_message = new " << MessageName(it) << "(); " << endl;
		oFile << "\t}" << endl;
		oFile << endl;
		oFile << "\tpublic " << MessageName(it) << " getContent()" << endl;
		oFile << "\t{" <<endl;
		oFile << "\t\treturn _message as " << MessageName(it) << ";" << endl;
		oFile << "\t}" << endl;
		oFile << "};" << endl;
		oFile << endl;
	}

	oFile << "public class NetMessageFactory" << endl;
	oFile << "{" << endl;
	oFile << "\tstatic public NetMessage createNetMessagById(NetMsgId messageId)" << endl;
	oFile << "\t{" << endl;
	oFile << "\t\tNetMessage netMsg = null;" << endl;
	oFile << "\t\tswitch(messageId)" << endl;
	oFile << "\t\t{" << endl;

	for (it = pNetMessgeList.begin(); it != pNetMessgeList.end(); it++)
	{
		oFile << "\t\t\tcase NetMsgId."<<MessageId(it)<<":" << endl;
		oFile << "\t\t\t\tnetMsg = new "<<MessageName(it)<<"NetMessage();" << endl;
		oFile << "\t\t\t\tbreak;" << endl;
	}

	oFile << "\t\t\tdefault:" << endl;
	oFile << "\t\t\t\tbreak;" << endl;
	oFile << "\t\t}" << endl;
	oFile << "\t\treturn netMsg;" << endl;
	oFile << "\t}" << endl;
	oFile << "}" << endl;
	oFile.close();
}