
#include <iostream>
#include "Cell.h"

IntCell::IntCell(int initial)
{
    storedValue=initial;
}
int IntCell::size() const
{
    return storedValue;
}
int IntCell::read() const
{
    return storedValue;
}
void IntCell::write(int x)
{
    storedValue=x;
}
int IntCell::operator-(const IntCell &x) const
{
    return (read()-x.read());
}
bool IntCell::operator< (const IntCell &x) const
{
    if (read()<x.read())
    {
        return true;
    }
    else
    {
        return false;
    }
}
