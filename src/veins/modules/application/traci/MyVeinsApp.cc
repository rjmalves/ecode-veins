#include "veins/modules/application/traci/MyVeinsApp.h"
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
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
    lastSentNR = 0;
    lastSentTMR = 0;
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
        if (this->edge.compare(ent->edge) == 0)
        {
            nr[adv->getSenderID()] = ent;
            std::cout << "Veiculo " << id << " atualizando NR em " << time << std::endl;
        }

    }
    else if (NRMessage* nr = dynamic_cast<NRMessage*>(frame))
    {
        for (int i = 0; i < nr->getNumElements(); i++)
        {
            int id = nr->getIds(i);
            simtime_t time = nr->getTimes(i);
            if (this->nr.find(id) != this->nr.end())
            {
                if (this->nr[id]->time > time)
                {
                    continue;
                }
            }
            if (this->edge.compare(nr->getEdges(i)) != 0)
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
    ECODEBaseApplLayer::handleSelfMsg(msg);
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

void MyVeinsApp::populateTMR(TMRMessage* tmr)
{
    NRTable table = NRTable(this->nr);
    double length = traci->lane(lane).getLength();
    double edge_max_allowed_speed = traci->lane(lane).getMaxSpeed();
    double edge_density = table.entries.size() / length;
    double edge_average_speed;
    double edge_travel_time;
    std::vector<double> speeds;
    for (auto const& entrada : table.entries)
    {
        speeds.push_back(entrada->speed);
    }
    if (speeds.size() > 0)
    {
        edge_average_speed = std::accumulate(speeds.begin(),
                                             speeds.end(),
                                             0.0) / speeds.size();
    }
    else
    {
        edge_average_speed = edge_max_allowed_speed;
    }
    if (edge_average_speed == 0)
    {
        edge_travel_time = length;
    }
    else
    {
        edge_travel_time = length / edge_average_speed;
    }
    tmr->setSenderID(id);
    tmr->setSenderEdge(edge.c_str());
    tmr->setEdgeAverageSpeed(edge_average_speed);
    tmr->setEdgeDensity(edge_density);
    tmr->setEdgeTravelTime(edge_travel_time);
    tmr->setTime(time);
}

void MyVeinsApp::handlePositionUpdate(cObject* obj)
{
    ECODEBaseApplLayer::handlePositionUpdate(obj);

    id = mobility->getId();
    time = simTime();
    speed = mobility->getSpeed();
    // Se trocou de via, limpa a tabela NR
    if (edge.compare(traciVehicle->getRoadId()) != 0)
    {
        std::cout << "Veiculo " << id << " mudou de via em " << time << std::endl;
        this->nr.clear();
    }
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
        std::cout << "Veiculo " << id << " enviando ADV em " << time << std::endl;
        ADVMessage* adv = new ADVMessage();
        populateWSM(adv);
        populateADV(adv);
        sendDown(adv);
    }
    // Se é o veículo mais no início ou no final da via, faz
    // o broadcast da mensagem NR
    if (time - lastSentNR > 1.0)
    {
        lastSentNR = time;
        NRMessage* nr = new NRMessage();
        populateWSM(nr);
        populateNR(nr);
        sendDown(nr);
        std::cout << "Veiculo " << id << " enviando NR em " << time << std::endl;
    }

    // Se é o veículio mais no início ou no final da via, gera a mensagem
    // de TMR e envia para as RSU
    std::vector<double> positions;
    for (auto const& par : nr)
    {
        positions.push_back(par.second->lanePosition);
    }
    if (((this->lanePosition >= *max_element(positions.begin(),
                                             positions.end())) 
        or (this->lanePosition <= *min_element(positions.begin(),
                                               positions.end())))
        and (time - lastSentTMR > 1.0))
    {
        lastSentTMR = time;
        TMRMessage* tmr = new TMRMessage();
        populateWSM(tmr);
        populateTMR(tmr);
        sendDown(tmr);
    }

}
