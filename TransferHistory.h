#pragma once

#ifndef TranserHistory_H
#define TranserHistory_H

#include <string>

class TransferHistory
{
private:
	std::string transferred;
	double amount;
	std::string transferredTime;

public:
	TransferHistory(std::string &lock, double cash);
	TransferHistory(std::string &lock, double cash, std::string &lockTime);
	std::string Gain_transferred();
	double Gain_amount();
	std::string Gain_transferredTime();
};

#endif // !TranserHistory_H
