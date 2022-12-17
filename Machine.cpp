#include <sstream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Machine.h"

constexpr auto INIT_Capital_Pools = 100000.0;
constexpr auto MAX_Capital_Pools = 1000000.0;

Machine atmMachine;

Machine::Machine()
{
    this->capitalPools = 0;
    std::ifstream read;
    read.open("./data/MachineData.txt", std::ios_base::in);
    if (read.is_open() == false)
    {
        MessageBox(nullptr, L"资金池异常，已初始化资金池", L"Warning", MB_OK);
        this->capitalPools = INIT_Capital_Pools;
    }
    else
    {
        std::string input;
        std::getline(read, input);
        std::stringstream stream(input);
        stream >> this->capitalPools;
        read.close();
    }
}

double Machine::Gain_CapitalPools()
{
    return this->capitalPools;
}

Machine::~Machine()
{
    std::ofstream write;
    write.open("./data/MachineData.txt", std::ios_base::out);
    if (write.is_open() == false)
    {
        MessageBox(nullptr, L"资金池异常，无法填入资金池", L"ERROR", MB_OK);
        system("del ./data/MachineData.txt");
    }
    else
    {
        std::stringstream stream;
        stream << this->capitalPools;
        std::string output;
        stream >> output;
        write << output << std::endl;
        write.close();
    }
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

Machine *ATMPort()
{
    return &atmMachine;
}
