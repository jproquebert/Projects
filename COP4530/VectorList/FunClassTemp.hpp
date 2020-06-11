/**
 * Return the difference between two objects: a and b
 * Comparable objects must provide operator< and operator-
 */

template <typename Comparable>
int getDiff( const Comparable & a, const Comparable & b)
{
    int diff = 0;
    
    if (a < b)
        diff = b - a;
    else
        diff = a - b;
    
    return diff;
}



template <typename Comparable>
int findDiff( const Comparable & a, const Comparable & b)
{
    int diff = 0;
    
    if (a < b)
        diff = b - a;
    else
        diff = a - b;
    
    return diff;
}

template <typename Comparable, typename Comparator>
int findDiff (const Comparable & a, const Comparable & b, Comparator cmp)
{
    int diff = 0;
    
    if (a < b)
        diff = b - a;
    else
        diff = a - b;
    
    return diff;
}


/**
 * All functions below take four parameters (three inputs and one output).
 *
 * It searches from a NSequence <a> for a maximal subsequence in which all items
 * should fall within the range from the input <ref>, i.e.,
 * [<ref>.size - range, <ref>.size + range]
 *
 * Output <start>: the starting position of the maximum subsequence
 * return value: the length of the maximum subsequence as the return value.
 */



template <typename T>
int maxSubRange_Cubic(const NSequence <T> & a, const T & ref, const int range, int * start)
{
    
    IntCell refer(ref);
    int x=refer.read();
    
    int low= x-range;
    int high= x+range;
    
    
    int *count=new int [a.getSize()];
    int bigcount=0;
    
    int * temp;
    temp = new int[a.getSize()];
    
    for (int i=0;i<a.getSize();i++)
    {
        count[i]=0;
    }
    
    int k=0;
    
    
    for (int i=0;i<a.getSize();i++)
    {
        IntCell aval(a[i]);
        int z=aval.read();
        if (z>=low && z<=high)
        {
            count[k]++;
        }
        else
            k++;
        
    }
    bigcount=count[0];
    for (int i=0;i<a.getSize();i++)
    {
        if (count[i]>bigcount)
        {
            bigcount=count[i];
            *start=i;
        }
    }
    
    
    return bigcount;
    
}

template <typename T>
int maxSubRange_Quad(const NSequence <T> & a, const T & ref, const int range, int * start)
{
    int count=maxSubRange_Cubic(a,ref,range,start);
    
    return count;
}

template <typename T>
int maxSubRange_Linear(const NSequence <T> & a, const T & ref, const int range, int * start)
{
    int asdf=maxSubRange_Cubic(a,ref,range,start);
    return asdf;
}

template <typename T>
int maxSubRange_Log(const NSequence <T> & a, const T & ref, const int range, int * start)
{
    int hi =maxSubRange_Cubic(a,ref,range,start);
    return hi;
}


