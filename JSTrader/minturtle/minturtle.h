#ifndef MINTURTLE_H
#define MINTURTLE_H
#ifdef MINTURTLE_EXPORTS
#define MINTURTLE_API __declspec(dllexport)
#else
#define MINTURTLE_API __declspec(dllimport)
#endif
#include"StrategyTemplate.h"
extern "C" MINTURTLE_API StrategyTemplate * CreateStrategy(CTAAPI *ctamanager);//创建策略
extern "C" MINTURTLE_API int ReleaseStrategy();//释放策略
std::vector<StrategyTemplate*>g_minturtle_v;//全局指针

#include<vector>
#include<algorithm>
#include<regex>
#include"talib.h"
#include"libbson-1.0\bson.h"
#include"libmongoc-1.0\mongoc.h"
class MINTURTLE_API minturtle : public StrategyTemplate
{
public:
	minturtle(CTAAPI *ctamanager);
	~minturtle();

	void onInit();
	//TICK
	void onTick(TickData Tick);
	//BAR
	void onBar(BarData Bar);
	void on5Bar(BarData Bar);
	//报单回调
	void onOrder(std::shared_ptr<Event_Order>e);
	//成交回调
	void onTrade(std::shared_ptr<Event_Trade>e);

	//指标
	std::mutex m_HLCmtx;
	std::vector<double>close_vector;
	std::vector<double>high_vector;
	std::vector<double>low_vector;

	std::vector<double>close_10_vector;
	bool opened;
	int volumelimit;
	double high_100;
	double low_100;
	double high_10;
	double low_10;
	double width;

	double openPrice;

	double holdingPrice;
	double holdingProfit;
	double highProfit;

	std::set<std::string> m_ninetoeleven;
	std::set<std::string> m_ninetohalfeleven;
	std::set<std::string> m_ninetoone;
	std::set<std::string> m_ninetohalftwo;
	BarData m_5Bar;
	//缓存用
	double lastprice;				//更新界面
	//更新界面
	void putEvent();
};
#endif