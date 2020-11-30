#include "leviathan.h"
#include "rapidjson/document.h"

using namespace rapidjson;

const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";

int main(int argc, char* argv[])
{
    _putenv("TZ=UTC");

    Document document;
    document.Parse(json);

    std::string dir_config = "";
    if (argc == 2)
        dir_config = argv[1];
    if (!Leviathan::cLeviathan::Instance().Booting(dir_config))
    {
        return -1;
    }

    while (!Leviathan::cLeviathan::Instance().ShuttingDown())
    {
        Sleep(1);
    }

    return 0;
}