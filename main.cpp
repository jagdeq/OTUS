#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "async.h"

constexpr size_t g_cmdBlockSize = 3;

void doFirstThread()
{
    std::vector<std::string> buf = {"cmd1_1", "cmd2_1", "{",      "cmd3_1", "cmd4_1", "}", "{", "cmd5_1",  "cmd6_1",
                                    "{",      "cmd7_1", "cmd8_1", "}",      "cmd9_1", "}", "{", "cmd10_1", "cmd11_1"};

    size_t context = async::connect(3);
    for (std::string& cmd : buf)
        async::receive(cmd.data(), cmd.size(), context);

    async::disconnect(context);
}

void doSecondThread()
{
    std::vector<std::string> buf{"cmd1_2", "cmd2_2", "cmd3_2", "cmd4_2", "cmd5_2"};
    size_t context = async::connect(3);
    for (std::string& cmd : buf)
        async::receive(cmd.data(), cmd.size(), context);

    async::disconnect(context);
}

int main()
{
    std::thread th(doSecondThread);
    doFirstThread();
    th.join();

    while (true) {}
    return 0;
}
