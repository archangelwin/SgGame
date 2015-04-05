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
            case NetMsgId.CS_UseItem:
                handleUseItemMessage(netMsg);
                break;
			default:
				Debug.Log("handle unknow message:" + netMsg.msgId);
				break;
		}
	}

	private void handelPbTestMessage(NetMessage netMsg)
	{
		Debug.Log("handelPbTestMessage");
        PbTestNetMessage pbTest = netMsg as PbTestNetMessage;
        Debug.Log("msgTest.id:" + pbTest.getContent().id + " msgTest.name:" + pbTest.getContent().name);
	}

    private void handleUseItemMessage(NetMessage netMsg)
    {
        UseItemNetMessage uItemMsg = netMsg as UseItemNetMessage;

        Debug.Log("uItemMsg.:" + uItemMsg.getContent().itemIndex.ToString()+ "" + uItemMsg.getContent().pktId.ToString()+ " "+ uItemMsg.getContent().useCommond.ToString());
    }
}
