#pragma once

#ifndef Machine_H
#define Machine_H

class Machine
{
private:
	double capitalPools;  // 资金池
public:
    Machine();
    double Gain_CapitalPools();          // 获取资金池数值
    bool Push_CapitalPools(double eval); // 资金存入资金池
    bool Pop_CapitalPools(double eval);  // 资金取出资金池
    void EmptyThePool();                 // 清空资金池
};

//Port
Machine* ATMPort();

#endif // !Machine_H
