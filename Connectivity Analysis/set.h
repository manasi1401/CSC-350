/*************************************************************************//**
 * @file set.h
 *
 * @brief Defines our disjoint set class, which is the crux of the performance
 * of this connected component analysis. The struct object contains fields for
 * data, rank, and parent, which allow us to perform path compression to the trees.
 * This vastly increases the speed of the program. To operate, we create a map
 * of Objects linked to integers corresponding to the location in the image.
 *****************************************************************************/

#ifndef _SET_H
#define _SET_H

#include <cstdio>
#include <iostream>
#include <map>

using namespace std;
/*!
*@brief Defines the disjoint set class
*/
class DisjointSet {
    public:
        /*!
        *@brief Structure containing the cell data. Operated on by class member functions
        */
        struct object
        {
            /*!Group label (0 if ungrouped)*/
            int data;
            /*!Rank field for performing merges*/
            int rank;
            /*!Parent of this object*/
            int parent;
            /*!Default constructor*/
            object ( int value, int parent ) : data ( value ),
                rank ( 0 ), parent ( parent ) {}
        };

    public:
    /*!Initialize the forest*/
        DisjointSet() : setCount ( 0 ) {}
    /*!Find a set containing int*/
        int find ( int x );
    /*!merge two sets*/
        void merge ( int x, int y );
        /*!Insert a single object in the forest*/
        void insertSingle ( int x, int value );
        /*!Get Number of Inserts*/
        int getCount() const;
        /*!Number of sets in the forest*/
        int getSetNum() const;
        /*!Clear the forest*/
        void clearForest();

    private:
    /*!Map containing Forest*/
        map<int, object> forest;
        /*!Number of Sets*/
        int setCount;
        /*!function to link objects during merge*/
        void link ( int x, int y );
        /*!get an object from set*/
        object &get_object ( int x );

};
#endif
