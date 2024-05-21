
#include "cli.h"

#include <iostream>




class TheApp
{
    public:
        void Func();
};


void TheApp::Func()
{
    std::cout << "TheApp::Func()\n";
}


CLI_RETCODE CmdExit(TheApp &/*theApp*/, const char * /*cline*/)
{
    std::cout << __func__ << std::endl;
    return CLI_RETCODE::ERROR_QUIT;
}


CLI_RETCODE CmdFunc(TheApp &theApp, const char * /*cline*/)
{
    std::cout << __func__ << std::endl;
    theApp.Func();
    return CLI_RETCODE::SUCCESS;
}


int main(int /*argc*/, const char * /*argv*/[])
{
    std::cout << "CLI Command Line Interface example V0.0" << std::endl;

    TheApp theApp;

    CmdMap<TheApp> mapCmd("mapCmd");
    mapCmd["exit"]  = { "Exit", "Quits the program",    CmdExit };
    mapCmd["quit"]  = { "Exit", "Quits the program",    CmdExit };
    mapCmd["q"]     = { "Exit", "Quits the program",    CmdExit };
    mapCmd["f"]     = { "Func", "Executes Func()",      CmdFunc };
    mapCmd["func"]  = { "Func", "Executes Func()",      CmdFunc };

    auto fn = [&mapCmd, &theApp] (const char *cline) -> CLI_RETCODE
    {
        CLI_RETCODE rc = mapCmd.ExecuteCommand(theApp, cline);
        return rc;
    };

    cli(fn);

    return 0;
}

