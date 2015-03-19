@echo off
set cs_factory_class=cs_package_factory
set name_space_protol=gateproto
set name_space_packet_id=opcodes
set class_packet_id=Opcodes

echo using System.Collections;
echo using System.Collections.Generic;
echo using System.IO;
echo using System;
echo using ProtoBuf;
echo using gateproto;
echo using opcodes;
echo.
echo public class %cs_factory_class%
echo {
echo		private Dictionary^<%class_packet_id%, PacketBuilder^> _packetBuilder;
echo.
echo		public %cs_factory_class%()
echo		{
echo			_packetBuilder = new Dictionary^<%class_packet_id%, PacketBuilder^>();
echo. 

for /f "delims=- tokens=2" %%a in ('findstr /n .* %in_put_file%') do (
echo			_packetBuilder[%class_packet_id%.%%a] = new GCLoginCSRTBuilder^(^)^;
)
echo		}

echo 	public Packet decodePacket^(UInt16 pktID^, MemoryStream stream^)
echo 	{
echo 		if^(^!_packetBuilder.ContainsKey^(^(%class_packet_id%^)pktID^)^)
echo 		{
echo 			return null;
echo 		}
echo.
echo 		PacketBuilder pktBuilder = _packetBuilder^[^(%class_packet_id%^)pktID^];
echo 		return pktBuilder.createPacket^(stream^);
echo 	}
echo }
echo.
echo public class Packet
echo {
echo 	public %class_packet_id% packageID;
echo 	public IExtensible _content;
echo.
echo 	public IExtensible getContent()
echo 	{
echo 		return _content;
echo 	}
echo }
echo.
echo public class PacketBuilder
echo {
echo 	public %class_packet_id% packageID;
echo.
echo 	public virtual Packet createPacket(Stream inputStream)
echo 	{
echo 		return null;
echo 	}
echo }
for /f "delims=- tokens=2,3,4,5,6" %%a in ('findstr /n .* %in_put_file%') do (
echo.
echo public class %%d:Packet
echo {
echo 	public %%d^(^)
echo 	{
echo 		packageID = %class_packet_id%.%%a;
if %%e==0 (
echo 		_content  = new %%b^(^)^;
)
echo 	}
if %%e==1 (
echo 	public void decodeStream^(Stream inputStream^)
echo 	{
echo 		_content = Serializer.Deserialize^<%%b^>^(inputStream^);
echo 	}
)
echo.
echo 	public %%b getData^(^)
echo 	{
echo 		return ^(%%b^)_content;
echo 	}
echo }

if %%e==1 (
echo.
echo public class %%c:PacketBuilder
echo {
echo 	public %%c^(^)
echo 	{
echo 		packageID = %class_packet_id%.%%a;
echo 	}
echo.
echo 	public override Packet createPacket ^(Stream inputStream^)
echo 	{
echo 		%%d pkt = new %%d^(^);
echo 		pkt.decodeStream^(inputStream^);
echo 		return pkt;
echo 	}
echo }
)
)