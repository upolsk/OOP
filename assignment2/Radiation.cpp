#include "radiation.h"
#include "plant.h"
#include <iostream>

using namespace std;

// implementation of Radiation class
void Radiation::changeDemand(const bool findDemand, const int demand)
{

    if(findDemand)
    {
        alphaDemand+=demand;
    }
    else
    {
        deltaDemand+=demand;
    }

}

void Radiation::reset()
{
    Radiation::alphaDemand=0;
    Radiation::deltaDemand=0;
}


Radiation* Radiation::findRadiation()
{
    cout<<"Alpha demand: "<<alphaDemand<<endl;
    cout<<"Delta demand: "<<deltaDemand<<endl;
    if((alphaDemand - deltaDemand) >= 3)
    {
        return Alpha::instance();
    }
    else if((deltaDemand-alphaDemand) >= 3)
    {
        return Delta::instance();
    }
    else
    {
        return noRadiation::instance();
    }


}

// implementation of Alpha class
Alpha* Alpha::_instance = nullptr;
Alpha* Alpha::instance()
{
    if(_instance == nullptr)
    {
        _instance = new Alpha();
    }
    return _instance;
}
void Alpha::destroy()
{
    if ( nullptr!=_instance )
    {
        delete _instance;
        _instance = nullptr;
    }
}

Radiation* Alpha::react(Wombleroot *w)
{
    if(w->isAlive())
    {
        w->changeLevel(2);
    }

    if(w->nutrientLevel()>10)
    {
        w->die();
    }
    if(w->isAlive())
    {
        changeDemand(true, 10);
    }
    return this;
}

Radiation* Alpha::react(Wittentoot *w)
{
    if(w->isAlive())
    {
        w->changeLevel(-3);
    }
    if(w->isAlive() && w->nutrientLevel() < 5)
    {
        changeDemand(false,4);
    }
    else if (w->nutrientLevel()>=5 && w->nutrientLevel()<=10)
    {
        changeDemand(false,1);
    }
    return this;
}

Radiation* Alpha::react(Woreroot *w)
{
    if(w->isAlive())
    {
        w->changeLevel(1);
    }
    return this;
}

// implementation of Delta class
Delta* Delta::_instance = nullptr;
Delta* Delta::instance()
{
    if(_instance == nullptr)
    {
        _instance = new Delta();
    }
    return _instance;
}
void Delta::destroy()
{
    if ( nullptr!=_instance )
    {
        delete _instance;
        _instance = nullptr;
    }
}

Radiation* Delta::react(Wombleroot *w)
{
    if(w->isAlive())
    {
        w->changeLevel(-2);
        changeDemand(true, 10);
    }

    if(w->nutrientLevel()>10)
    {
        w->die();
    }

    return this;
}

Radiation* Delta::react(Wittentoot *w)
{
    if(w->isAlive())
    {
        w->changeLevel(4);
    }

    if(w->isAlive() && w->nutrientLevel() < 5)
    {
        changeDemand(false,4);
    }
    else if (w->nutrientLevel()>=5 && w->nutrientLevel()<=10)
    {
        changeDemand(false,1);
    }
    return this;
}

Radiation* Delta::react(Woreroot *w)
{
    if(w->isAlive())
    {
        w->changeLevel(1);
    }

    return this;
}

// implementation of noRadiation class
noRadiation* noRadiation::_instance = nullptr;
noRadiation* noRadiation::instance()
{
    if(_instance == nullptr)
    {
        _instance = new noRadiation();
    }
    return _instance;
}
void noRadiation::destroy()
{
    if ( nullptr!=_instance )
    {
        delete _instance;
        _instance = nullptr;
    }
}

Radiation* noRadiation::react(Wombleroot *w)
{
    if(w->isAlive())
    {
        w->changeLevel(-1);
        changeDemand(true, 10);
    }

    if(w->nutrientLevel()>10)
    {
        w->die();
    }

    return this;
}

Radiation* noRadiation::react(Wittentoot *w)
{
    if(w->isAlive())
    {
        w->changeLevel(-1);
    }

    if(w->isAlive() && w->nutrientLevel() < 5)
    {
        changeDemand(false,4);
    }
    else if (w->nutrientLevel()>=5 && w->nutrientLevel()<=10)
    {
        changeDemand(false,1);
    }
    return this;
}

Radiation* noRadiation::react(Woreroot *w)
{
    if(w->isAlive())
    {
        w->changeLevel(-1);
    }

    return this;
}
