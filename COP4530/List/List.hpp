for (auto i = myList.begin(); i != myList.end(); i++)
{
    myList.push_back(node[i]);
/*
 Jean Roquebert
 COP4530
 Project #2
 Due October 10,2019
 Fall 2019
 
 List.hpp
 
 */




/*      const iterator      */

template <typename T>
List<T>::const_iterator::const_iterator()
{
    current=nullptr;
}

template <typename T>
const T& List<T>::const_iterator::operator*( ) const
{
    return retrieve();
}

template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++()
{
    current = current->next;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
    const_iterator old = *this;
    ++( *this );
    return old;
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--()
{
    current = current->prev;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
    const_iterator old = *this;
    --( *this );
    return old;

}

template <typename T>
bool List<T>::const_iterator::operator== ( const const_iterator & rhs ) const
{
    return (current==rhs.current);
}

template <typename T>
bool List<T>::const_iterator::operator!= ( const const_iterator & rhs ) const
{
    return !(*this==rhs);
}

template <typename T>
T& List<T>::const_iterator::retrieve( ) const
{
    return current->data;
}

template <typename T>
List<T>::const_iterator::const_iterator(Node *p )
{
    current=p;
}














/*      iterator class      */
template <typename T>
List<T>::iterator::iterator( ): const_iterator()
{}


template <typename T>
T & List<T>::iterator::operator* ( )
{ return const_iterator::retrieve( ); }

template <typename T>
const T & List<T>::iterator::operator* ( ) const
{ return const_iterator::operator*( ); }




template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
    this->current = this->current->next;
    return *this;

}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    iterator old = *this;
    ++( *this );
    return old;

}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--()
{
    this->current = this->current->prev;
    return *this;

}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
    iterator old = *this;
    --( *this );
    return old;

}


template <typename T>
List<T>::iterator::iterator( Node *p ) : const_iterator(p)
{}


















/*      list functions      */
template <typename T>
List<T>::List()
{
    init();
}

template<typename T>
List<T>::List(const List &rhs)
{
    init( );
    for( auto & x : rhs )
        push_back( x );
}

