#pragma once

#ifndef Machine_H
#define Machine_H

class Machine
{
private:
	double capitalPools;  // �ʽ��
public:
    Machine();
    double Gain_CapitalPools();          // ��ȡ�ʽ����ֵ
    bool Push_CapitalPools(double eval); // �ʽ�����ʽ��
    bool Pop_CapitalPools(double eval);  // �ʽ�ȡ���ʽ��
    void EmptyThePool();                 // ����ʽ��
};

//Port
Machine* ATMPort();

#endif // !Machine_H
