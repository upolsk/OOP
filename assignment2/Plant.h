#pragma once


#include <iostream>
#include "Radiation.h"

using namespace std;


class Plant
{


protected:

    string name;
    int nutLevel;
    Plant (const string &n, int e) :name(n), nutLevel(e) {}


public:
    bool isAlive() const
    {
        return nutLevel > 0;
    }


    string getName() const
    {
        return name;
    }

    int nutrientLevel() const
    {
        return nutLevel;
    }


    void changeLevel(int e)
    {
        nutLevel+= e;
    }

     void die()
    {
        nutLevel=0;
    }


    virtual void changeNextDay(Radiation* &r)=0;
    virtual ~Plant () {}
};


class Wombleroot : public Plant
{
public:
    Wombleroot(const string &n, int e = 0) : Plant(n, e) {}
    void changeNextDay(Radiation* &r) override
    {
        r=r->react(this);
    }
};

class Wittentoot : public Plant
{
public:
    Wittentoot(const string &n, int e = 0) : Plant(n, e) {}
    void changeNextDay(Radiation* &r) override
    {
        r=r->react(this);

    }
};

class Woreroot : public Plant
{
public:
    Woreroot(const string &n, int e = 0) : Plant(n, e) {}
    void changeNextDay(Radiation* &r) override
    {
        r=r->react(this);
    }
};



