#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <iostream>


template <class T>
struct NodeType
{
    T nodeData;     //actual value or data
    NodeType <T> * leftLink;    //pointer to the left child
    NodeType <T> * rightLink;   //pointer to the right child

};

/**
 * @class Bst
 * @brief A binary search tree that stores items of type T.
 *
 * Maintains the representation invariant: left subtree < node < right subtree.
 * Duplicate keys are not inserted.
 *
 * @tparam T The type of data stored in the tree. Must support operator<, operator>, and operator==.
 */
template <class T>
class Bst
{
public:
    typedef void (*fp)(T &);     //typedef function pointer
    /**
    * @brief Default constructor. Creates an empty tree.
    */
    Bst();

    /**
    * @brief Destructor. Deletes all nodes in the tree.
    */
    ~ Bst();

    /**
     * @brief Copy constructor. Creates a deep copy of another tree.
     * @param otherTree The tree to copy from.
     */
    Bst(const Bst<T> & otherTree);

    /**
     * @brief Assignment operator. Replaces this tree with a deep copy of another.
     * @param otherTree The tree to copy from.
     * @return Reference to this tree.
     */
    Bst<T> & operator=(const Bst<T> & otherTree);

    /**
     * @brief Inserts an item into the tree.
     * @param item The item to insert.
     * @note Duplicates are ignored.
     */
    void Insert(const T & item);

    /**
     * @brief Searches for an item in the tree.
     * @param item The item to search for.
     * @return true if the item is found, false otherwise.
     */
    bool Search(const T & item) const;

    /**
     * @brief Deletes the entire tree and frees all memory.
     */
    void DeleteTree();

    /**
     * @brief Performs an in-order traversal and prints the nodes.
     * @note Prints items in sorted order.
     */
    void InorderTraversal(fp CollectData) const;

    /**
     * @brief Performs a pre-order traversal and prints the nodes.
     */
    void PreorderTraversal(fp CollectData) const;

    /**
     * @brief Performs a post-order traversal and prints the nodes.
     */
    void PostorderTraversal(fp CollectData) const;

private:
    NodeType<T> * root;

    void Copy(NodeType<T>* & copyRoot, NodeType<T>* firstRoot);

    void Insert(NodeType<T> * newNode, NodeType<T> * parent);

    bool Search(NodeType<T> * p, const T & item) const;

    void Destroy(NodeType<T> *p);

    void Inorder(NodeType<T> *p, fp CollectData) const;

    void Preorder(NodeType<T> *p, fp CollectData) const;

    void Postorder(NodeType<T> *p, fp CollectData) const;
};


//Public method imolementation

template <class T>
Bst<T>::Bst()
{
    root = nullptr;
}

template <class T>
Bst<T>::~Bst()
{
    Destroy(root);
}

//copy constructor
template <class T>
Bst<T>::Bst(const Bst<T> & otherTree)   //other tree - the tree we are copying from
{
    if (otherTree.root == nullptr)  //other tree is empty
        root = nullptr;
    else
        Copy(root, otherTree.root); //make full copy using root
}

//overload assignment operator
template <class T>
Bst<T> & Bst<T>::operator=(const Bst<T> & otherTree)
{
    // If they were the same object (tree = tree), we did nothing
    if (this != &otherTree) //are these different object
    {
        // Yes, they are different.
        // If the left tree has any nodes, delete them all
        // (so we don’t leak memory)
        if (root != nullptr)   //if the binary tree is not empty,
            Destroy(root);  //destroy the binary tree

        root = nullptr; //left tree now empty

        // If the right tree is empty, leave the left tree empty
        if (otherTree.root == nullptr)
            root = nullptr;
        else                // Otherwise make a full independent copy of the right tree
            Copy(root, otherTree.root);
    }//end else

    return *this;
}

/*
if they are different objects:
    empty the left tree
    then deep-copy the right tree into it
*/

