/*2. At every competition of the National Angling Championship, the results of the
competitors were recorded and put into a text file. Every line of the file contains the name
of the angler the ID of the competition (string without spaces), and the species and the
size of the caught fishes (pair of a string without spaces and a natural number). Data is
separated by space or tab. The lines of the file are ordered by contest ID. The file is
assumed to be in the correct form. Sample line in the file:
Peter LAC0512 carp 45 carp 53 catfish 96*/


#include <iostream>
#include "library/summation.hpp"
#include <sstream>
#include "library/stringstreamenumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/counting.hpp"

using namespace std;

/*(1) Give the angler who has caught the most fishes on one contest. Give the ID of the
contest and the number of caught fishes, too.*/
//Summation, Max Search -> enumerators

struct Fish
{
    string name;
    int size;
    friend istream &operator>>(istream &is, Fish &f)
    {
        is>>f.name>>f.size;
        return is;
    }
};

class MySummation : public Summation<Fish, int>
{
    protected:
    int func(const Fish &f) const override { return 1;}
    int neutral() const override { return 0;}
    int add(const int &a, const int &b) const override { return a + b; }
};

struct Competetion
{
    string name;
    string ID;
    int sum;
    friend istream& operator>>(istream &is, Competetion &c)
    {
        string line;
        getline(is, line, '\n');
        stringstream ss(line);
        ss>>c.name>>c.ID;

        StringStreamEnumerator<Fish> myenor(ss);
        MySummation pr;
        pr.addEnumerator(&myenor);
        pr.run();
        c.sum = pr.result();

        return is;
    }
};

class MyMaxSearch : public MaxSearch<Competetion, int>
{      protected:
       int func(const Competetion& c) const override{ return c.sum;}
};

/////////////////////////////////////////////////////////////////////////////////
//(2) How many contests there are where no fishes were caught?*/
//Summation, Summation, Counting ->custom enumerators



class MyCounting : public Summation<Competetion, int>
{    private:
     string m_name;
     public:
     MyCounting(const string &name) : m_name(name) {}
     protected:
    int func(const Competetion &f) const override { return f.sum;}
    int neutral() const override { return 0;}
    int add(const int &a, const int &b) const override { return a + b; }

     bool whileCond(const Competetion &con) const override{ return con.ID == m_name;}
     void first() override {}
};
class ContestEnumerator : public Enumerator<Competetion>
{
    private:
    SeqInFileEnumerator<Competetion> *f;
    Competetion contest;
    bool m_end;
    public:
    ContestEnumerator(const string &fileName)
    {
        f = new SeqInFileEnumerator<Competetion>(fileName);
    }
    ~ContestEnumerator() { delete f;}
    void first() override{ f->first(); this->next();}
    void next() override
    {
        if(m_end = f->end()) return;
        contest.ID = f->current().ID;
        MyCounting pr(contest.ID);
        pr.addEnumerator(f);
        pr.run();
        contest.sum = pr.result();
    }
    Competetion current() const override{ return this->contest;}
    bool end() const override { return this->m_end;}
};
class Write : public Counting<Competetion>
{
    protected:
        bool cond(const Competetion &c) const override {
            return c.sum == 0;
        }
};


/////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    try
    {
     string file;
     if(argc > 1) { file = argv[1];}
     else {file = "inp3.txt";}

     SeqInFileEnumerator<Competetion> enor(file);
     MyMaxSearch my;
     my.addEnumerator(&enor);
     my.run();

     if(my.found())
     {
         cout<<"Task A: \n";
        cout<<my.optElem().name<<" has caught most fishes!\n";
        cout<<"Contest ID: "<<my.optElem().ID<<endl;
        cout<<"Number of caught fishes: "<<my.opt()<<endl;}
     else{cout<<"File is empty!\n";}
    }
    catch(SeqInFileEnumerator<Competetion>::Exceptions e)
    {
        cerr<<"File is not found!\n";
    }
    cout<<"\n";
    cout<<"////////////////////////////////////////////////////////////////////////////////"<<endl;
    cout<<"\n";

    try
    {
     string file;
     if(argc > 1) { file = argv[1];}
     else {file = "inp3.txt";}
     ContestEnumerator enor(file);
     Write my;
     my.addEnumerator(&enor);
     my.run();
    cout<<"Task B: \n";
    cout<<"Number of contests where no fishes were caught: "<<my.result()<<endl<<endl;
    }
    catch(SeqInFileEnumerator<Competetion>::Exceptions e)
    {
        cerr<<"File is not found!\n";
    }
    return 0;
}
