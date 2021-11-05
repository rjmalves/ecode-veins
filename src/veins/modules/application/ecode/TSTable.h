#include <map>
#include <vector>

namespace veins {


class VEINS_API TSTableEntry
{
public:
    std::string edge;
    int senderVehicleID;
    double edgeAverageSpeed;
    double edgeDensity;
    double edgeTravelTime;
    simtime_t time;
};


class VEINS_API TSTable
{
public:
    int num_elements;
    std::vector<TSTableEntry*> entries;

    TSTable(std::map<int, TSTableEntry*> table)
    {
        this->num_elements = table.size();
        for (auto const& par : table)
        {
            this->entries.push_back(par.second);
        }
    }
};

}