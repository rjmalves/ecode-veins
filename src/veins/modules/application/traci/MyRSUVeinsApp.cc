#include "veins/modules/application/traci/MyRSUVeinsApp.h"

using namespace veins;

Define_Module(veins::MyRSUVeinsApp);

void MyRSUVeinsApp::initialize(int stage)
{
    ECODEBaseApplLayer::initialize(stage);
}

void MyRSUVeinsApp::onWSM(BaseFrame1609_4* frame)
{
    if (ADVMessage* adv = dynamic_cast<ADVMessage*>(frame)) {
        // std::cout << "RSU " << getId() << " Recebeu ADV de " << adv->getSenderID() << " em " << simTime() << std::endl;
    }
}
