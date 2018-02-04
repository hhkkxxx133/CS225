/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

 #include <iostream>
 using namespace std;

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
    clear();

}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
    if (tail == NULL)
    {
        delete tail;
        delete head;
        length = 0;
        return;
    }

    while ( tail->prev != NULL )
    {
        tail = tail->prev;
        delete tail->next;
        tail->next = NULL;
    }

    delete tail;
    tail = NULL;

    head = NULL;

    length = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    /// @todo Graded in MP3.1
    ListNode * front = new ListNode(ndata);

    if (head == NULL)
    {
        head = front;
        tail = front;
    }
    else
    {
        front->next = head;
        head->prev = front;
        front->prev = NULL;
        head = front;
    }

    length++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    /// @todo Graded in MP3.1
    ListNode * back = new ListNode(ndata);

    if( tail == NULL )
    {
        tail = back;
        head = back;
    }
    else
    {
        tail->next = back;
        back->prev = tail;
        back->next = NULL;
        tail = back;
    }

    length++;
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
    /// @todo Graded in MP3.1
    if (startPoint == NULL || startPoint == endPoint ) return;
    
    ListNode * temp = startPoint;
    
    int len = 1;
    while(temp != endPoint){
        temp = temp->next;
        len++;
    }

    ListNode * forward = startPoint;
    ListNode * backward = endPoint;

    for ( int i=0 ; i < len/2 ; ++i )
    {
        if (forward->prev != NULL && backward->next != NULL){
            ListNode * tempprev = forward->prev;
            ListNode * tempnext = backward->next;

            forward->prev = forward->next;
            forward->next = tempprev;

            backward->next = backward->prev;
            backward->prev = tempnext;
        }
        else if ( forward->prev == NULL && backward->next != NULL ){

            forward->prev = forward->next;
            forward->next = backward->next;

            backward->next = backward->prev;
            backward->prev = NULL;
            //head = backward;
        }
        else if ( forward->prev != NULL && backward->next == NULL ){
            ListNode * tempprev = forward->prev;

            forward->prev = forward->next;
            forward->next = NULL;
            //tail = forward;

            backward->next = backward->prev;
            backward->prev = tempprev;
        }
        else
        {
            forward->prev = forward->next;
            forward->next = NULL;
            //tail = forward;

            backward->next = backward->prev;
            backward->prev = NULL;
            //head = backward;
        }

        if ( i != len/2 -1 ){
            forward = forward->prev;
            backward = backward->next;
        }
    }

    if ( len%2 != 0 )
    {
        forward->prev->next = forward;
        backward->next->prev = backward;
    }

    temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;

}



/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
    /// @todo Graded in MP3.1
    if (length <= 1) return;
    if (n <= 1) return;
    if (n==length) {
        reverse(head, tail);
        return;
    }

    int l = length;
    ListNode* tempstart = NULL;
    ListNode* tempend = NULL;
    ListNode* temp = NULL;
    ListNode* ptr = NULL;

    while (l - n > 0){

        if (l==length) {
            tempstart = head;
        }
        else {
            temp = tempend;
            tempstart = ptr;      
        }

        tempend = tempstart;
        for( int i=0 ; i<n-1 ; ++i ){
            tempend = tempend->next;
        }
        ptr = tempend->next;

        reverse(tempstart,tempend);

        if (l==length) head = tempstart;
        else {
            temp->next = tempstart;
            tempstart->prev = temp;
            tempend->next = ptr;
        }

        l = l-n;
    }

    temp = tempend;
    tempstart = ptr;
    reverse(tempstart,tail);
    temp->next = tempstart;
    tempstart->prev = temp;

}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
    if (length == 0) return;

    ListNode * curr = head;
    ListNode * temp;
    while ( curr->next != tail )
    {
        temp = curr->next;
        temp->next->prev = curr;
        curr->next = curr->next->next;

        tail->next = temp;
        temp->prev = tail;
        temp->next = NULL;
        tail = temp;

        curr = curr->next;
    }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
    /// @todo Graded in MP3.2
    if (start == NULL) return NULL;
    if (splitPoint > length) return NULL;

    ListNode * temphead = start;
    for (int i=0; i<splitPoint-1;++i)
        temphead = temphead->next;

    if (temphead->next != NULL){
        temphead = temphead->next;
        temphead->prev->next = NULL;
        temphead->prev = NULL;
    }
    else temphead = NULL;

    return temphead;

    //return NULL; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
    /// @todo Graded in MP3.2
    
    if (first==NULL && second==NULL) return NULL;
    if (first==NULL && second!=NULL) return second;
    if (first!=NULL && second==NULL) return first;

    ListNode * temphead;
    ListNode * temp;
    if(first->data < second->data) {
        temphead = first;
        first = first->next;
    }
    else {
        temphead = second;
        second = second->next;
        /*
        temp = first;
        first = second;
        second = temp;
        */
    }
    /*    
    if (first->next != NULL) first = first->next;
    else {
        temphead->next = second;
        second->prev = temphead;
    }
    */
    temp = temphead;
    while( first != NULL && second != NULL)
    {
        if (first->data < second->data){
            temp->next->prev = NULL;
            temp->next = first;
            first->prev = temp;
            temp = first;
            first = first->next;
        }
        else {
            temp->next->prev = NULL;
            temp->next = second;
            second->prev = temp;
            temp = second;
            second = second->next;
        }
    }

    if (first == NULL) {
        temp->next = second;
        second->prev = temp;
    }
    else {
        temp->next = first;
        first->prev = temp;
    }

    return temphead;
    //return NULL; // change me!

}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    /// @todo Graded in MP3.2
    if(chainLength <= 1) return start;

    int half = chainLength/2;
    ListNode * temp = split(start, half);
    start = mergesort(start, half);
    temp = mergesort(temp, chainLength-half);
    return merge(start, temp);
    
    //return NULL; // change me!
}
