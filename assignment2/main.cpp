#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "plant.h"
#include "radiation.h"

using namespace std;

void printPlant(Plant* plant)
{
    cout << plant->getName() << "        " <<plant->nutrientLevel() <<endl;
}

void printRadiation(Radiation* radiations)
{
    if (radiations == Alpha::instance())
    {
        cout << "Alpha Radiation";
    }
    else if (radiations == Delta::instance() )
    {
        cout << "Delta Radiation";
    }
    else if  (radiations == noRadiation::instance() )
    {
        cout<< "No Radiation";
    }
    cout << endl;
}

void create(string fileName,vector<Plant*> &p, vector<Radiation*> &r)
{


    ifstream f(fileName);
    if(f.fail())
    {
        cout<<"Invalid file!\n";
        exit(1);
    }

    int n;
    f >> n;
    p.resize(n);
    for( int i=0; i<n; ++i )
    {
        string name;
        string type;
        int level;
        f >> name >> type >> level;

        if (type=="wom")
        {
            p[i] = new Wombleroot(name, level);
        }
        else if (type=="wit")
        {
            p[i] = new Wittentoot(name, level);
        }
        else if (type=="wor")
        {
            p[i] = new  Woreroot(name, level);
        }
    }

    r.clear();
    //first day always starts with noRadiation
    r.push_back(noRadiation::instance());
}

bool check(vector<Radiation*> &r)
{
    for(int i=0; i<(int)r.size(); i++)
    {
        if(r[i] == noRadiation::instance() && r[i+1] == noRadiation::instance() && r[i]==r[i+1])
        {
            return false;
        }
    }
    return true;
}

void ecosystem(vector<Plant*> &plant, vector<Radiation*> &radiations, vector<string>& alive)
{
    alive.clear();
    try
    {
        int day = 0;
        while(check(radiations))
        {
            cout << "DAY: " << day+1 << endl;
            cout<<"RADIATION TYPE: ";
            printRadiation(radiations[day]);
            radiations[day]->reset();
            cout<<endl;
            cout<<"PLANT NAME    NUTRIENT LEVEL"<<endl;
            for(unsigned int i = 0; i < plant.size(); ++i)
            {
                plant[i]->changeNextDay(radiations[day]);
                printPlant(plant[i]);
            }
            cout<<endl;
            //finds radiation type for the next day and adds to radiation vector
            radiations.push_back(radiations[day]->findRadiation());
            cout<<endl;
            cout << "Next Day Radiation will be: ";
            printRadiation(radiations[day + 1]);
            cout<<endl;
            cout<<"********************************************"<<endl;
            cout << endl << endl; // DEBUG

        //loop over each plant, check if it's alive or not, if alive then add plant name to the vector
        for(unsigned int i=0; i<plant.size(); ++i)
        {
            int l=0;
            if(plant[i]->isAlive() && plant[i]->nutrientLevel()> l )
            {
                alive.clear();
                l=plant[i]->nutrientLevel();
                alive.push_back(plant[i]->getName());

            }
        }
        day++;

        }

    }
    catch(exception &e)
    {
        cout << e.what() << endl;
    }
}

//memory
void destroy(vector<Plant*> &plant)
{
    for(int i=0; i<(int)plant.size(); ++i) delete plant[i];
}


void destroyRadiations()
{
    Alpha::destroy();
    Delta::destroy();
    noRadiation::destroy();
}
#define NORMAL_MODE
#ifdef NORMAL_MODE
#define NORMAL_MODE

