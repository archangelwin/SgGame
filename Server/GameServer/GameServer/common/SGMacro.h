//  [3/5/2015 wuliangyu]

#ifndef SGMacro_h__
#define SGMacro_h__

#define NS_BEGIN_SG	namespace sg{
#define NS_END_SG	}
#define US_NS_SG	using namespace sg;
#define US_NS_STD	using namespace std;
#define US_NS_BOOST	using namespace boost;

#define SG_TRACE(__x) std::cout<<(__x)<<std::endl;
#define SG_TRACE2(__x, __y) std::cout<<(__x)<<(__y)<<std::endl;

#endif // SGMacro_h__