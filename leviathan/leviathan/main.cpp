#include "leviathan.h"
Leviathan::cMinidump gMinidupm;

void DoTest(int count)
{
    auto start = std::chrono::steady_clock::now();

    std::vector<long long> vec;
    std::vector<char*> chunks;

    for (int cnt = 0; cnt != count; ++cnt)
    {
        for (int len = 1; len != 8; ++len)
        {
            long long v = 0;
            char* p = new char[len];
            for (int idx = 0; idx != len; ++idx)
            {
                p[idx] = (p[idx] | 0xFF);
            }
            for (int idx = 0; idx != len; ++idx)
            {
                v = p[idx];
            }
            vec.push_back(v);
            chunks.push_back(p);
        }
        for (auto p : chunks)
        {
            delete[] p;
        }
        chunks.clear();
        chunks.shrink_to_fit();
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "len: " << vec.size() << std::endl;
    std::cout << "sum: " << std::accumulate(vec.begin(), vec.end(), 0ll) << std::endl;
    std::cout << elapsed.count() << "ms" << std::endl;
}

int main(int argc, char* argv[])
{
    DoTest(10000000);
    int t;
    std::cin >> t;

    _putenv("TZ=UTC");

    std::string dir_config = "";
    if (argc == 2)
        dir_config = argv[1];

    if (!Leviathan::cLeviathan::Instance().Booting(dir_config))
    {
        printf("[SYSTEM] booting failed\n");
        return -1;
    }

    while (!Leviathan::cLeviathan::Instance().ShuttingDown())
    {
        Sleep(1);
    }

    return 0;
}