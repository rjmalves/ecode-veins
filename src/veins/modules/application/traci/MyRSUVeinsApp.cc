#include "veins/modules/application/traci/MyRSUVeinsApp.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Define_Module(veins::MyRSUVeinsApp);

void MyRSUVeinsApp::onWSM(BaseFrame1609_4* frame)
{
    // TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);

    // this rsu repeats the received traffic update in 2 seconds plus some random delay
    // sendDelayedDown(wsm->dup(), 2 + uniform(0.01, 0.2));
}
