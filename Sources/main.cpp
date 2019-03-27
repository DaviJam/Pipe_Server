//+------------------------------------------------------------------+
//|                                                      Pipe Server |
//|                                                   Copyright .... |
//|                                                                  |
//+------------------------------------------------------------------+
#include "Headers\pipeserver.h"


/*
enum Symbols{EURAUD,EURCAD,EURCHF,EURGBP,EURJPY,EURNZD,EURUSD,AUDCAD,AUDCHF,AUDJPY,AUDNZD,AUDUSD,CADCHF,CADJPY,CHFJPY,GBPAUD,GBPCAD,GBPCHF,GBPJPY,GBPNZD,GBPUSD,NZDCAD,NZDCHF,NZDJPY,NZDUSD,USDCAD,USDCHF,USDJPY};

static int index=0;

//--- Creation control
static bool M30_FreeToConnect=true;
static bool H1_FreeToConnect=true;
static bool H4_FreeToConnect=true;
static bool Daily_FreeToConnect=true;
static bool Weekly_FreeToConnect=true;
//static bool Monthly_FreeToConnect=true;

std::string Pairs(Symbols sym)
{
    std::string pairs[28]={"EURAUD","EURCAD","EURCHF","EURGBP","EURJPY","EURNZD","EURUSD","AUDCAD","AUDCHF","AUDJPY","AUDNZD","AUDUSD","CADCHF","CADJPY","CHFJPY","GBPAUD","GBPCAD","GBPCHF","GBPJPY","GBPNZD","GBPUSD","NZDCAD","NZDCHF","NZDJPY","NZDUSD","USDCAD","USDCHF","USDJPY"};

    return pairs[sym];
}

void ClearCsv(std::string ID)
{
    std::string pairs[28]={"EURAUD","EURCAD","EURCHF","EURGBP","EURJPY","EURNZD","EURUSD","AUDCAD","AUDCHF","AUDJPY","AUDNZD","AUDUSD","CADCHF","CADJPY","CHFJPY","GBPAUD","GBPCAD","GBPCHF","GBPJPY","GBPNZD","GBPUSD","NZDCAD","NZDCHF","NZDJPY","NZDUSD","USDCAD","USDCHF","USDJPY"};
    //std::string index[6]={"M30","H1","H4","Daily","Weekly","Monthly"};

    for(int i=EURAUD; i<=USDJPY; i++)
    {

        std::string FilePath="H:\\Users\\Dada\\Documents\\QtProject\\PipeServerMt5\\Pairs\\"+ID+"\\"+pairs[i]+".csv";
        std::ofstream PriceData;
        PriceData.open(FilePath, std::ofstream::out | std::ofstream::trunc);
        PriceData.close();

        std::string DatePath="H:\\Users\\Dada\\Documents\\QtProject\\PipeServerMt5\\Pairs\\"+ID+"\\"+"Date.csv";
        std::ofstream DateData;
        DateData.open(DatePath, std::ofstream::out | std::ofstream::trunc);
        DateData.close();

    }

}

int PriceWriter(std::string ID,char *symbol, char *open, char *close, bool append_mode=false )
{

    std::string FilePath="H:\\Users\\Dada\\Documents\\QtProject\\PipeServerMt5\\Pairs\\XXXXXX.csv";
    std::string SymbolName="XXXXXX";

    SymbolName=symbol;
    FilePath="H:\\Users\\Dada\\Documents\\QtProject\\PipeServerMt5\\Pairs\\"+ID+"\\"+SymbolName+".csv";// throws exceptions!



    try
    {
        std::cout << FilePath << std::endl;
        csvfile PriceData(FilePath,";",append_mode);

        // Header
        //   csv << "TIME" << "PAIR" << "OPEN" << "CLOSE" << endrow;
        // Data
        PriceData << open << close << endrow;

    }
    catch (const std::exception &ex)
    {
        std::cout << "Exception was thrown: " << ex.what() << std::endl;
    }


    return 0;
}

int DateWriter(std::string ID, char *time, bool append_mode=false)
{
    std::string DatePath="H:\\Users\\Dada\\Documents\\QtProject\\PipeServerMt5\\Pairs\\"+ID+"\\Date.csv";
    try
    {
        csvfile DateData(DatePath,";",append_mode);
        DateData << time << endrow;
    }
    catch (const std::exception &ex)
    {
        std::cout << "Exception was thrown: " << ex.what() << std::endl;
    }

    return 0;
}

int DateWeekWriter(char *time)
{
    std::string DatePath="H:\\Users\\Dada\\Documents\\QtProject\\PipeServerMt5\\WeekDate.csv";
    try
    {
        csvfile DateData(DatePath,";",false);
        DateData << time << endrow;
    }
    catch (const std::exception &ex)
    {
        std::cout << "Exception was thrown: " << ex.what() << std::endl;
    }

    return 0;
}

int SendString(CPipeManager &manager, LPCSTR value)
{
    //---Send value

    wprintf(L"Server: sending value\n");
    if(!manager.SendString(value))
    {
        wprintf(L"Server: sending string failed\n");
        return(-1);
    }

    return 0;
}

template<typename T>
int SendValue(CPipeManager &manager, T &value)
{
    //---Send value

    wprintf(L"Server: sending value\n");
    if(!manager.Send(&value,sizeof(value)))
    {
        wprintf(L"Server: sending value failed\n");
        return(-1);
    }

    return 0;
}

int ReadString(CPipeManager &manager,char *ToArray)
{
    //--- Read String
    char Answer[256];
    if(!manager.ReadString(Answer,_countof(Answer)-1))
    {
        wprintf(L"Server: reading string failed\n");
        return(-1);
    }
    wprintf(L"Server: '%S' received\n",Answer);
    strcpy_s(ToArray,sizeof(Answer),Answer);

    return 0;
}

int ReadValue(CPipeManager &manager, int value)
{
    //--- Read value

    if(!manager.Read(&value,sizeof(value)))
    {
        wprintf(L"Server: reading value failed\n");
        return(-1);
    }
    wprintf(L"Server: %d received\n",value);

    return 0;
}

//+------------------------------------------------------------------+
//|Pipe server: retrieve data from client                            |
//+------------------------------------------------------------------+
int PipeServer(void)
{


    //--- create named pipe

    CPipeManager  M30_Pipe;
    CPipeManager  H1_Pipe;
    CPipeManager  H4_Pipe;
    CPipeManager  Daily_Pipe;
    CPipeManager  Weekly_Pipe;
    CPipeManager  Monthly_Pipe;


    if(M30_FreeToConnect==true)
    {
        if(!M30_Pipe.Create(L"\\\\.\\pipe\\MQL5.Pipe.ServerM30"))
            return(-1);
    }
    else if(H1_FreeToConnect==true)
    {
        if(!H1_Pipe.Create(L"\\\\.\\pipe\\MQL5.Pipe.ServerH1"))
            return(-1);
    }
    else if(H4_FreeToConnect==true)
    {
        if(!H4_Pipe.Create(L"\\\\.\\pipe\\MQL5.Pipe.ServerH4"))
            return(-1);
    }
    else if(Daily_FreeToConnect==true)
    {
        if(!Daily_Pipe.Create(L"\\\\.\\pipe\\MQL5.Pipe.ServerDaily"))
            return(-1);
    }
    else if(Weekly_FreeToConnect==true)
    {
        if(!Weekly_Pipe.Create(L"\\\\.\\pipe\\MQL5.Pipe.ServerWeekly"))
            return(-1);
    }
    /* else if(Monthly_FreeToConnect==true)
    {
        if(!Monthly_Pipe.Create(L"\\\\.\\pipe\\MQL5.Pipe.ServerMonthly"))
            return(-1);
    }


    //--- wait for client

    char          Time[256];
    char          Symbol[256];
    char          answer[256];
    char          Open[256];
    char          Close[256];
    char          Bars[256];


    wprintf(L"Client: waiting for connection...\n");

    while(!M30_Pipe.IsConnected() &&
          !H1_Pipe.IsConnected() &&
          !H4_Pipe.IsConnected() &&
          !Daily_Pipe.IsConnected() &&
          !Weekly_Pipe.IsConnected() &&
          !Monthly_Pipe.IsConnected())
    {
        if(!M30_Pipe.ReadString(answer,_countof(answer)-1) &&
                !H1_Pipe.ReadString(answer,_countof(answer)-1) &&
                !H4_Pipe.ReadString(answer,_countof(answer)-1) &&
                !Daily_Pipe.ReadString(answer,_countof(answer)-1) &&
                !Weekly_Pipe.ReadString(answer,_countof(answer)-1) &&
                !Monthly_Pipe.ReadString(answer,_countof(answer)-1))
        {
            Sleep(250);
            continue;
        }
    }
    wprintf(L"Client: connected as '%S'\n",answer);

    //--- Control creation of each pipe in an ordered way
    if(strcmp(answer,"M30 Pipe")==0){M30_FreeToConnect=false; }
    if(strcmp(answer,"H1 Pipe")==0){H1_FreeToConnect=false; }
    if(strcmp(answer,"H4 Pipe")==0){H4_FreeToConnect=false; }
    if(strcmp(answer,"Daily Pipe")==0){Daily_FreeToConnect=false; }
    if(strcmp(answer,"Weekly Pipe")==0){
        M30_FreeToConnect=true;
        H1_FreeToConnect=true;
        H4_FreeToConnect=true;
        Daily_FreeToConnect=true;
        Weekly_FreeToConnect=true;

    }

    /*if(strcmp(answer,"Monthly Pipe")==0){
                                          M30_FreeToConnect=true;
                                          H1_FreeToConnect=true;
                                          H4_FreeToConnect=true;
                                          Daily_FreeToConnect=true;
                                          Weekly_FreeToConnect=true;
                                          Monthly_FreeToConnect=true;

                                        }*//*


    //--- Read M30 Datas
    if(M30_Pipe.IsConnected())
    {
        //--- Clear CSV file
        ClearCsv("M30");

        //--- Read bars
        wprintf(L"Server: reading bars\n");
        memset(Bars, 0, sizeof (Bars));
        ReadString(M30_Pipe,Bars);
        index=0;

        for (int i = EURAUD; i<=USDJPY; i++) {

            for(int i = 0;i<=atoi(Bars);i++)
            {
                index++;
                //--- Read Time
                wprintf(L"Server: reading Time\n");
                ReadString(M30_Pipe,Time);
                wprintf(L"Server: Time: %S\n",Symbol);
                if(index<=atoi(Bars)+1)
                {
                    //--- Write date to file
                    DateWriter("M30",Time);
                }

                //--- Read Symbol
                wprintf(L"Server: reading Symbol\n");
                ReadString(M30_Pipe,Symbol);
                wprintf(L"Server: Symbol: %S\n",Symbol);

                //--- Read Open
                wprintf(L"Server: reading Open Price\n");
                ReadString(M30_Pipe,Open);
                wprintf(L"Server: Open: %S\n",Symbol);

                //--- Read Close
                wprintf(L"Server: reading Close Price\n");
                ReadString(M30_Pipe,Close);
                wprintf(L"Server: Close: %S\n",Symbol);

                //---  Write data to file
                PriceWriter("M30",Symbol,Open,Close);



            }
        }

        M30_Pipe.Close();
    }
    //--- Read H1 Datas
    if(H1_Pipe.IsConnected())
    {
        //--- Clear CSV file
        ClearCsv("H1");

        //--- Read bars
        wprintf(L"Server: reading bars\n");
        memset(Bars, 0, sizeof (Bars));
        ReadString(H1_Pipe,Bars);
        index=0;

        for (int i = EURAUD; i<=USDJPY; i++)
        {

            for(int i = 0;i<=atoi(Bars);i++)
            {
                index++;

                //--- Read Time
                wprintf(L"Server: reading Time\n");
                ReadString(H1_Pipe,Time);
                if(index<=atoi(Bars)+1)
                {
                    //--- Write date to file
                    DateWriter("H1",Time);
                }

                //--- Read Symbol
                wprintf(L"Server: reading Symbol\n");
                ReadString(H1_Pipe,Symbol);

                //--- Read Open
                wprintf(L"Server: reading Open Price\n");
                ReadString(H1_Pipe,Open);

                //--- Read Close
                wprintf(L"Server: reading Close Price\n");
                ReadString(H1_Pipe,Close);

                //---  Write data to file
                PriceWriter("H1",Symbol,Open,Close);

            }
        }

        H1_Pipe.Close();
    }
    //--- Read H4 Datas
    if(H4_Pipe.IsConnected())
    {
        //--- Clear CSV file
        ClearCsv("H4");

        //--- Read bars
        wprintf(L"Server: reading bars\n");
        memset(Bars, 0, sizeof (Bars));
        ReadString(H4_Pipe,Bars);
        index=0;

        for (int i = EURAUD; i<=USDJPY; i++)
        {

            for(int i = 0;i<=atoi(Bars);i++)
            {
                index++;

                //--- Read Time
                wprintf(L"Server: reading Time\n");
                ReadString(H4_Pipe,Time);
                if(index<=atoi(Bars)+1)
                {
                    //--- Write date to file
                    DateWriter("H4",Time);
                }

                //--- Read Symbol
                wprintf(L"Server: reading Symbol\n");
                ReadString(H4_Pipe,Symbol);

                //--- Read Open
                wprintf(L"Server: reading Open Price\n");
                ReadString(H4_Pipe,Open);

                //--- Read Close
                wprintf(L"Server: reading Close Price\n");
                ReadString(H4_Pipe,Close);

                //---  Write data to file
                PriceWriter("H4",Symbol,Open,Close);

            }
        }

        H4_Pipe.Close();
    }
    //--- Read Daily Datas
    if(Daily_Pipe.IsConnected())
    {
        //--- Clear CSV file
        ClearCsv("Daily");

        //--- Read bars
        wprintf(L"Server: reading bars\n");
        memset(Bars, 0, sizeof (Bars));
        ReadString(Daily_Pipe,Bars);

        index=0;

        for (int i = EURAUD; i<=USDJPY; i++)
        {

            for(int i = 0;i<=atoi(Bars);i++)
            {
                index++;
                //--- Read Time
                wprintf(L"Server: reading Time\n");
                ReadString(Daily_Pipe,Time);
                if(index<=atoi(Bars)+1)
                {
                    //--- Write date to file
                    DateWriter("Daily",Time);
                }
                //--- Read Symbol
                wprintf(L"Server: reading Symbol\n");
                ReadString(Daily_Pipe,Symbol);

                //--- Read Open
                wprintf(L"Server: reading Open Price\n");
                ReadString(Daily_Pipe,Open);

                //--- Read Close
                wprintf(L"Server: reading Close Price\n");
                ReadString(Daily_Pipe,Close);

                //---  Write data to file
                PriceWriter("Daily",Symbol,Open,Close);

            }
        }

        Daily_Pipe.Close();
    }
    //--- Read Weekly Datas
    if(Weekly_Pipe.IsConnected())
    {
        //--- Clear CSV file
        ClearCsv("Weekly");

        //--- Read bars
        wprintf(L"Server: reading bars\n");
        memset(Bars, 0, sizeof (Bars));
        ReadString(Weekly_Pipe,Bars);
        index=0;

        for (int i = EURAUD; i<=USDJPY; i++)
        {

            for(int i = 0;i<=atoi(Bars);i++)
            {
                index++;
                //--- Read Time
                wprintf(L"Server: reading Time\n");
                ReadString(Weekly_Pipe,Time);
                if(index<=atoi(Bars)+1)
                {
                    //--- Write date to file
                    DateWriter("Weekly",Time);
                }
                //--- Read Symbol
                wprintf(L"Server: reading Symbol\n");
                ReadString(Weekly_Pipe,Symbol);

                //--- Read Open
                wprintf(L"Server: reading Open Price\n");
                ReadString(Weekly_Pipe,Open);

                //--- Read Close
                wprintf(L"Server: reading Close Price\n");
                ReadString(Weekly_Pipe,Close);

                //---  Write data to file
                PriceWriter("Weekly",Symbol,Open,Close);

            }
        }

        Weekly_Pipe.Close();
    }
    //--- Read Monthly Datas
    if(Monthly_Pipe.IsConnected())
    {
        //--- Clear CSV file
        ClearCsv("Monthly");

        //--- Read bars
        wprintf(L"Server: reading bars\n");
        memset(Bars, 0, sizeof (Bars));
        ReadString(Monthly_Pipe,Bars);
        index=0;

        for (int i = EURAUD; i<=USDJPY; i++)
        {

            for(int i = 0;i<=atoi(Bars);i++)
            {
                index++;
                //--- Read Time
                wprintf(L"Server: reading Time\n");
                ReadString(Monthly_Pipe,Time);
                if(index<=atoi(Bars)+1)
                {
                    //--- Write date to file
                    DateWriter("Monthly",Time);
                }
                //--- Read Symbol
                wprintf(L"Server: reading Symbol\n");
                ReadString(Monthly_Pipe,Symbol);

                //--- Read Open
                wprintf(L"Server: reading Open Price\n");
                ReadString(Monthly_Pipe,Open);

                //--- Read Close
                wprintf(L"Server: reading Close Price\n");
                ReadString(Monthly_Pipe,Close);

                //---  Write data to file
                PriceWriter("Monthly",Symbol,Open,Close);

            }
        }

        Monthly_Pipe.Close();

    }
    //---
    return(0);
}*/


//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int _tmain(int argc, _TCHAR* argv[])
{
    wprintf(L"Pipe Server\n");
    wprintf(L"Copyright ....\n");

PipeServer Server;


    //--- Run Pipe server
    while(true)
    {
        Server.Run();
    }
    //---
    return(0);
}
//+------------------------------------------------------------------+
