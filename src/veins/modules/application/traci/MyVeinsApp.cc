#include "veins/modules/application/traci/MyVeinsApp.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Define_Module(veins::MyVeinsApp);

void MyVeinsApp::initialize(int stage)
{
    ECODEBaseApplLayer::initialize(stage);
    if (stage == 0)
    {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
    }
    simtime_t time = 0;
    lastSentADV = 0;
}

void MyVeinsApp::onWSM(BaseFrame1609_4* frame)
{
    if (ADVMessage* adv = dynamic_cast<ADVMessage*>(frame))
    {
        NRTableEntry * ent = new NRTableEntry();
        ent->id = adv->getSenderID();
        ent->speed = adv->getSenderSpeed();
        ent->edge = adv->getSenderEdge();
        ent->lane = adv->getSenderLane();
        ent->lanePosition = adv->getSenderLanePosition();
        ent->destination = adv->getSenderDestination();
        ent->time = adv->getSendingTime();
        nr[adv->getSenderID()] = ent;
        std::cout << id << ": Tabela NR:" << std::endl;
        for (auto const& par : nr)
        {
            std::cout << par.first << " -> " << par.second->time << std::endl;
        }

        NRMessage* nr = new NRMessage();
        populateWSM(nr);
        populateNR(nr);
        sendDown(nr);
    }
    else if (NRMessage* nr = dynamic_cast<NRMessage*>(frame))
    {
        for (int i = 0; i < nr->getNumElements(); i++)
        {
            int id = nr->getIds(i);
            simtime_t time = nr->getTimes(i);

            if ((this->nr.find(id) != this->nr.end()) and
                (this->time >= time))
            {
                continue;
            }
            NRTableEntry * ent = new NRTableEntry();
            ent->id = id;
            ent->time = time;
            ent->speed = nr->getSpeeds(i);
            ent->edge = nr->getEdges(i);
            ent->lane = nr->getLanes(i);
            ent->lanePosition = nr->getLanePositions(i);
            ent->destination = nr->getDestinations(i);
            this->nr[id] = ent; 
        }
    }
}

void MyVeinsApp::handleSelfMsg(cMessage* msg)
{
    if (TraCIDemo11pMessage* wsm = dynamic_cast<TraCIDemo11pMessage*>(msg))
    {
        // send this message on the service channel until the counter is 3 or higher.
        // this code only runs when channel switching is enabled
        sendDown(wsm->dup());
        wsm->setSerial(wsm->getSerial() + 1);
        if (wsm->getSerial() >= 3) {
            // stop service advertisements
            delete (wsm);
        }
        else {
            scheduleAt(simTime() + 1, wsm);
        }
    }
    else
    {
        ECODEBaseApplLayer::handleSelfMsg(msg);
    }
}

void MyVeinsApp::populateADV(ADVMessage* adv)
{
    adv->setSenderID(id);
    adv->setSenderSpeed(speed);
    adv->setSenderEdge(edge.c_str());
    adv->setSenderLane(lane.c_str());
    adv->setSenderLanePosition(lanePosition);
    adv->setSenderDestination(destination.c_str());
    adv->setTime(time);
}

void MyVeinsApp::populateNR(NRMessage* nr)
{
    NRTable table = NRTable(this->nr);
    nr->setNumElements(table.num_elements);
    for (unsigned int i = 0; i < table.num_elements; i++)
    {
        nr->setIds(i, table.entries[i]->id);
        nr->setSpeeds(i, table.entries[i]->speed);
        nr->setEdges(i, table.entries[i]->edge.c_str());
        nr->setLanes(i, table.entries[i]->lane.c_str());
        nr->setLanePositions(i, table.entries[i]->lanePosition);
        nr->setDestinations(i, table.entries[i]->destination.c_str());
        nr->setTimes(i, table.entries[i]->time);
    }
}

void MyVeinsApp::handlePositionUpdate(cObject* obj)
{
    ECODEBaseApplLayer::handlePositionUpdate(obj);

    id = mobility->getId();
    time = simTime();
    speed = mobility->getSpeed();
    edge = traciVehicle->getRoadId();
    lane = traciVehicle->getLaneId();
    lanePosition = traciVehicle->getLanePosition();
    destination = traciVehicle->getPlannedRoadIds().back();

    NRTableEntry * ent = new NRTableEntry();
    ent->id = id;
    ent->time = time;
    ent->speed = speed;
    ent->edge = edge;
    ent->lane = lane;
    ent->lanePosition = lanePosition;
    ent->destination = destination;
    nr[id] = ent;

    if (time - lastSentADV > 1.0)
    {
        lastSentADV = time;
        std::cout << mobility->getId() << " enviando ADV em " << simTime() << " Road = " << traciVehicle->getRoadId() << " Lane = " << traciVehicle->getLaneId() << std::endl;
        ADVMessage* adv = new ADVMessage();
        populateWSM(adv);
        populateADV(adv);
        sendDown(adv);
    }

}
