#include "leviathan.h"
#include "rapidjson/document.h"

using namespace rapidjson;

const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";

int main(int argc, wchar_t* argv[])
{
    Document document;
    document.Parse(json);

    Leviathan::cLeviathan::instance().do_somting();

    std::cout << document["hello"].GetString() << std::endl;
    getchar();

    return 0;
}