#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

/**
 * @class Vector
 * @brief A box that holds many items of the same type.
 *
 * This is not the vector from the C++ library. The box does not know
 * or care what it is holding. The items sit in an array made with new.
 * When the array is full, a bigger one is made and the old items are
 * copied over. Copy, assign, and the destructor are here because the
 * array is on the heap.
 *
 * @tparam T The type of one item in the box.
 */

template <class T>
class Vector
{
public:
    /**
     * @brief Makes an empty box with space for 5 items.
     */
    Vector();

    /**
     * @brief Makes an empty box with space for n items.
     * @param n How many empty slots to start with. The box still holds nothing.
     */
    Vector(int n);

    /**
     * @brief Deep copy constructor
     */
    Vector(const Vector<T> & initialiser);

    /**
     * @brief Cleans up the array when the box is destroyed.
     */
    ~Vector();

    /**
     * @brief Puts one item into the box at the given spot.
     *
     * If the box is full, resize it by 2 times
     *
     * @param index Where to put the item. From 0 up to Size().
     * @param element The item to put in - each record of weather data
     * @return True if the spot was allowed and the item was stored.
     */
    bool Insert(int index, const T & element);
    /**
    * @brief Removes the item at index and closes the gap.
    * @param index Which item to remove. From 0 up to Size() - 1.
    * @return True if the index was allowed and the item was removed.
    */
    bool Delete(int index);
    /**
     * @brief Gets an item so it can be changed.
     * @param index Which item.
     * @return That item.
     */
    T& operator[](int index);
    /**
     * @brief Gets an item for reading only.
     * @param index Which item.
     * @return That item.
     */
    const T& operator[] (int index) const;

    /**
     * @brief Tells you how many items are in the box.
     * @return The number of items stored, not the number of empty slots.
     */
    int Size() const;

    /**
     * @brief Makes this box a full copy of another box.
     * @param rhs The box to copy from.
     * @return This box, after the copy.
     */
    Vector<T>& operator=(const Vector<T>& rhs);

private:
    T * m_array;  ///< The array that holds the items.
    int m_alloc;  ///< How many slots the array has.
    int m_size;   ///< How many items are actually stored.

    /**
     * @brief Makes a new array and copies every item from another box.
     * @param rhs The box to copy from.
     * @return True when the copy is done.
     */
    bool Copy(const Vector<T> & rhs);
};

//class implementation follows

/***
The empty constructor makes room for 5 items, says the box holds 0, and new makes the array.
The empty constructor is for when you do not know, or do not care, how big the box should start.
Vector<WeatherRecType> Weather_data; calls that one. It picks 5 so the box has somewhere to put the first items.
When those 5 are full, Insert makes a bigger array.
***/
template <class T>
Vector<T>::Vector()
{
    m_alloc = 5;
    m_size = 0;
    m_array = new T[m_alloc];
}

/***
The Vector(int n) constructor does the same with room for n.
Vector(int n) is for when you already know a starting size. Vector<float> values(100); makes room for 100 straight away, so it does not have to grow as often.
n is that number. m_alloc = n stores it, and new T[m_alloc] makes that many slots. m_size is still 0, because room is not the same as items stored.
***/
template <class T>
Vector<T>::Vector(int n)
{
    m_alloc = n;
    m_size = 0;
    m_array = new T[m_alloc];
}

/***
The copy constructor sets the pointer to nothing, then Copy builds the real copy.
***/
template <class T>
Vector<T>::Vector(const Vector<T> & initialiser)
{
    m_array = nullptr;
    Copy(initialiser);
}

/***
The destructor delete[] frees the array and sets the pointer to nothing.
***/
template <class T>
Vector<T>::~Vector()
{
    // if array is not null
    delete[] m_array;
    m_array = nullptr;
}

/***
Insert returns false if the spot is below 0 or past the end.
If the box is full, big_alloc is twice the old room, a new array is made,
the old items are copied across, the old array is freed, and the box now points at the new array.
Then the new item is written at index and the count goes up by 1. It returns true.
***/
template <class T>
bool Vector<T>::Insert(int index, const T & element)
{
    if (index < 0 || index > m_size)        //return false if out of bound
        return false;

    if (m_size == m_alloc)      //when it is full
    {
        int big_alloc = m_alloc * 2;
        T* big_array = new T[big_alloc];
        for (int i = 0; i < m_size; i++)
        {
            big_array[i] = m_array[i];
        }
        delete[] m_array;
        m_array = big_array;
        m_alloc = big_alloc;

    }

    m_array[index] = element;
    m_size++;
    return true;
}

/***
Delete returns false if the index is below 0 or past the last stored item.
start at the item you want gone, copy the next item onto it, then do the same for the rest.
After the copies, forget the last item by lowering the count. The old last value may still sit in the array,
but Size() no longer reports it, so the rest of the program does not see it.
***/
template <class T>
bool Vector<T>::Delete(int index)
{
    if (index < 0 || index >= m_size)
        return false;

    for (int i = index; i < m_size - 1; i++)
        m_array[i] = m_array[i + 1];

    m_size--;
    return true;
}

/***
The non-const operator[] returns the item so the caller can change it.
***/
template <class T>
T& Vector<T>::operator[](int index)
{
    return m_array[index];
}

/***
The const operator[] returns the item at index for reading.
***/
template <class T>
const T& Vector<T>::operator[] (int index) const
{
    // if index is oiut of boads, then throw exception
    return m_array[index];
}

/***
Size returns how many items are stored, not how many slots exist
***/
template <class T>
int Vector<T>::Size() const
{
    return m_size;
}

/***
Copy copies the room and the count from the other box, makes a new array of that room, and copies each stored item.
Assignment checks this == &rhs so a box is not copied onto itself.
Otherwise it frees the old array, calls Copy, and returns this box.
***/
template <class T>
bool Vector<T>::Copy(const Vector<T> & rhs)
{
    m_alloc = rhs.m_alloc;
    m_size = rhs.m_size;
    m_array = new T[m_alloc];
    for (int i = 0; i < m_size; i++)
        m_array[i] = rhs.m_array[i];
    return true;
}

//assignment
template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
    if(this == &rhs)
    {
        return *this;
    }

    delete[] m_array;
    m_array = nullptr;
    Copy(rhs);
    return *this;
}


#endif // VECTOR_H_INCLUDED