template<typename T>
List<T>::List( List && rhs )                /* move constructor */
{
    theSize=rhs.theSize;
    head=rhs.head;
    tail=rhs.tail;
    
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template<typename T>
List<T>::List(int num, const T & val)
{
    theSize=0;
    head= new Node(val);
    tail= new Node(val);
    head->next=tail;
    tail->prev=head;
    
    for (int i=0;i<num;i++)
    {
        this->push_back(val);
    }
}

template<typename T>
List<T>::List(const_iterator start, const_iterator end)
{
    init();
    const_iterator itr=start;
    while(itr!= end)
        this->push_back(*itr++);
    
}


template<typename T>
List<T>::List(std::initializer_list<T> iList)
{
    init();
    for(const auto& it: iList)
        push_back(it);
}



template<typename T>
List<T>::~List( )
{
    clear( );
    delete head;
    delete tail;
}


template<typename T>
List<T>& List<T>::operator=(const List & rhs ) /* copy assignment operator= */
{
    List copy = rhs;
    std::swap( *this, copy );
    return *this;
}

template<typename T>
List<T>& List<T>::operator=(List && rhs ) /* move assignment operator=  */
{
    std::swap( theSize, rhs.theSize );
    std::swap( head, rhs.head );
    std::swap( tail, rhs.tail );
    
    return *this;

}


template<typename T>
List<T>& List<T>::operator=(std::initializer_list<T> iList)
{
    clear();
    
    for(const auto& it: iList)
        push_back(it);
    
    return *this;
}

template<typename T>
int List<T>::size() const
{
    return theSize;
}

template<typename T>
bool List<T>::empty( ) const
{ return size( ) == 0; }

template <typename T>
void List<T>::clear()
{
    while(!empty())
        pop_front();
}

template<typename T>
T & List<T>::front( )
{ return *begin( ); }

template<typename T>
const T & List<T>::front( ) const
{ return *begin( ); }

template<typename T>
T & List<T>::back( )
{ return *--end( ); }

template<typename T>
const T & List<T>::back( ) const
{ return *--end( ); }

template<typename T>
void List<T>::push_front( const T & x )        /* copy  */
{ insert( begin( ), x ); }

template <typename T>
void List<T>::push_back(const T & x)        /* copy  */
{ insert(end(),x); }

template<typename T>
void List<T>::push_front( T && x )        /* move   */
{ insert( begin( ), std::move( x ) ); }

template<typename T>
void List<T>::push_back( T && x )        /* move    */
{ insert( end( ), std::move( x ) ); }

template<typename T>
void List<T>::pop_front( )
{ erase( begin( ) ); }

template<typename T>
void List<T>::pop_back( )
{ erase( --end( ) ); }

template<typename T>
void List<T>::remove(const T &val)
{
    iterator i = begin();
    while (i!=end())
    {
        if (*i==val)
        {
            erase(i);
        }
        i++;
    }
}


template<typename T>
template<typename PREDICATE>
void List<T>::remove_if(PREDICATE pred)
{
    iterator a=begin();
    
    while (a!=end())
    {
        if (pred(*a))
            erase(a);
        a++;
    }
}

template<typename T>
void List<T>::print(std::ostream& os, char ofc) const
{
    for (auto a=begin(); a!=end(); a++)
    {
        os << *a<< ofc;
    }
}

template <typename T>
typename List<T>::iterator List<T>::begin()
{
    return iterator( head->next );
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return const_iterator( head->next );
}

template<typename T>
typename List<T>::iterator List<T>::end()
{ return iterator( tail ); }


template<typename T>
typename List<T>::const_iterator List<T>::end() const
{ return const_iterator( tail ); }



template<typename T>
typename List<T>::iterator List<T>::insert( iterator itr, const T & x )
{
    Node *p = itr.current;
    ++theSize;
    return iterator( p->prev = p->prev->next = new Node{ x, p->prev, p } );
}

template<typename T>
typename List<T>::iterator List<T>::insert( iterator itr, T && x )
{
    Node *p = itr.current;
    ++theSize;
    return iterator(p->prev=p->prev->next = new Node{std::move(x),p->prev,p});
    
}


template<typename T>
typename List<T>::iterator List<T>::erase( iterator itr )
{
    Node *p = itr.current;
    iterator retVal(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;
    return retVal;
}

template<typename T>
typename List<T>::iterator List<T>::erase( iterator from, iterator to )
{
    for( iterator itr = from; itr != to; )
        itr = erase( itr );
    
    return to;
}

template<typename T>
void List<T>::init( )
{
    theSize=0;
    head= new Node;
    tail= new Node;
    head->next=tail;
    tail->prev=head;
}















/*      special member functions        */

template <typename T>
void List<T>::reverse()
{
    iterator a1= begin();
    iterator a2= end();
    a1--;
    for(int i=0; i<=theSize/2; i++)
    {
        std::swap(*a1, *a2);
        a1++;
        a2--;
    }
}


template <typename T>
void List<T>::deduplicate()
{
    Node *p1,*p2,*dup;
    p1=head;
    /* Pick elements one by one */
    while (p1 != NULL && p1->next != NULL)
    {
        p2=p1;
        /* Compare the picked element with rest of elements*/
        while (p2->next != NULL)
        {
            /* If duplicate then delete it */
            if (p1->data == p2->next->data)
            {
                dup = p2->next;
                p2->next = p2->next->next;
                delete(dup);
                --theSize;
            }
            else
            {
                p2 = p2->next;
            }
            tail=p2;
        }
        p1 = p1->next;
    }
}








/*      comparison operators        */


template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs)
{
    if(lhs.size()==rhs.size())
    {
        auto itrl = lhs.begin();
        auto itrr = rhs.begin();
        while(itrl!=lhs.end())
        {
            if(*itrl!=*itrr)
                return false;
            itrl++;
            itrr++;
        }
    }
    else
        return false;
    
    return true;
}

template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs)
{
    return !(lhs==rhs);
}

/* overloading output operator*/
template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l)
{
    l.print(os);
    return os;
}



