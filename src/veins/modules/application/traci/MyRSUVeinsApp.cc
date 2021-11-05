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
        TSTableEntry * ent = new TSTableEntry();
        ent->senderVehicleID = tmr->getSenderID();
        ent->time = tmr->getSendingTime();
        ent->edge = tmr->getSenderEdge();
        if (this->ts.find(ent->edge) != this->ts.end())
        {
            if (this->ts[ent->edge]->time > ent->time)
            {
                return;
            }
        }
        ent->edgeAverageSpeed = tmr->getEdgeAverageSpeed();
        ent->edgeDensity = tmr->getEdgeDensity();
        ent->edgeTravelTime = tmr->getEdgeTravelTime();
        ts[ent->edge] = ent;
        std::cout << "RSU " << getId() << std::endl;
        for (auto const& e : ts)
        {
            std::cout << "Estado estimado da aresta " << e.first << " " << e.second->edgeAverageSpeed << std::endl;
        }
    }
}
