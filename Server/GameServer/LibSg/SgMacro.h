//  [3/5/2015 wuliangyu]

#ifndef SGMacro_h__
#define SGMacro_h__

#define NS_BEGIN_SG	namespace sg{
#define NS_END_SG	}
#define US_NS_SG	using namespace sg;
#define US_NS_STD	using namespace std;
#define US_NS_BOOST	using namespace boost;

#define ReturnVoidIfNull(__x) if((__x) == NULL) { return; }
#define ReturnFalseIfNull(__x) if((__x) == NULL) { return false; }

#define ASIO_TCP_SOCKET boost::asio::ip::tcp::socket

#define SgUInt8 boost::uint8_t
#define SgUInt16 boost::uint16_t
#define SgInt16 boost::int16_t
#define SgInt32 boost::int32_t
#define SgUInt32 boost::uint32_t

#define SgScopedLock(__x) boost::mutex::scoped_lock lock((__x))

#define SG_TRACE(__x) std::cout<<(__x)<<std::endl;
#define SG_TRACE2(__x, __y) std::cout<<(__x)<<(__y)<<std::endl;
#define SG_TRACE3(__x, __y, __z) std::cout<<(__x)<<(__y)<<__z<<std::endl;
#define SgInsSessionServMgr SessionServiceManager::getInstance()

#endif // SGMacro_h__