#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <NTL/ZZ_p.h>
#include <vector>

class Message
{
private:
    std::vector<NTL::ZZ_p> values;

public:
    Message(/* args */);
    ~Message();
};

Message::Message(/* args */)
{
}

Message::~Message()
{
}

#endif /* MESSAGE_HPP */
