#pragma once

#include <exception>
#include <fstream>
#include "datamodels/donor.hpp"
#include "datastructures/maxheap.hpp"
#include "datastructures/date.hpp"

using namespace std;

class DonorDB
{
    struct Collection
    {
        MaxHeap<int, Donor> o, a, b, ab;
    } pos, neg;

public:
    DonorDB()
    {
        // populating the collection for demo.

        MaxHeap<int, Donor> *heaps[] = {&pos.o, &pos.a, &pos.b, &pos.ab, &neg.o, &neg.a, &neg.b, &neg.ab};
        string fnames[] = {"donordb_opos.txt", "donordb_apos.txt", "donordb_bpos.txt", "donordb_abpos.txt",
                           "donordb_oneg.txt", "donordb_aneg.txt", "donordb_bneg.txt", "donordb_abneg.txt"};
        for (int i = 0; i < 8; i++)
        {
            ifstream file("data/" + fnames[i], ios::in);
            if (!file)
                continue;
            MaxHeap<int, Donor> *heap = heaps[i];
            string record;
            while (std::getline(file, record))
            {
                // file.read(reinterpret_cast<char *>(&donor), sizeof(Donor));
                // file.seekg(sizeof(Donor), ios::cur);
                Donor *donor = new Donor(record);
                heap->insert(getInterval(donor->lastDontationDate), *donor);
            }
            file.close();
        }
    }

    ~DonorDB()
    {
        // saving the collection
        MaxHeap<int, Donor> *heaps[] = {&pos.o, &pos.a, &pos.b, &pos.ab, &neg.o, &neg.a, &neg.b, &neg.ab};
        string fnames[] = {"donordb_opos.txt", "donordb_apos.txt", "donordb_bpos.txt", "donordb_abpos.txt",
                           "donordb_oneg.txt", "donordb_aneg.txt", "donordb_bneg.txt", "donordb_abneg.txt"};
        for (int i = 0; i < 8; i++)
        {
            ofstream file("data/" + fnames[i], ios::out);
            if (!file)
            {
                cout << "Error writing to file." << endl;
                continue;
            }
            MaxHeap<int, Donor> *heap = heaps[i];
            while (!heap->isEmpty())
            {
                Donor *donor = heap->getMax();
                heap->deleteMax();
                string ser = donor->Serialize() + "\n";
                file << ser;
            }
        }
    }

    class DonorNotFoundException : public exception
    {
        const char *what()
        {
            return "Error: Donor for the requested type not found.";
        };
    };

    Donor *getDonor(std::string type, char antigen)
    {
        Collection *col;
        if (antigen == '+')
            col = &pos;
        else
            col = &neg;

        MaxHeap<int, Donor> *heap;
        if (type == "O")
            heap = &col->o;
        if (type == "A")
            heap = &col->a;
        if (type == "B")
            heap = &col->b;
        if (type == "AB")
            heap = &col->ab;

        if (heap->isEmpty())
            throw DonorNotFoundException();
        Donor *temp = heap->getMax();
        heap->deleteMax();
        return temp;
    }

    void addDonor(Donor d)
    {
        Collection *col;
        if (d.antigen == '+')
            col = &pos;
        else
            col = &neg;

        MaxHeap<int, Donor> *heap;
        if (d.type == "O")
            heap = &col->o;
        if (d.type == "A")
            heap = &col->a;
        if (d.type == "B")
            heap = &col->b;
        if (d.type == "AB")
            heap = &col->ab;

        heap->insert(getInterval(d.lastDontationDate), d);
    }
};
