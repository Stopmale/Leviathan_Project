#include "leviathan.h"
#include "rapidjson/document.h"

using namespace rapidjson;

const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";

int main(int argc, wchar_t* argv[])
{
    _putenv("TZ=UTC");

    Document document;
    document.Parse(json);

    std::string dir_config = "";
    if (argc == 2)
        dir_config = Leviathan::WideCharToMultiByte(argv[1]);
    Leviathan::cLeviathan::Instance().Booting(dir_config);

    //std::cout << document["hello"].GetString() << std::endl;
    std::cout << "안녕" << std::endl;
    return 0;
}