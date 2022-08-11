#ifndef CHESS_H
#define CHESS_H
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;

class chess
{
    public:

    ///Constructors
    chess();
    chess(int size);
    chess(const string &fileName);

    ///Getters
    int getElement(int i, int j) const;
    int getSize() const {return _size;}

    ///Setter
    void setElement(int i, int j, int e);
    void setElToVec(int i, int j);
    void setSize(int sz) {_size = sz;}
    void setVec(const vector <int> &vec);


    ///Static methods
    static chess add(const chess &a, const chess &b);
    static chess multiply(const chess &a, const chess &b);

    ///Operator overloading
    friend ostream &operator<<(ostream &os, const chess &c);
    friend istream &operator>>(istream &is, chess &c);

    ///Exceptions
    class InvalidIndexException : public exception {};
    class InvalidVectorException : public exception {};
    class DimensionMisMatchException : public exception {};
    class InvalidNumberException : public exception {};
    //enum Exceptions{InvalidIndexException,InvalidVectorException, DimensionMisMatchException, InvalidNumberException};



    private:
    ///Attributes
        int _size;
        vector <int> _vec;

    ///Methods
    int ind(int i, int j) const;
    double calcSizeFromLength(unsigned int size);
    bool insideChessMatrix(int i, int j) const;

};

#endif // CHESS_H
