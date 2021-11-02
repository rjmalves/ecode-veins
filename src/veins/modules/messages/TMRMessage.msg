
cplusplus {{
#include "veins/modules/messages/BaseFrame1609_4_m.h"
#include "veins/base/utils/SimpleAddress.h"
}}

namespace veins;

class BaseFrame1609_4;
class LAddress::L2Type extends void;

packet TMRMessage extends BaseFrame1609_4 {
    int senderID;
    string senderEdge;
    double edgeAverageSpeed;
    double edgeDensity;
    double edgeTravelTime;
    simtime_t time;
}
