using UnityEngine;
using System.Collections.Generic;
using SgMsg;

public class GameMain : MonoBehaviour 
{
	public NetManager netManager;

	void Start()
	{
		DontDestroyOnLoad(gameObject);
		if(netManager != null)
		{
			netManager.messageHandle = new NetMessageHandle();
			netManager.start();
		}

	}

	void OnClick()
	{
		Debug.Log("OnClick");
		if(netManager != null)
		{
			PbTest testMsg = new PbTest();
			testMsg.id = 4567;
			testMsg.name = "xxasdtest";

			netManager.sendNetMessage(SgMsgId.NetMsgId.CS_PbTest, testMsg);
		}
	}
}
