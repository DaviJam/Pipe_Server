#ifndef PIPESERVER_H
#define PIPESERVER_H


#include "Sources/stdafx.cpp"
#include "Headers/PipeManager.h"
#include <string>
#include <cctype>


class PipeServer
{
enum Symbols{EURAUD,EURCAD,EURCHF,EURGBP,EURJPY,EURNZD,EURUSD,AUDCAD,AUDCHF,AUDJPY,AUDNZD,AUDUSD,CADCHF,CADJPY,CHFJPY,GBPAUD,GBPCAD,GBPCHF,GBPJPY,GBPNZD,GBPUSD,NZDCAD,NZDCHF,NZDJPY,NZDUSD,USDCAD,USDCHF,USDJPY};

public:
    PipeServer();

void ClearCsv(std::string ID);
int PriceWriter(std::string ID,char *symbol, char *open, char *close, bool append_mode=false );
int DateWriter(std::string ID, char *time, bool append_mode=false);
int DateWeekWriter(char *time);
int SendString(CPipeManager &manager, LPCSTR value);
template<typename T>
int SendValue(CPipeManager &manager, T &value);
int ReadString(CPipeManager &manager,char *ToArray);
int ReadValue(CPipeManager &manager, int value);
int Run(void);
std::string Pairs(Symbols sym);

private:
//--- Creation control
static bool M30_FreeToConnect;
static bool H1_FreeToConnect;
static bool H4_FreeToConnect;
static bool Daily_FreeToConnect;
static bool Weekly_FreeToConnect;
};

#endif // PIPESERVER_H
