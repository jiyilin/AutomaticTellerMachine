#include "Machine.h"

constexpr auto INIT_Capital_Pools = 100000.0;;
constexpr auto MAX_Capital_Pools = 1000000.0;;

Machine atmMachine;

Machine::Machine()
{
	this->capitalPools = INIT_Capital_Pools;
}

double Machine::Gain_CapitalPools()
{
	return this->capitalPools;
}

bool Machine::Push_CapitalPools(double eval)
{
    if (this->capitalPools + eval > MAX_Capital_Pools)
    {
        return false;
    }
    this->capitalPools = this->capitalPools + eval;
    return true;
}

bool Machine::Pop_CapitalPools(double eval)
{
    if (this->capitalPools - eval < 0)
    {
        return false;
    }
    this->capitalPools = this->capitalPools - eval;
    return true;
}

void Machine::EmptyThePool()
{
	this->capitalPools = 0.0;
}

Machine* ATMPort()
{
    return &atmMachine;
}