int main()
{


    vector<Plant*> plants;
    vector<Radiation*> radiations;
    int days;
    string fileName;
    cout<<"Enter the file: ";
    cin>>fileName;
    cout<<endl;
    create(fileName, plants, radiations);

    vector<string> alive;
    ecosystem(plants, radiations, alive);

    destroy(plants);
    destroyRadiations();
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE("Test1", "empty.txt")
{
    vector<Plant*> plants;
    vector<Radiation*> radiations;
    vector<string> alive;


    create("empty.txt",plants, radiations);
    ecosystem(plants, radiations, alive);
    CHECK(alive.size() == 0);
    destroy(plants);

}

TEST_CASE("Test2", "inp.txt")
{
    vector<Plant*> plants;
    vector<Radiation*> radiations;
    vector<string> alive;

    create("inp.txt",plants, radiations);
    ecosystem(plants, radiations, alive);
    CHECK(alive.size() == 1);
    CHECK(alive[0] == "Big");

    CHECK(radiations[0] == noRadiation::instance());
    CHECK(radiations[1] == Alpha::instance());
    CHECK(radiations[2] == Alpha::instance());
    CHECK(radiations[3] == Alpha::instance());
    CHECK(radiations[4] == Alpha::instance());
    CHECK(radiations[5] == noRadiation::instance());
    CHECK(radiations[6] == noRadiation::instance());


    CHECK(plants[0]->isAlive() == false);
    CHECK(plants[1]->isAlive() == false);
    CHECK(plants[2]->isAlive() == true);

    CHECK(plants[0]->getName() == "Hungry");

    destroy(plants);
    destroyRadiations();
}


TEST_CASE("Test3", "")
{

    vector<Plant*> plants;
    vector<Radiation*> radiations;
    vector<string> alive;

    plants.clear();
    radiations.clear();
    plants.push_back(new Wombleroot("Upol", 5));
    radiations.push_back(Alpha::instance());
    radiations.push_back(Delta::instance());
    radiations.push_back(noRadiation::instance());
    ecosystem(plants, radiations, alive);

    CHECK(plants[0]->isAlive() == false);
    CHECK(radiations[0] == Alpha::instance());
    CHECK(radiations[1] == Delta::instance());
    CHECK(radiations[2] == noRadiation::instance());

    destroy(plants);


    plants.clear();
    radiations.clear();
    plants.push_back(new Wittentoot("Asel", 7));
    radiations.push_back(Alpha::instance());
    radiations.push_back(Delta::instance());
    radiations.push_back(noRadiation::instance());
    ecosystem(plants, radiations, alive);

    CHECK(plants[0]->isAlive() == true);
    CHECK(radiations[0] == Alpha::instance());
    CHECK(radiations[1] == Delta::instance());
    CHECK(radiations[2] == noRadiation::instance());

    destroy(plants);


    plants.clear();
    radiations.clear();
    plants.push_back(new Woreroot("Zhainagul", 10));
    radiations.push_back(Alpha::instance());
    radiations.push_back(Delta::instance());
    radiations.push_back(noRadiation::instance());
    ecosystem(plants, radiations, alive);

    CHECK(plants[0]->isAlive() == true);
    CHECK(radiations[0] == Alpha::instance());
    CHECK(radiations[1] == Delta::instance());
    CHECK(radiations[2] == noRadiation::instance());

    destroy(plants);


    plants.clear();
    radiations.clear();
    plants.push_back(new Woreroot("Someone", -5));
    radiations.push_back(Alpha::instance());
    radiations.push_back(Delta::instance());
    radiations.push_back(noRadiation::instance());
    ecosystem(plants, radiations, alive);

    CHECK(plants[0]->isAlive() == false);
    CHECK(radiations[0] == Alpha::instance());
    CHECK(radiations[1] == Delta::instance());
    CHECK(radiations[2] == noRadiation::instance());

    destroy(plants);

    destroyRadiations();
}

TEST_CASE("Test4", "")
{

    vector<Plant*> plants;
    vector<Radiation*> radiations;
    vector<string> alive;

    plants.clear();
    radiations.clear();
    plants.push_back(new Wombleroot("he", 1));
    radiations.push_back(Alpha::instance());
    radiations.push_back(Delta::instance());
    ecosystem(plants, radiations, alive);

    CHECK(plants[0]->isAlive() == false);
    CHECK(radiations[0] == Alpha::instance());
    CHECK(radiations[1] == Delta::instance());

    destroy(plants);


    plants.clear();
    radiations.clear();
    plants.push_back(new Wombleroot("me", -5));
    radiations.push_back(Alpha::instance());
    radiations.push_back(Delta::instance());
    ecosystem(plants, radiations, alive);

    CHECK(plants[0]->isAlive() == false);
    CHECK(radiations[0] == Alpha::instance());
    CHECK(radiations[1] == Delta::instance());

    destroy(plants);

    plants.clear();
    radiations.clear();
    plants.push_back(new Wittentoot("you", 10));
    radiations.push_back(noRadiation::instance());
    radiations.push_back(Delta::instance());
    ecosystem(plants, radiations, alive);

    CHECK(plants[0]->isAlive() == true);
    CHECK(radiations[0] == noRadiation::instance());
    CHECK(radiations[1] == Delta::instance());
    CHECK(radiations[0]->findRadiation()== noRadiation::instance() );


    destroyRadiations();
}


TEST_CASE("Test5", "inp1.txt")
{
     vector<Plant*> plants;
    vector<Radiation*> radiations;
    vector<string> alive;

    create("inp1.txt",plants, radiations);
    ecosystem(plants, radiations, alive);
    CHECK(alive.size() == 1);
    CHECK(alive[0] == "Satisfied");


    CHECK(radiations[3]->getAlphaDemand() == 0);
    CHECK(radiations[3]->getDeltaDemand() == 0);
    CHECK(radiations[4]->getAlphaDemand() == 0);
    CHECK(radiations[4]->getDeltaDemand() == 0);

}

#endif // NORMAL_MODE
