#include "leviathan.h"
Leviathan::cMinidump gMinidupm;

class test
{
public :
    bool temp;
};

int main(int argc, char* argv[])
{
    _putenv("TZ=UTC");

    std::string dir_config = "";
    if (argc == 2)
        dir_config = argv[1];
    if (!Leviathan::cLeviathan::Instance().Booting(dir_config))
    {
        printf("[SYSTEM] booting failed\n");
        return -1;
    }

    test* obj = new test;
    obj = NULL;
    obj->temp = false;

    while (!Leviathan::cLeviathan::Instance().ShuttingDown())
    {
        Sleep(1);
    }

    return 0;
}