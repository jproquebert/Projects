
 /*public functions*/
    template<typename T>
    NSequence<T>::NSequence(int initSize)   /*explicit constructor*/
    {
        if (initSize<=0)
        {
            initSize=1;
        }
        totalCapacity=initSize+5;
        numOfItems=initSize;
        items = new T [totalCapacity];
        
    }
    
    template<typename T>
 NSequence<T>::NSequence( const NSequence & rhs )   /*copy constructor*/
    {
        numOfItems=rhs.numOfItems;
        totalCapacity=rhs.totalCapacity;
        items=new T[totalCapacity];
        for (int i=0;i<rhs.numOfItems;i++)
        {
            items[i]=rhs.items[i];
        }
    }
    
    template<typename T>
   NSequence<T>& NSequence<T>::operator= ( const NSequence & rhs )  /*copy operator*/
    {
        numOfItems=rhs.numOfItems;
        totalCapacity=rhs.totalCapacity;
        items=new T[totalCapacity];
        for (int i=0;i<rhs.numOfItems;i++)
        {
            items[i]=rhs.items[i];
        }
        return *this;
    }
    
    template<typename T>
    NSequence<T>::~NSequence( ) /*destructor*/
    {
        delete [] items;
        numOfItems=0;
        totalCapacity=0;
    }
    
    template<typename T>
    NSequence<T>::NSequence( NSequence && rhs ) /*move constructor*/
    {
        numOfItems=rhs.numOfItems;
        totalCapacity=rhs.totalCapacity;
        items=new T[totalCapacity];
        for (int i=0;i<rhs.numOfItems;i++)
        {
            items[i]=rhs.items[i];
        }
    }
    
    template<typename T>
    NSequence<T>& NSequence<T>::operator= ( NSequence && rhs )  /*move assignment operator*/
    {
        numOfItems=rhs.numOfItems;
        totalCapacity=rhs.totalCapacity;
        items=new T[totalCapacity];
        for (int i=0;i<rhs.numOfItems;i++)
        {
            items[i]=rhs.items[i];
        }
    }
    
    template<typename T>
    bool NSequence<T>::isEmpty( ) const     /*isempty function*/
    {
        if (numOfItems==0)
            return true;
        else
            return false;
    }
    
    template<typename T>
    int NSequence<T>::getSize( ) const      /*get size*/
    {
        return numOfItems;
    }
    
    template<typename T>
    int NSequence<T>::getCapacity( ) const      /*get capacity*/
    {
        return totalCapacity;
    }

    template<typename T>
    T& NSequence<T>::operator[](int index)
    {
        if (index>numOfItems)
        {
            //return NULL;
        }
        return items[index];
    }

    template<typename T>
    const T& NSequence<T>::operator[](int index) const
    {
        return items[index];
    }

    template<typename T>
    T& NSequence<T>::getFirst() const
    {
        return items[0];
    }

    template<typename T>
    T& NSequence<T>::getLast() const
    {
        return items[numOfItems-1];
    }
    
    /* insert data element d just before item at pos position*/
    template<typename T>
    void NSequence<T>::insert(const int pos, const T & d) /* copy semantics*/
    {
        NSequence<T> temp=*this;
        numOfItems++;
        items=new T[getSize()];
        for (int i=getSize();i>=0;--i)
        {
            if (i>pos)
            {
                for (int j=pos+1;j<getSize()-1;j++)
                {
                items[i]=temp.items[j];
                }
            }
            else if (i==pos)
            {
                items[i]=d;
            }
            else
            {
                items[i]=temp.items[i];
            }
        }
        /*remember to resize array capacity*/
        if (numOfItems>totalCapacity)
        {
            growCapacity(5);
        }
    }

    template<typename T>
    void NSequence<T>::insert(const int pos, T && d) /* move semantics*/
    {
        NSequence<T> temp=*this;
        numOfItems++;
        items=new T[getSize()];
        for (int i=getSize();i>=0;--i)
        {
            if (i>pos)
            {
                items[i]=temp.items[i-1];
                
            }
            else if (i==pos)
            {
                items[i]=d;
            }
            else
            {
                items[i]=temp.items[i];
            }
        }
        
        /*remember to resize array capacity*/
        if (numOfItems>totalCapacity)
        {
            growCapacity(5);
        }
    }

    template<typename T>
    void NSequence<T>::remove(const int pos) /* remove item at pos position*/
    {
        NSequence<T> temp=*this;
        numOfItems--;
        items=new T[getSize()];
        for (int i=0;i<getSize();i++)
        {
            if (i<pos)
            {
                items[i]=temp.items[i];
            }
            else
                items[i]=temp.items[i+1];
        }
    }

    template<typename T>
    void NSequence<T>::push_back( const T & x ) /*copy semantics, insert at the end*/
    {
        insert(getSize(),x);
        if (numOfItems>=totalCapacity)
        {
            growCapacity();
        }
    }

    template<typename T>
    void NSequence<T>::push_back( T && x ) /* move semantics, insert at the end*/
    {
        insert(getSize(),x);
        if (numOfItems>=totalCapacity)
        {
            growCapacity();
        }
    }

    template<typename T>
    void NSequence<T>::pop_back( ) /* delete the last element*/
    {
        remove(getSize());
    }
    
    /* Grow the totalCapacity by newCapacity, double if zero input provided) */
    template<typename T>
    void NSequence<T>::growCapacity (int newCapacity)
    {
        NSequence<T> temp=*this;
        
        if (newCapacity==0)
        {
            totalCapacity=totalCapacity * 2;
        }
        else
        {
            totalCapacity=totalCapacity+newCapacity;
        }
        
        items = new T [totalCapacity];
        numOfItems=temp.numOfItems;
        
        for (int i=0;i<numOfItems;i++)
        {
            items[i]=temp.items[i];
        }
        
    }
    
    /* print out the items from begin to end, up to 50 if too many */
    template<typename T>
    void NSequence<T>::printout (int begin, int end)
    {
        for (int i=begin;i<end+1;i++)
        {
            if (i==50)
            {
                break;
            }
            cout<<"["<<i<<"]"<<"="<<items[i]<<"   ";
        }
    }

