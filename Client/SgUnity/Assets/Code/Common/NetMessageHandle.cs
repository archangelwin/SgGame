using UnityEngine;
using System.Collections.Generic;
using SgMsg;
using SgMsgId;

public class NetMessageHandle : INetMessageHandle 
{
	public void handleNetMessage(NetMessage netMsg)
	{
		switch (netMsg.msgId)
		{
			case NetMsgId.CS_PbTest:
				handelPbTestMessage(netMsg);
				break;
			default:
				Debug.Log("handle unknow message:" + netMsg.msgId);
				break;
		}
	}

	private void handelPbTestMessage(NetMessage netMsg)
	{
		Debug.Log("handelPbTestMessage");
		PbTest msgTest = netMsg.message as PbTest;
		Debug.Log("msgTest.id:" + msgTest.id + " msgTest.name:" + msgTest.name);
	}
}
