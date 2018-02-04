/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if( curDim>=Dim || curDim<0)
        return false;

    if (first[curDim] == second[curDim])
        return first<second;

    return (first[curDim] < second[curDim]);
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
    int poDistance = Distance(target, potential);
    int currDistance = Distance(target, currentBest);

    if (currDistance == poDistance) return (potential<currentBest);
    
    return (poDistance < currDistance);
}

template<int Dim>
int KDTree<Dim>::Distance(const Point<Dim> p1, const Point<Dim> p2) const
{
    int sum = 0;
    for (int i = 0; i < Dim; ++i){
        sum = sum + (p1[i] - p2[i]) * (p1[i] - p2[i]);
    }

    return sum;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    /**
     * @todo Implement this function!
     */
    points = newPoints;
    buildTree(points, 0, points.size()-1, 0);
}

template<int Dim>
void KDTree<Dim>::buildTree(vector< Point<Dim> > & newPoints, int left, int right, int dimension)
{
    if (left >= right) return;
    
    //quickselect algorithm for median
    int mid = (left+right) / 2;
    points[mid] = select(newPoints, left, right, mid, dimension);
    
    //recurse through left and right partitions
    buildTree(newPoints, left, mid - 1,  (dimension + 1) % Dim);
    buildTree(newPoints, mid + 1, right, (dimension + 1) % Dim);
}

template<int Dim>
Point<Dim> KDTree<Dim>::select(vector< Point<Dim> > & list, int left, int right, int k, int dimension)
{
    while(left < right){
        int pivotNewIndex = partition(list, left, right, (right + left) / 2, dimension);
        
        if (pivotNewIndex == k){
            return list[pivotNewIndex];
        }
        else if (k <  pivotNewIndex){
            right = pivotNewIndex - 1; // search left of pivotNewIndex
        }       
        else left = pivotNewIndex + 1; // search right of pivotNewIndex
    }

    return list[left];
}

template<int Dim>
int KDTree<Dim>::partition(vector< Point<Dim> > & list, int left, int right, int pivotIndex, int dimension)
{
    Point<Dim> pivotValue = list[pivotIndex];
    swap(list[pivotIndex], list[right]); // swap pivot to end

    int storeIndex = left;
    int temp = left;

    while (temp<right){
        //if (list[i][dimen] < pivotValue[dimen]){
        if (smallerDimVal(list[temp], pivotValue, dimension)){
            swap(list[temp], list[storeIndex]);
            storeIndex++;
        }
        temp++;
    }

    swap(list[right], list[storeIndex]); // swap Pivot to its final place
    return storeIndex;
}

template<int Dim>
void KDTree<Dim>::swap(Point<Dim> &point1, Point<Dim> &point2)
{
    Point<Dim> temp;

    temp = point1;
    point1 = point2;
    point2 = temp;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
   if (points.size() == 0){
         return Point<Dim>();
     }
    return findNearestNeighbor(0, points.size()-1, query, 0);
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(int begin, int end, const Point<Dim> & query, int curDim) const
{
    if (begin >= end) return points[begin];

    int mid = (begin + end) / 2;
    Point<Dim> currBest;
    Point<Dim> temp;
    
    if (smallerDimVal(points[mid], query, curDim))
        currBest = findNearestNeighbor(mid + 1, end, query, (curDim + 1) % Dim);   
    else // root is greater than query, search left 
        currBest = findNearestNeighbor(begin, mid - 1, query, (curDim + 1) % Dim);

    //check if root is closer than subtrees, set to currbest
    if (shouldReplace(query, currBest, points[mid]))
        currBest = points[mid];
    
    int radius = Distance(query, currBest);
    int distance = (-points[mid][curDim]+query[curDim])*(query[curDim] - points[mid][curDim]);

    if (distance <= radius){
        if (smallerDimVal(points[mid], query, curDim)){
            temp = findNearestNeighbor(begin, mid - 1, query, (curDim + 1) % Dim);
        }
        else{
            temp = findNearestNeighbor(mid + 1, end, query, (curDim + 1) % Dim);
        }
        //if temp is closer than currBest
        if (shouldReplace(query, currBest, temp)){
            currBest = temp;
        }
    }
    
    return currBest;
}
