#include "veins/modules/application/traci/MyRSUVeinsApp.h"

using namespace veins;

Define_Module(veins::MyRSUVeinsApp);

void MyRSUVeinsApp::initialize(int stage)
{
    ECODEBaseApplLayer::initialize(stage);
}

void MyRSUVeinsApp::onWSM(BaseFrame1609_4* frame)
{
    if (TMRMessage* tmr = dynamic_cast<TMRMessage*>(frame)) {
        std::cout << "RSU " << getId() << " Recebeu TMR de " << tmr->getSenderID() << " em " << simTime() << std::endl;
        std::cout << "    Velocidade no segmento " << tmr->getSenderEdge() << " = " << tmr->getEdgeAverageSpeed() << std::endl;
    }
}