template <class T>
void Bst<T>::Insert(const T & item)
{
    NodeType<T> * newNode;
    newNode = new NodeType<T>;  //Create a brand-new node on the heap
    newNode->nodeData = item;   // insert data into the new node
    newNode->leftLink = nullptr;    //new node no children, both both children empty
    newNode->rightLink = nullptr;

    if (root == nullptr)
        root = newNode; //if empty, the root node will be the new node
    else
        Insert(newNode, root);  //else use private helper recursive function to insert
}

template <class T>
bool Bst<T>::Search(const T & item) const
{
    return Search(root, item);  //call private function, start searching from the root
}


template <class T>
void Bst<T>::DeleteTree()
{
    Destroy(root);
}

template <class T>
void Bst<T>::InorderTraversal(fp CollectData) const
{
    Inorder(root, CollectData);
}

template <class T>
void Bst<T>::PreorderTraversal(fp CollectData) const
{
    Preorder(root, CollectData);
}

template <class T>
void Bst<T>::PostorderTraversal(fp CollectData) const
{
    Postorder(root, CollectData);
}

//private method implementation

template <class T>
void Bst<T>::Copy(NodeType<T>* & copyRoot, NodeType<T>* firstRoot)
{
    if (firstRoot == nullptr)
        copyRoot = nullptr;
    else
    {
        copyRoot = new NodeType<T>;     //create new node in the heap
        copyRoot->nodeData = firstRoot->nodeData;   //copy the data
        copyRoot->leftLink = nullptr;
        copyRoot->rightLink = nullptr;

        Copy(copyRoot->leftLink, firstRoot->leftLink);  //copy left sub-tree
        Copy(copyRoot->rightLink, firstRoot->rightLink);    //copy right sub-tree
    }
}

template <class T>
void Bst<T>::Insert(NodeType<T> * newNode, NodeType<T> * parent)    //*& function change caller pointer to link properly
{
    if (newNode->nodeData < parent->nodeData)   //compare new node with current data
    {
        if (parent->leftLink == nullptr)    //smaller keeping it to the left sub-tree
            parent->leftLink = newNode;     // if empty assign to the left children, Representation Invariant
        else
            Insert(newNode, parent->leftLink);  //recursive call, go deeper
    }
    else if (newNode->nodeData > parent->nodeData)
    {
        if (parent->rightLink == nullptr)   //bigger than current data, keep to right sub-tee
            parent->rightLink = newNode;    //if empty, assign to the right child, representation invariant
        else
            Insert(newNode, parent->rightLink); //recursive call, go deeper
    }
    else
        delete newNode;     // duplicate – do nothing; free memory allocated
}

template <class T>
bool Bst<T>::Search(NodeType<T> * p, const T & item) const
{
    if (p == nullptr)   //empty tree, nothing found
        return false;
    if (p->nodeData == item)    //value found
        return true;
    if (p->nodeData > item) //decide which way to go deeper, here the data search is smaller than the node, so left
        return Search(p->leftLink, item);   //smaller item go left
    else
        return Search(p->rightLink, item);  //bigger item go right
}

template <class T>
void Bst<T>::Destroy(NodeType<T> *p)
{
    if (p != nullptr)
    {
        Destroy(p->leftLink);   //post order, delete the child first
        Destroy(p->rightLink);
        delete p;
        p = nullptr;
    }
}

template <class T>
void Bst<T>::Inorder(NodeType<T> *p, fp CollectData) const
{
    if (p != nullptr)
    {
        Inorder(p->leftLink, CollectData);
        CollectData(p->nodeData);
        Inorder(p->rightLink, CollectData);
    }
}

template <class T>
void Bst<T>::Preorder(NodeType<T> *p, fp CollectData) const
{
    if (p != nullptr)
    {
        CollectData(p->nodeData);
        Preorder(p->leftLink, CollectData);
        Preorder(p->rightLink, CollectData);
    }
}

template <class T>
void Bst<T>::Postorder(NodeType<T> *p, fp CollectData) const
{
    if (p != nullptr)
    {
        Postorder(p->leftLink, CollectData);
        Postorder(p->rightLink, CollectData);
        CollectData(p->nodeData);
    }
}

#endif
