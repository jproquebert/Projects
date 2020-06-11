/*
 Jean Roquebert
 COP4530
 Fall 2019
 due oct 29, 2019
 Stack.hpp, project #3
 */
template<typename T>
Stack<T>::Stack(int initSize) /* zero argument constructor */
{
    
}

template<typename T>
Stack<T>::~Stack()   /*  destructor    */
{
    data.clear();
}

template<typename T>
Stack<T>::Stack(const Stack<T>& rhs)    /* copy constructor */
{
    auto i=rhs.data.begin();
    while (i!=rhs.data.end())
    {
        data.push_back(*i);
        i++;
    }
}

template<typename T>
Stack<T>::Stack(Stack<T> && rhs) /* move constructor */
{
    *this=rhs;
    rhs.clear();
}

template<typename T>
Stack<T>& Stack<T>::operator= (const Stack <T>&rhs) /* copy assignment operator= */
{
    auto i=rhs.data.begin();
    while (i!=rhs.data.end())
    {
        data.push_back(*i);
        i++;
    }
    return *this;
}


template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T> && rhs) /* move assignment operator= */
{
    data=rhs.data;
    rhs.clear();
    return *this;
}

template<typename T>
bool Stack<T>::empty() const /* returns true if the Stack contains no elements, and false otherwise */
{
    if (data.empty())
        return true;
    else
        return false;
}


template<typename T>
void Stack<T>::clear() /*deletes all elements */
{
    data.clear();
}


template<typename T>
int Stack<T>::size() const /* returns the number of elements stored in the Stack.*/
{
    return data.size();
}


template<typename T>
void Stack<T>::push(const T & x) /* adds  x  to the Stack.  copy version */
{
    data.push_back(x);
}

template<typename T>
void Stack<T>::push(T && x) /* adds x to the Stack. move version.*/
{
    data.push_back(std::move(x));
}


template<typename T>
void Stack<T>::pop() /* removes and discards the most recently added element of the Stack. */
{
    data.pop_back();
}


template<typename T>
T& Stack<T>::top() /* mutator that returns a reference to the most recently added element of the Stack */
{
    return data.back();
}

template<typename T>
const T& Stack<T>::top() const /* accessor that returns the most recently added element of the Stack */
{
    return data.back();
}

template<typename T>
void Stack<T>::print(std::ostream& os, char ofc) const /*oldest element printed first*/
{
    for (int i=0;i<data.size();i++)
    {
        os<<data[i]<<ofc;
    }
}












/*              non - member functions          */








/* invokes the print() method to print the Stack<T> a in the specified ostream */
template <typename T>
ostream& operator<<(std::ostream& os, const Stack <T>& a)
{
    a.print(os);
    return os;
}


/* returns true if the two compared Stacks have the same elements, in the same order, and false otherwise */
template <typename T>
bool operator==(const Stack<T>& lhs, const Stack<T>& rhs)
{
    Stack<T> a,b;
    a=lhs; b=rhs;
    if(a.size()!=b.size())
        return false;
    
    for(int i=0; i<a.size(); i++)
    {
        if(a.top()!=b.top())
            return false;
        a.pop();
        b.pop();
    }
    return true;
}


/* opposite of operator==(). */
template <typename T>
bool operator!=(const Stack<T>& lhs, const Stack<T>& rhs)
{
    return !(lhs==rhs);
}


/* returns true if every element in Stack a is smaller than or equal to the corresponding element of Stack b, */
template <typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b) //every element <= other
{
    Stack<T> lhs,rhs;
    lhs=a; rhs=b;
    
    if (lhs.size()<=rhs.size())
    {
        for (int i=0;i<lhs.size();i++)
        {
            if (lhs.top()>rhs.top())
            {
                return false;
            }
        }
        return true;
    }
    else
        return false;
}












