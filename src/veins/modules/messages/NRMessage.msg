
cplusplus {{
#include <map>
#include "veins/modules/messages/BaseFrame1609_4_m.h"
#include "veins/base/utils/SimpleAddress.h"
}}

namespace veins;

class BaseFrame1609_4;
class LAddress::L2Type extends void;

packet NRMessage extends BaseFrame1609_4 {
    int numElements;
    int ids[50];
    double speeds[50];
    string edges[50];
    string lanes[50];
    double lanePositions[50];
    string destinations[50];
    simtime_t times[50];
}
