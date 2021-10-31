#include <map>
#include <vector>
#include "veins/modules/messages/ADVMessage_m.h"

namespace veins {


class VEINS_API NRTableEntry
{
public:
    int id;
    double speed;
    std::string edge;
    std::string lane;
    double lanePosition;
    std::string destination;
    simtime_t time;
};


class VEINS_API NRTable
{
public:
    int num_elements;
    std::vector<NRTableEntry*> entries;

    NRTable(std::map<int, NRTableEntry*> table)
    {
        this->num_elements = table.size();
        for (auto const& par : table)
        {
            this->entries.push_back(par.second);
        }
    }
};

}