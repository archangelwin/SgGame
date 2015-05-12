/*!
 * \file NetMessageFactory.h
 *
 * \author wuly
 * \date ËÄÔÂ 2015
 *
 * 
 */


#ifndef __NETMESSAGEFACTORY_H__
#define __NETMESSAGEFACTORY_H__

#include <SgLib.h>
#include "./message/SgMsgId.pb.h"
#include "./message/SgMsg.pb.h"
#include <google/protobuf/stubs/common.h>

US_NS_BOOST

class NetMessageFactory
{
public:
	static shared_ptr<google::protobuf::Message> createNetMessage(NetMsgId messageId);
};

#endif // __NetMessageFactory_H__
