/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    // your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node*& subRoot){
    if(subRoot != NULL){
	mirror(subRoot->left);
	mirror(subRoot->right);
	Node* tempNode = subRoot->left;
	subRoot->left = subRoot->right;
	subRoot->right = tempNode;
    }
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // your code here
    return isOrdered(root);
}

template <typename T>
T BinaryTree<T>::maxLeftNode(const Node* subRoot) const{
    if(subRoot->left == NULL && subRoot->right == NULL){return subRoot->elem;}
    else if(subRoot->right == NULL){return max(subRoot->elem, maxLeftNode(subRoot->left));}
    else if(subRoot->left == NULL){return max(subRoot->elem, maxLeftNode(subRoot->right));}
    else{return max(subRoot->elem, max(maxLeftNode(subRoot->left), maxLeftNode(subRoot->right)));}
}

template <typename T>
T BinaryTree<T>::minRightNode(const Node* subRoot) const{
    if(subRoot->left == NULL && subRoot->right == NULL){return subRoot->elem;}
    else if(subRoot->right == NULL){return min(subRoot->elem, minRightNode(subRoot->left));}
    else if(subRoot->left == NULL){return min(subRoot->elem, minRightNode(subRoot->right));}
    else{return min(subRoot->elem, min(minRightNode(subRoot->left), minRightNode(subRoot->right)));}
}

template <typename T>
bool BinaryTree<T>::isOrdered(const Node* subRoot) const{
    bool isInOrder = true;
    if(subRoot == NULL){return isInOrder;}
    if(subRoot->left != NULL){
	if(subRoot->elem < maxLeftNode(subRoot->left)){isInOrder = false;}
    }
    if(subRoot->right != NULL){
	if(subRoot->elem > minRightNode(subRoot->right)){isInOrder = false;}
    }
    return (isOrdered(subRoot->left) && isOrdered(subRoot->right) && isInOrder);
}

/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards,
 * ending at a leaf node. Paths ending in a left node should be printed before
 * paths ending in a node further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
    // your code here
    std::vector<const BinaryTree<T>::Node*> treeVector;
    printPaths(treeVector, root);
}

template <typename T>
void BinaryTree<T>::printPaths(std::vector<const BinaryTree<T>::Node*>& treeVector, const Node* subRoot) const{
    treeVector.push_back(subRoot);
    if(subRoot->left == NULL && subRoot->right == NULL){printVector(treeVector);}
    if(subRoot->left != NULL){printPaths(treeVector, subRoot->left);}
    if(subRoot->right != NULL){printPaths(treeVector, subRoot->right);}
    treeVector.pop_back(); return;
}

template <typename T>
void BinaryTree<T>::printVector(std::vector<const BinaryTree<T>::Node*> treeVector) const{
    std::cout << "Path: ";
    for(typename std::vector<const BinaryTree<T>::Node*>::iterator i = treeVector.begin(); i != treeVector.end(); ++i){std::cout << ' ' << (*i)->elem;}
    std::cout << std::endl;
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    int sum = 0;
    return sumDistances(root, -1, sum);
}

template <typename T>
int& BinaryTree<T>::sumDistances(const Node* subRoot, int portion, int& sum) const{
    sum += (++portion);
    if(subRoot->left != NULL){sum = sumDistances(subRoot->left, portion, sum);}
    if(subRoot->right != NULL){sum = sumDistances(subRoot->right, portion, sum);}
    return sum;
}
