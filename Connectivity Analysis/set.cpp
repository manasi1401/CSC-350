/***************************************************************************//**
 * @file set.cpp
 *
 * @par Description
 *
 * @brief This file contains the functions used to operate on the disjoint set class
 *
 * @author Dakotah Rusley
 * @par Course:
 *    CSC315 Data Structures
 * @date  Fall 2017
 *
 *
 ******************************************************************************/

#include "set.h"

using namespace std;
/***************************************************************************//**
 * @brief Merge quite simply takes two Object IDs (x and y) and if they aren't
 * the same, merges them. One limitation of this function is that calling merge
 * on an object that doesn't exist will result in a segfault. Since in our
 * implementation, we will never do this, this wasn't a concern; However, it
 * is a limitation, and should be noted as such
 *
 * @param[in] x - operand 1 to merge
 * @param[in] y - operand 2 to merge
 *
 ******************************************************************************/
void DisjointSet::merge ( int x, int y )
{
    int setX = find ( x );
    int setY = find ( y );

    if ( setX != setY )
    {
        link ( setX, setY );
    }
}
/***************************************************************************//**
 * @brief Find is given an object ID (x), and returns the parent of that object.
 * Along the way, it recursively compresses the path of the tree, resetting
 * all parent fields to point to the top of the tree.
 *
 * @param[in] x - operand to find
 *
 * @returns - integer corresponding to the parent of the operand x
 ******************************************************************************/
int DisjointSet::find ( int x )
{
    object &object = get_object ( x );
    int &parent = object.parent;

    if ( parent == x )
    {
        return parent;
    }

    //path compression
    parent = find ( parent );

    return parent;
}
/***************************************************************************//**
 * @brief insertSingle will insert a new item in the forest (in this case represented
 * by a map), and increment the set counter. This setCount variable isn't used in
 * our implementation, but is very convenient for debugging and ensuring that
 * the set class is performing correctly
 *
 * @param[in] x - New objectID (integer corresponding to a location in the image)
 * @param[in] value - Group label for the new object (typically 0 for a fresh image)
 ******************************************************************************/
void DisjointSet::insertSingle ( int x, int value )
{
    forest.insert ( make_pair ( x, object ( value, x ) ) );
    setCount++;
}
/***************************************************************************//**
 * @brief getCount accesses the forest size, which is useful for ensuring that
 * all pixels are being mapped. If the program is operating correctly, the pixel
 * count of the image will be equal to the size of the forest
 *
 * @returns - size of the forest (number of pixels in the image)
 ******************************************************************************/
int DisjointSet::getCount() const
{
    return forest.size();
}
/***************************************************************************//**
 * @brief getSetNum retrieves the number of unique sets in the forest. This
 * value will correspond to the number of "blobs" in the image. Very useful
 * for debugging.
 *
 * @returns - number of unique sets in the workspace
 ******************************************************************************/
int DisjointSet::getSetNum() const
{
    return setCount;
}
/***************************************************************************//**
 * @brief The link helper function is what actually does the merge operation
 * on two objects. Called by merge, this private member function retrieves the
 * two objects from the map, checks their rank, and merges them accordingly. In
 * this operation, we also will decrement the set class, since we've turned 2 sets
 * into 1.
 *
 * @param[in] x - operand 1 to merge
 * @param[in] y - operand 2 to merge
 ******************************************************************************/
void DisjointSet::link ( int x, int y )
{
    object &objectA = get_object ( x );
    object &objectB = get_object ( y );

    int &rankA = objectA.rank;
    int &rankB = objectB.rank;

    if ( rankA > rankB )
    {
        objectB.parent = x;
    }
    else
    {
        objectA.parent = y;
        if ( rankA == rankB )
        {
            ++rankB;
        }
    }
    --setCount;
}

/***************************************************************************//**
 * @brief The getObject function, given some object ID, searches the forest and
 * returns the object itself. This acts as our accessor, allowing the program to
 * perform lookups by an object ID and getting back an object corresponding to that
 * ID. One limitation of this function is its behavior when trying to find an object
 * that doesn't exist. The try/catch block is there to mitigate some of this odd behavior,
 * but tread with caution. Since we never try to access things that don't exist, we
 * didn't consider this a major problem, but future use of this set class should
 * be warned.
 *
 * @param[in] x - ObjectID to locate
 *
 * @returns - object corresponding to the object ID
 ******************************************************************************/
DisjointSet::object &DisjointSet::get_object ( int x )
{
    map<int, object>::iterator it = forest.find ( x );
    if ( it != forest.end() )
    {
        return it->second;
    }
    else
    {
        try
        {
            throw 2;
        }
        catch ( int e ) {}
    }
    return it->second; //this should never happen. Just makes the compiler complain less
}
/***************************************************************************//**
 * @brief clearForest simply calls the clear function on the map, and sets
 * the number of unique sets to 0.
 *
 * @returns - number of unique sets in the workspace
 ******************************************************************************/
void DisjointSet::clearForest()
{
    if ( !forest.empty() )
    {
        forest.clear();
        setCount = 0;
    }
}
