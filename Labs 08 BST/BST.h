
#ifndef LAB08_BST_BST_H
#define LAB08_BST_BST_H

#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "BSTInterface.h"
#include "BTNODE.h"

using namespace std;

template<typename T>
class BST : public BSTInterface<T> {
private:
    const T *find(Node<T> *local_root, const T &item) const;

    virtual bool addNode(Node<T> *&local_root, const T &item);

    virtual bool removeNode(Node<T> *&local_root, const T &item);

    virtual void replaceParent(Node<T> *&old_root, Node<T> *&local_root);

    virtual bool clearTree(Node<T> *&tree);

public:
    Node<T> *root;

    BST() : root(NULL) {};

    virtual ~BST() {clearTree();};


    virtual bool addNode(const T &item);

    virtual bool removeNode(const T &item) {
        return removeNode(this->root, item);
    };

    virtual bool clearTree() {
        return clearTree(root);
    };




    virtual int size() {
        stringstream out;
        if (root == NULL)
            return 0;
        else
            return sizeAtN(root);
    }

    virtual int sizeAtN(Node<T> *node) {
        if (node == NULL) {
            return 0;
        } else {
            return (sizeAtN(node->left) + 1 + sizeAtN(node->right));
        }
    }

    virtual bool outLevel(Node<T>* root, int level, stringstream& out) const;

    virtual std::string toString() const;

    const T *find(const T &target) const;

};

/************************************
 * Add<data> function recursively
 ***********************************/

template<typename T>
bool BST<T>::addNode(const T &item) {
    if (find(item)) {
        return false;
    }
    return addNode(this->root, item);
}

template<typename T>
bool BST<T>::addNode(Node<T> *&local_root, const T &item) {
    if (local_root == NULL) {
        local_root = new Node<T>(item);
        return true;
    } else {
        if (item < local_root->data)
            return addNode(local_root->left, item);
        else if (local_root->data < item)
            return addNode(local_root->right, item);
        else {
            return false;
        }
    }

}

/************************************
 * Remove<data> function recursively
 ***********************************/

template<typename T>
bool BST<T>::removeNode(Node<T> *&local_root, const T &item) {
    if (local_root == NULL) {
        return false;
    } else {
        if (item < local_root->data)
            return removeNode(local_root->left, item);
        else if (local_root->data < item)
            return removeNode(local_root->right, item);
        else {
            Node<T> *old_root = local_root;
            if (local_root->left == NULL) {
                local_root = local_root->right;
            } else if (local_root->right == NULL) {
                local_root = local_root->left;
            } else {
                replaceParent(old_root, old_root->left);
            };
            delete old_root;
            return true;
        }
    }
}

/************************************
 * Replace parent function recursive
 ***********************************/

template<typename T>
void BST<T>::replaceParent(Node<T> *&old_root, Node<T> *&local_root) {
    if (local_root->right != NULL) {
        replaceParent(old_root, local_root->right);
    } else {}
    old_root->data = local_root->data;
    old_root = local_root;
    local_root = local_root->left;
}

/************************************
 * Clear tree function recursively
 ***********************************/

template<typename T>
bool BST<T>::clearTree(Node<T> *&tree) {
    if (tree == NULL) {
        return true;
    }
    if (tree->left != NULL) {
        clearTree(tree->left);
    }
    if (tree->right != NULL) {
        clearTree(tree->right);
    }
    delete tree;
    tree = NULL;
    return true;
}

/************************************
 * Find<data> function recursively
 ************************************/

template<typename T>
const T *BST<T>::find(const T &target) const {
    return find(this->root, target);
}

template<typename T>
const T *BST<T>::find(Node<T> *local_root, const T &target) const {
    if (local_root == NULL) return NULL;
    if (target < local_root->data) return find(local_root->left, target);
    else if (local_root->data < target) return find(local_root->right, target);
    else return &(local_root->data);
}

/************************************
 * Print level order traversal
 ************************************/
template<typename T>
bool BST<T>::outLevel(Node<T>* root, int level, stringstream& out) const
{
    if (root == NULL) return false;
    if (level == 1)
    {
        out << " " << root->data;
        if ((root->left != NULL) || (root->right != NULL)) return true;
        return false;
    }
    if ((level == 2) && !root->left && root->right) out << " _";
    bool left = outLevel(root->left, level - 1, out);
    bool right = outLevel(root->right, level - 1, out);
    if ((level == 2) && root->left && !root->right) out << " _";
    return left || right;
} // end outLevel()

/** Return a level order traversal of a BST as a string */
template<typename T>
string BST<T>::toString() const
{
    stringstream out;
    if (root == NULL) out << " empty";
    else
    {
        int level = 0;
        do
        {
            out << endl << "  " << ++level << ":";
        } while (outLevel(root, level, out));
    }
    return out.str();
} // end toString()


#endif //LAB08_BST_BST_H
