#include "chess.h"
///Implementation of constructors
chess::chess()
{
    _size = 4;
    _vec = {1, 2, 3, 4, 5, 6, 7, 8};
}

chess::chess(int size)
{
    _size = size;
    _vec.resize(ceil((size*size)/2.0), 0);
}

chess::chess(const string &fileName)
{
      fstream f(fileName);
      if(f.fail())
      {
          _size = 0;
          _vec.clear();
       }
       else
       {
           int e;
           while(f>>e)
           {
              _vec.push_back(e);
           }
           double n = calcSizeFromLength(_vec.size());
           if(n == floor(n))
           {
               _size = n;
           }
           else
           {
               throw InvalidNumberException();
           }
        }
    }

///Implementation of private methods
int chess::ind(int i, int j) const
{
    return ((_size * i )+ j)/2;

}

double chess::calcSizeFromLength(unsigned int size)
{
    if(size% 2 ==0)
    return 2 * sqrt(size/2);
    else
        return sqrt((size * 2) - 1);
}

bool chess::insideChessMatrix(int i, int j) const
{
    if (i < _size && j < _size && i >= 0 && j >= 0) {
        return(i+j)%2==0;
    }else {
        throw InvalidIndexException();
    }
}


///Implementation of getters
int chess::getElement(int i, int j) const
{
    if(insideChessMatrix(i, j))
    {
        return _vec[ind(i, j)];
    }
    else if(0<=i && i<_size && 0<=j && j<_size)
    {
        return 0;
    }
    else
    {
        throw InvalidIndexException();
    }
}


///Implementation of setters
void chess::setVec(const vector <int> &vec)
{
    double n = calcSizeFromLength(vec.size());
    if(n == floor(n))
    {
        _size = n;
        _vec = vec;
    }
    else
    {
        throw InvalidVectorException();
    }
}

void chess::setElement(int i, int j, int e)
{
    if(insideChessMatrix(i, j))
    {
        _vec[ind(i, j)] = e;
    }
    else
    {
       throw InvalidIndexException();
    }
}

void chess::setElToVec(int i, int e)
{
    _vec[i] = e;
}

///Implementation of static methods
chess chess::add(const chess &a, const chess &b)
{
    if(a.getSize() == b.getSize())
    {
        chess sum(a._size);

        for(int i = 0; i<a._vec.size(); i++)
        {
            sum._vec[i] =  a._vec[i] + b._vec[i];
        }
        return sum;
    }
    else
    {
        throw DimensionMisMatchException();
    }
}

chess chess::multiply(const chess& a,const chess& b)
{
    if (a.getSize() == b.getSize())
    {
        chess mul(a.getSize());

        for (int i=0;i<a._size;i++)
        {
            for (int j=0;j<a._size;j++)
            {
                if (a.insideChessMatrix(i,j))
                {
                    for (int k=0; k<a._size;k++)
                    {
                        mul.setElement(i,j,mul.getElement(i,j)+a.getElement(i,k)*b.getElement(k,j));
                    }
                }
            }
        }
        return mul;
    }
    else
    {
        throw DimensionMisMatchException();
    }
}
///Implementation of operator overloading
ostream &operator<<(ostream &os, const chess &m)
{
    os<<"Chess size: "<<m.getSize()<<"x"<<m.getSize()<<endl;
    for(int i=0; i<m.getSize(); i++)
    {
        for(int j=0; j<m.getSize(); j++)
        {
            os<<m.getElement(i, j)<<" ";
        }
        os<<endl;
    }
    return os;
}

istream &operator>>(istream &is, chess &a) {
  int size, e;
  cout<<"Give a size of matrix: "<<endl;
  is>>size;
  a.setSize(size);
  a._vec.resize(ceil((size*size )/ 2.0), 0);
  cout << "Enter " << ceil((size * size) / 2.0) << " elements: "<<endl;
  for (int i = 0; i < ceil(size*size / 2.0); i++)
  {
    is >> e;
    a.setElToVec(i, e);
  }
  return is;
}

