#include <string>
#include <iostream>
#include <algorithm>
#include <chrono>
#include<vector>

#include "donordb.hpp"
#include "inventory.hpp"

using namespace std;
using namespace std::chrono;

int main()
{
    cout << "WELCOME" << endl;

    DonorDB donors;
    Inventory inv;
    int choice = 0;

    vector<int> values(10000);
 
    // Generate Random values
    auto f = []() -> int { return rand() % 10000; };
 
    // Fill up the vector
    generate(values.begin(), values.end(), f);
 
    // Get starting timepoint
    auto start = high_resolution_clock::now();
 
    // Call the function, here sort()
    sort(values.begin(), values.end());
 
    // Get ending timepoint
    auto stop = high_resolution_clock::now();
 
    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl;




    while (choice != 3)
    {
        cout << "Enter your choice: \n\t1.Donor Registration \n\t2.Request Blood \n\t3.QUIT" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int age, count;
            long long phno;
            string name, bg;
            cout << "THANK YOU for choosing to become a part of us\n";
            cout << "Enter your following details please (NAME, AGE, BLOOD GROUP (A+, AB-), PHONE NO.):\n";
            cin >> name >> age >> bg >> phno;
            char anti = bg[bg.length() - 1];
            bg.pop_back();
            Donor donor(name, age, bg, anti, phno);
            donors.addDonor(donor);
            cout << "Successfully registered." << endl;
            break;
        }
        case 2:
        {
            std::string bg;
            cout << "PLEASE ENTER THE BLOOD GROUP YOU ARE SEARCHING FOR (A+, AB-, etc.): ";
            cin >> bg;
            cout << "CHECKING FOR AVAILABILITY OF BLOOD PACKS..." << endl;

            // CHECK THE BLOOD PACK TREE
            int count;
            cout << "PLEASE ENTER THE NO. OF PACKS YOU REQUIRE: ";
            cin >> count;

            // IF AVAILABLE
            if (inv.counts[bg] >= count)
            {
                cout << "BLOOD PACKS ARE AVAILABLE." << endl;
                for (int i = 0; i < count; i++)
                {
                    BloodUnit unit = inv.queues[bg]->dequeue();
                    cout << "\tDonor ID: #" << unit.donorId << "Date: " << unit.donationDate << endl;
                }
                inv.counts[bg] -= count;
            }
            else
            {
                cout << "BLOOD PACKS ARENT AVAILABLE FOR THE SEARCH YOU MADE, BUT YOU CAN CONTACT ONE OF OUR DONORS AND REQUEST THEM...\nTHEIR DETAILS ARE LISTED BELOW:" << endl;
                char anti = bg[bg.length() - 1];
                bg.pop_back();

                try
                {   
                    auto start = high_resolution_clock::now();
                    Donor *donor = donors.getDonor(bg, anti);
                    

                    cout << "\tName: " << donor->name << endl;
                    cout << "\tId: #" << donor->id << endl;
                    cout << "\tBlood Group: " << donor->type << donor->antigen << endl;
                    cout << "\tLast donation date: " << donor->lastDontationDate << endl;
                    cout << "\tPh. no.: " << donor->phoneNo << endl;
                    
                    donor->lastDontationDate = Date();
                    donors.addDonor(*donor);

                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);

                    cout << "Time taken by function: "
                    << duration.count() << " microseconds" << endl;
                }
                catch (DonorDB::DonorNotFoundException &ex)
                {
                    cout << "SORRY, DONOR DETAILS FOR THE REQUESTED BLOOD TYPE NOT FOUND." << endl;
                }
            }
            break;
        }
        case 3: 
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "PLEASE ENTER A VALID CHOICE...";
        }
    }
    cout << "HOPE YOU FOUND THE HELP YOU NEEDED ..." << endl;

    return 0;
}

