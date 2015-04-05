using UnityEngine;
using System.Collections.Generic;
using System;

using ProtoBuf.Meta;
using ProtoBuf;
using SgMsg;
using SgMsgId;

public interface INetMessageHandle
{
	void handleNetMessage(NetMessage netMsg);
}

public class NetManager : MonoBehaviour 
{
	public string ip = "127.0.0.1";
	public int port = 3344;

	[HideInInspector]
	public INetMessageHandle messageHandle;
	private NetMessageCodec _msgFactory = NetMessageCodec.getInstance();
	private NetWork _netWork;

	static private NetManager _instance = null;
	static public NetManager getInstance()
	{
		return _instance;
	}

	void Awake()
	{
		_instance = this;
		DontDestroyOnLoad(gameObject);
	}

	public void start()
	{
		_netWork = new NetWork(ip, port);
		_netWork.funcNetWorkStatChgCallBack = onNetWorkStatChg;
		_netWork.funcDecodeData = _msgFactory.decodeData;
		_netWork.init();
	}

	void Update()
	{
		if(messageHandle == null)
		{
			return;
		}

		NetMessage netMsg = _msgFactory.fetchNetMessage();
		if(netMsg == null)
		{
			return;
		}

		messageHandle.handleNetMessage(netMsg);
	}

	public void sendNetMessage(NetMsgId msgId, IExtensible message) 
	{
        PbTestNetMessage pbMessage = new PbTestNetMessage();
        pbMessage.getContent().id = 12343;
        pbMessage.getContent().name = "PbTestNetMessage";
        sendNetMessage(pbMessage);
	}

	public void sendNetMessage(NetMessage msg)
	{
		if((msg == null) || (msg.content == null))
		{
			return;
		}

		if((_msgFactory==null) || (_netWork == null))
		{
			return;
		}

		int dataSize;
		Byte[] buff = _msgFactory.encodeNetMessage(msg, out dataSize);
		if (buff != null)
		{
			_netWork.send(buff, dataSize);
		}
	}

	void OnDestory()
	{
		if(_netWork != null)
		{
			_netWork.uninit();
		}
	}

	private void onNetWorkStatChg(NetWorkStat stat)
	{
		Debug.Log("onNetWorkStatChg: "+stat);
	}
}
