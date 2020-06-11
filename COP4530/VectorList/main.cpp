#include <iostream>
#include "Cell.h"
#include "NSequence.h"
#include "FunClassTemp.h"

using namespace std;

int main( )
{
    NSequence <IntCell>     v1 (20); /* one item added for an empty sequence */
    for( int i = 0; i < v1.getSize(); i++ ) {
        v1[i].write(8*i+1);
    }
    cout<<endl;
    cout << "Sequence has "<< v1.getSize() << " items:";
    v1.printout(0, v1.getSize() - 1);
    
    int begin = 0;
    IntCell x(30);
    int sub = maxSubRange_Cubic<IntCell>(v1, x, 20, &begin);
    cout<<endl;
    cout << "Cubic func found "<< sub << " items:";
    v1.printout(begin, begin+sub -1 );
    
    begin = 0;
    sub = maxSubRange_Quad <IntCell>(v1, x, 20, &begin);
    cout<<endl;
    cout << "Quadratic func found "<< sub << " items:";
    v1.printout(begin, begin+sub -1 );
    
    begin = 0;
    sub = maxSubRange_Linear<IntCell>(v1, x, 20, &begin);
    cout<<endl;
    cout << "Linear func found "<< sub << " items:";
    v1.printout(begin, begin+sub -1 );
    
    begin = 0;
    sub = maxSubRange_Log<IntCell>(v1, x, 20, &begin);
    cout<<endl;
    cout << "Log func found "<< sub << " items:";
    v1.printout(begin, begin+sub -1 );
    
    return 0;
}



