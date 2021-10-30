
cplusplus {{
#include "veins/base/utils/Coord.h"
#include "veins/modules/messages/BaseFrame1609_4_m.h"
#include "veins/base/utils/SimpleAddress.h"
}}

namespace veins;

class BaseFrame1609_4;
class noncobject Coord;
class LAddress::L2Type extends void;

packet ADVMessage extends BaseFrame1609_4 {
    int senderID;
    double senderSpeed;
    Coord senderPos;
    Coord senderDirection;
    string senderDestination;
    simtime_t simTime;
}
