#include <iostream>
#include "menu.h"
#include "read.h"
#include <sstream>
#define menuCount 10

using namespace std;


bool check(int a){return a>=0 && a<=menuCount;}

void menu::Run()
{
    int n;
    do{
        n = MenuPrint();
        switch(n)
        {
            case 1:
                printElement();
                break;
            case 2:
                putElement();
                break;
            case 3:
                putVector();
                break;
            case 4:
                printSize();
                break;
            case 5:
                addChesses();
                break;
            case 6:
                multiplyChesses();
                break;
            case 7:
                print();
                break;
            case 8:
                file();
                break;
            case 9:
                addSecondChess();
                break;
            case 10:
                multiplySecondChess();
                break;
            default:
                cout<<"\nEnjoy your life!!\n";
                break;

        }
    }while(n != 0);
}

int menu::MenuPrint()
{
    int choice;
    cout<<"\n****************************************\n";
    cout<<"0. Exit!\n";
    cout<<"1. Get element:\n";
    cout<<"2. Set element:\n";
    cout<<"3. Set vector:\n";
    cout<<"4. Print size of the chessboard:\n";
    cout<<"5. Add two chessboards from the console:\n";
    cout<<"6. Multiply two chessboards from the console:\n";
    cout<<"7. Print the chessboard:\n";
    cout<<"8. Print chessboard from the file:\n";
    cout<<"9. Add matrices:\n";
    cout<<"10. Multiply matrices:\n\n";

    cout<<"****************************************\n";

    ostringstream s;
    s<<"Choose a number between 0 and "<<menuCount<<"!";
    string er = s.str();
    choice=read<int>("Choose a menuitem: ", er, check);

    return choice;
}

void menu::printElement()
{
   int i, j;
   cout<<"Enter row number: ";
   cin>>i;
   cout<<"Enter column number: ";
   cin>>j;
   try
   {
       cout<<c.getElement(i, j)<<endl;
   }
   catch(chess::InvalidIndexException ex)
   {
       cout<<"Sorry, you entered wrong indexes!\n";
   }
}

void menu::putElement()
{
    int i, j, e;
    cout<<"Enter row number: ";
    cin>>i;
    cout<<"Enter column number: ";
    cin>>j;
    cout<<"Enter the element that you want to set: ";
    cin>>e;

    try
    {
        c.setElement(i, j, e);
    }
    catch(chess::InvalidIndexException ex)
    {
        cout<<"Sorry, you entered wrong indexes!\n";
    }
    cout<<c<<endl;

}

void menu::putVector()
{
    int n, e;
    vector<int> vec;
    cout<<"How many vector elements do want to store: ";
    cin>>n;

    try
    {
        for(int i=0; i<n; i++)
    {
        cin>>e;
        vec.push_back(e);
    }
    c.setVec(vec);
    cout<<"After setting vector: ";
    cout<<c;
    }
    catch(chess::InvalidVectorException ex)
    {
        cout<<"Sorry, give the proper size of vector!\n";
    }
}


void menu::printSize()
{
   cout<<"Size of the chess is: "<<c.getSize();
}

void menu::addChesses()
{
chess a;
cin>>a;
cout<<"You entered: "<<endl;
cout<<a<<endl;

chess b;
cin>>b;
cout<<"You entered: "<<endl;
cout<<b<<endl;
try
{
    cout<<"Addition of two matrices: "<<endl;
    cout<<chess::add(a, b)<<endl;
}
catch(chess::DimensionMisMatchException ex)
{
    cout<<"Two matrices with different sizes! "<<endl;
}
}


void menu::addSecondChess()
{
chess b;
cin>>b;
cout<<"You entered: "<<endl;
cout<<b<<endl;
try
{
    cout<<"Addition of two matrices: "<<endl;
    cout<<chess::add(c, b)<<endl;
}
catch(chess::DimensionMisMatchException ex)
{
    cout<<"Two matrices with different sizes! "<<endl;
}
}


void menu::multiplyChesses()
{
chess a;
cin>>a;
cout<<"You entered: "<<endl;
cout<<a<<endl;
chess b;

cin>>b;
cout<<"You entered: "<<endl;
cout<<b<<endl;
try
{
    cout<<"Multiplication of two matrices: "<<endl;
    cout<<chess::multiply(a, b);
}
catch(chess::DimensionMisMatchException ex)
{
    cout<<"Two matrices with different sizes!"<<endl;
}
}

void menu::multiplySecondChess()
{
chess b;
cin>>b;
cout<<"You entered: "<<endl;
cout<<b<<endl;
try
{
    cout<<"Multiplication of two matrices: "<<endl;
    cout<<chess::multiply(c, b);
}
catch(chess::DimensionMisMatchException ex)
{
    cout<<"Two matrices with different sizes!"<<endl;
}
}


void menu::print()
{
    cout<<"Content of the chessboard: "<<endl;
    cout<<c;
}

void menu::file()
{
    string fileName;
    cout<<"Enter the file: ";
    cin>>fileName;
        try
        {
           chess k(fileName);
           cout<<"Chessboard from the file:\n";
           cout<<k<<endl;
        }
        catch(chess::InvalidNumberException ex)
        {
            cout<<"You have less number for matrix in your file!\n";
        }
}




