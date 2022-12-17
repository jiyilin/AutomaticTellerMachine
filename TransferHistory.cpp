#include <time.h>
#include <sstream>
#include "TransferHistory.h"

TransferHistory::TransferHistory(std::string &lock, double cash)
{
	this->transferred = lock;
	this->amount = cash;
	time_t now = time(nullptr);
	tm *process = localtime(&now);
	std::stringstream stream;
	stream << process->tm_year + 1900 << "_" << process->tm_mon + 1 << "_" << process->tm_mday << "_" << process->tm_hour << "_" << process->tm_min << "_" << process->tm_sec;
	stream >> this->transferredTime;
}

TransferHistory::TransferHistory(std::string &lock, double cash, std::string &lockTime)
{
	this->transferred = lock;
	this->amount = cash;
	this->transferredTime = lockTime;
}

std::string TransferHistory::Gain_transferred()
{
	return this->transferred;
}

double TransferHistory::Gain_amount()
{
	return this->amount;
}

std::string TransferHistory::Gain_transferredTime()
{
	return this->transferredTime;
}
