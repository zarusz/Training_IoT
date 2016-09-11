#include "MessageBus.h"

void MessageBus::SetHandler(MessageHandler* handler)
{
    this->handler = handler;
}
