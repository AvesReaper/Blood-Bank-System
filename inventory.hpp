#include <map>
#include "datastructures/queue.hpp"
#include "datamodels/bloodunit.hpp"

using namespace std;

class Inventory
{
public:
    map<std::string, int> counts = {{"A+", 0}, {"B+", 0}, {"AB+", 0}, {"O+", 0}, {"A-", 0}, {"B-", 0}, {"AB-", 0}, {"O-", 0}};

    map<std::string, Queue<BloodUnit> *> queues; // = {{"A+", new Queue<BloodUnit>}, {"B+", new Queue<BloodUnit>}, {"AB+", new Queue<BloodUnit>}, {"O+", new Queue<BloodUnit>}, {"A-", new Queue<BloodUnit>}, {"B-", new Queue<BloodUnit>}, {"AB-", new Queue<BloodUnit>}, {"O-", new Queue<BloodUnit>}};

    Inventory()
    {
        string qnames[] = {"O+", "A+", "B+", "AB+", "O-", "A-", "B-", "AB-"};
        string fnames[] = {"inv_opos.dat", "inv_apos.dat", "inv_bpos.dat", "inv_abpos.dat",
                           "inv_oneg.dat", "inv_aneg.dat", "inv_bneg.dat", "inv_abneg.dat"};
        for (int i = 0; i < 8; i++)
        {
            Queue<BloodUnit> *queue = new Queue<BloodUnit>;
            queues[qnames[i]] = queue;
            ifstream file("data/" + fnames[i], ios::in);
            if (!file)
                continue;
            string record;
            while (std::getline(file, record))
            {
                BloodUnit unit(record);
                queue->enqueue(unit);
                counts[qnames[i]] += 1;
            }
            file.close();
        }
    }

    ~Inventory()
    {
        string qnames[] = {"O+", "A+", "B+", "AB+", "O-", "A-", "B-", "AB-"};
        string fnames[] = {"inv_opos.dat", "inv_apos.dat", "inv_bpos.dat", "inv_abpos.dat",
                           "inv_oneg.dat", "inv_aneg.dat", "inv_bneg.dat", "inv_abneg.dat"};
        for (int i = 0; i < 8; i++)
        {
            ofstream file("data/" + fnames[i], ios::out);
            if (!file)
                continue;
            Queue<BloodUnit> *queue = this->queues[qnames[i]];
            while (!queue->content.isEmpty())
            {
                BloodUnit unit = queue->dequeue();
                string ser = unit.Serialize() + "\n";
                file.write(ser.c_str(), ser.length());
            }
            file.close();
        }
    }
};