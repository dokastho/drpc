#include "drpc.h"
#include "test_rpcs.h"
#include <iostream>
#include <map>
#include <mutex>
#include <string>

// std::mutex l;

class Test
{
private:
    drpc_server *s;
    int id;

public:
    Test()
    {
        drpc_host d{"localhost", 8021};
        s = new drpc_server(d, (void *)this);
        id = 1;

        s->publish_endpoint("foo", (void *)this->foo);
        std::cout << "starting server" << std::endl;
        s->start();
    }

    static void foo(Test *t, drpc_msg &m)
    {
        // l.lock();
        // basic_request *breq = (basic_request *)m.req->args;
        // std::cout << t->id << " Received a message from " << breq->name << std::endl;

        // setup reply
        int status = 0xf;
        basic_reply *brep = (basic_reply *)m.rep->args;
        brep->host = t->id;
        brep->status = status;
        m.rep->len = sizeof(basic_reply);

        // l.unlock();
        return;
    }

    ~Test()
    {
        delete s;
    }
};

int main()
{
    Test t;
    std::string cmd = "";
    do
    {
        std::cout << "enter 'q' to quit\n$ ";
        std::cin >> cmd;
    } while (cmd[0] != 'q');
    return 0;
}