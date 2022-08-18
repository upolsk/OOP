#pragma once
#include <iostream>
using namespace std;

class Wombleroot;
class Wittentoot;
class Woreroot;


class Radiation
{
public:

    virtual Radiation* react(Wombleroot *w) = 0;
    virtual Radiation* react(Wittentoot *w) = 0;
    virtual Radiation* react(Woreroot   *w) = 0;
    virtual ~Radiation() {}

    Radiation* findRadiation();
    void changeDemand(const bool findDemand, const int demand);
    void reset();

    int getAlphaDemand() const {return alphaDemand;}
    int getDeltaDemand() const {return deltaDemand;}

private:
    int alphaDemand = 0;
    int deltaDemand = 0;
};



// class of Alpha radiation
class Alpha : public Radiation
{
public:
    static Alpha* instance();
    Radiation* react(Wombleroot *w) override;
    Radiation* react(Wittentoot *w) override;
    Radiation* react(Woreroot   *w) override;
    static void destroy() ;
protected:
    Alpha() {}
private:
    static Alpha* _instance;
};

// class of Delta radiation
class Delta : public Radiation
{
public:
    static Delta* instance();
    Radiation* react(Wombleroot *w) override;
    Radiation* react(Wittentoot *w) override;
    Radiation* react(Woreroot   *w) override;
    static void destroy() ;
protected:
    Delta() {}
private:
    static Delta* _instance;
};

// No radiation class
class noRadiation : public Radiation
{
public:
    static noRadiation* instance();
    Radiation* react(Wombleroot *w) override;
    Radiation* react(Wittentoot *w) override;
    Radiation* react(Woreroot   *w) override;
    static void destroy() ;
protected:
    noRadiation() {}
private:
    static noRadiation* _instance;
};
