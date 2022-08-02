#include <iostream>

#include "bytecode.h"
#include "command.h"
#include "component.h"
#include "data-locality.h"
#include "dirty-flag.h"
#include "double-buffer.h"
#include "event-queue.h"
#include "flyweight.h"
#include "game-loop.h"
#include "hello-world.h"
#include "object-pool.h"
#include "observer.h"
#include "prototype.h"
#include "service-locator.h"
#include "singleton.h"
#include "spatial-partition.h"
#include "state.h"
#include "subclass-sandbox.h"
#include "type-object.h"
#include "update-method.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* const argv[])
{
    UnbufferedSlapstick::testComedy();
    SpatialPartition::test();
    ObserverPattern::test();
}
