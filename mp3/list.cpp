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
    if(head == NULL && tail == NULL){return;}
    ListNode* curr = head;
    ListNode* next = curr->next;
    while(curr != NULL){
	next = curr->next;
	delete curr;
	curr = next;
    }
    head = NULL;
    tail = NULL;
    length = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    /// @todo Graded in MP3.1
    ListNode* newNode = new ListNode(ndata);
    newNode->prev = NULL;
    if(length){head->prev = newNode;}
    else{tail = newNode;}
    newNode->next = head;
    head = newNode;
    length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
    ListNode* newNode = new ListNode(ndata);
    newNode->next = NULL;
    if(length){tail->next = newNode;}
    else{head = newNode;}
    newNode->prev = tail;
    tail = newNode;
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
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    /// @todo Graded in MP3.1
    if(startPoint == endPoint || length <= 1 || startPoint == NULL || endPoint == NULL){return;}
    ListNode* startPointPrev = startPoint->prev;
    ListNode* endPointNext = endPoint->next;
    ListNode* curr = startPoint;
    ListNode* temp = startPoint;

    while(curr != endPointNext){
	temp = curr->next;
	curr->next = curr->prev;
	curr->prev = temp;
	curr = curr->prev;
    }

    startPoint->next = endPointNext;
    endPoint->prev = startPointPrev;

    if(startPointPrev != NULL){startPointPrev->next = endPoint;}
    else{head = endPoint;}
    if(endPointNext != NULL){endPointNext->prev = startPoint;}
    else{tail = startPoint;}

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
void List<T>::reverseNth(int n)
{
    /// @todo Graded in MP3.1
    if(n <= 1 || length <= 1){return;}
    else if(n >= length){reverse();}
    else{
	ListNode* tempHead = head;
	ListNode* tempTail = tempHead;
	for(int i=0; i<length/n; i++){
	    for(int j=0; j<n-1; j++){
		tempTail = tempTail->next;
	    }
	    reverse(tempHead,tempTail);
	    tempTail = tempTail->next;
	    tempHead = tempTail;
	}
	if(tempHead != NULL){reverse(tempHead,tail);}
    }
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
    if(length < 3){return;}
    ListNode* curr = head;
    ListNode* currPrev;
    ListNode* currNext;
    while(curr->next != tail){
	curr = curr->next;
	currPrev = curr->prev;
	currNext = curr->next;
	currPrev->next = currNext;
	currNext->prev = currPrev;
	tail->next = curr;
	curr->prev = tail;
	curr->next = NULL;
	tail = curr;
	curr = currNext;
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

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
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
    if (ret.tail != NULL) {
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
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    if(start == NULL || splitPoint < 1 || splitPoint >= length){return start;}
    ListNode* curr = start;
    for(int i=0; i<splitPoint; i++){
	curr = curr->next;
    }
    ListNode* currPrev = curr->prev;
    currPrev->next = NULL;
    curr->prev = NULL;
    return curr; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
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
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    /// @todo Graded in MP3.2
    ListNode* retNode = first;
    ListNode* firstPrev = first->prev;
    ListNode* secondNext = second->next;
    while(second != NULL){
	if(first->data < second->data){
	    if(first->next != NULL){first = first->next;}
	    else{
		first->next = second;
		second->prev = first;
		break;
	    }
	}
	else{
	    firstPrev = first->prev;
	    first->prev = second;
	    second->prev = firstPrev;
	    if(firstPrev != NULL){firstPrev->next = second;}
	    else{retNode = second;}
	    secondNext = second->next;
	    second->next = first;
	    second = secondNext;
	}
    }
    return retNode; // change me!
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
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    if(chainLength <= 1){return start;}
    int half = chainLength/2;
    ListNode* otherHalf = split(start, half);
    start = mergesort(start, half);
    otherHalf = mergesort(otherHalf, chainLength - half);
    return merge(start, otherHalf); // change me!
}
