#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "iostream"

using namespace std;

template <typename Key, typename Info>
class Dictionary
{

    private:
        struct Node{
            Node *left;
            Node *right;
            Key key;
            Info info;
            int height;
            int bf;
            Node(Key key, Info info):left(nullptr), right(nullptr), key(key), info(info), height(0), bf(0){}
            Node(Node *left, Node *right, Key key, Info info, int height, int bf):left(left), right(right), key(key), info(info), height(height), bf(bf){}
        };

    private:
        Node *root;



    public:
        Dictionary():root(nullptr){};
        Dictionary(const Dictionary& basic){root = copy(basic.root);}
        ~Dictionary();

        // Modifiers
        void insert(const Key key, const Info info);
        void remove(const Key &key);
        void clear();

        // Print
        void printInOrder(){printInOrder(root);}
        void printPostOrder(){printPostOrder(root);}
        void printPreOrder(){printPreOrder(root);}
        void print_t();



        // Informations
        int getHeight(){return root ? root->height: 0;}
        bool contain(const Key& key) const{return contain(key, root);}
        bool isEmpty()const{if(root == nullptr) return true; return false;}

        //Access
        Key getValue(const Key key){return getNode(key, root)->info;}
        Key getMin(){return getMinNode(root);}
        Key getMax(){return getMaxNode(root);}

        //operators
        Dictionary& operator=(const Dictionary& basic){ clear(); root = copy(basic.root); return *this;};

    private:
        Node *insert(const Key &key, const Info &info, Node *root);
        void printInOrder(Node *root);
        void printPostOrder(Node *root);
        void printPreOrder(Node *root);
        Node* remove(const Key key, Node *root);
        Key getMinNode(Node *root);
        Key getMaxNode(Node *root);
        Node *getNode(const Key &key, Node *root);
        void updateHeight(Node *node) noexcept;
        int getHeight(Node *root);
        Node* balance(Node *root) noexcept;
        Node* lrotation(Node *root) noexcept;
        Node* rrotation(Node *root) noexcept;
        Node* llrotation(Node *root) noexcept;
        Node* lrrotation(Node *root) noexcept;
        Node* rlrotation(Node *root) noexcept;
        Node* rrrotation(Node *root) noexcept;
        void clear(Node *root);
        Node* copyTree(Node *root);
        bool contain(const Key& key, Node *root) const;
        int _print_t(Node *tree, int is_left, int offset, int depth, char s[20][255]);
};

//public methods
template <typename Key, typename Info>
void Dictionary<Key, Info>::insert(const Key key, const Info info){
    if(contain(key, root)){
        cout << "Contain" << endl;
        return;
    }

    root = insert(key, info, root);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::clear(){
    clear(root);
    root = nullptr;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::remove(const Key &key){
    if(!contain(key))
        return;

    root = remove(key, root);
}


// private methods
template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::insert(const Key &key, const Info &info, Node *root){
    if(root == nullptr){
        return new Node(nullptr, nullptr, key, info, 0, 0);
    }

    if(key>root->key)
        root->right = insert(key, info, root->right);
    if(key<root->key)
        root->left = insert(key, info,root->left);

    updateHeight(root);
    return balance(root);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::printInOrder(Node *root){
    if(root){
    printInOrder(root->left);
    cout <<"Key: "<< root->key <<" Info: " << root->info << endl;
    printInOrder(root->right);
    }

}

template <typename Key, typename Info>
void Dictionary<Key, Info>::printPostOrder(Node *root){
    if(root){
    printPostOrder(root->left);
    printPostOrder(root->right);
    cout <<"Key: "<< root->key <<" Info: " << root->info << endl;
    }

}

template <typename Key, typename Info>
void Dictionary<Key, Info>::printPreOrder(Node *root){
    if(root){
    cout <<"Key: "<< root->key <<" Info: " << root->info << endl;
    printPreOrder(root->left);
    printPreOrder(root->right);
    }

}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::remove(Key key, Node *root){
   if(root == nullptr)
        return nullptr;

   if(key < root->key)
        root->left = remove(key, root->left);
   else if(key > root->key)
        root->right = remove(key, root->right);
   else{
        if(root->left == nullptr){
            return root->right;
        }else if(root->right == nullptr){
            return root->left;
        }else{
            Node *temp = getNode(getMinNode(root->right), root->right);
            root->info = temp->info;
            root->key = temp->key;

            root->right = remove(temp->key, root->right);
        }
   }
    updateHeight(root);
    return balance(root);
}

template <typename Key, typename Info>
Key Dictionary<Key, Info>::getMinNode(Node *root){
    if(root->left == nullptr)
        return root->key;
    return getMinNode(root->left);
}

template <typename Key, typename Info>
Key Dictionary<Key, Info>::getMaxNode(Node *root){
    if(root->right == nullptr)
        return root->key;
    return getMinNode(root->right);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::getNode(const Key &key, Node *root){
    if(root->key == key || root == nullptr)
    return root;
    if(key < root->key)
        return getNode(key, root->left);

    return getNode(key, root->right);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::updateHeight(Node *root) noexcept{
    int leftHeight;
    int rightHeight;

    if(root->left)
         leftHeight = root->left->height;
    else
        leftHeight = -1;

    if(root->right)
         rightHeight = root->right->height;
    else
        rightHeight = -1;


    root->height = leftHeight > rightHeight ? 1 + leftHeight : 1 + rightHeight;
    root->bf = rightHeight - leftHeight;
}

template <typename Key, typename Info>
int Dictionary<Key, Info>::getHeight(Node* root)
{
    return (root == nullptr ? -1 : root->height);
}


template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::balance(Node *root) noexcept{
    if(root->bf < -1){
        //left left
        if(root->left->bf <= 0)
            return llrotation(root);
        else    //left right
            return lrrotation(root);
    }
    else if(root->bf > 1){
        //right right
        if(root->right->bf >= 0)
            return rrrotation(root);
        else    //right left
            return rlrotation(root);
    }

    //balanced
    return root;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::lrotation(Node *node) noexcept{
    Node *newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;
    updateHeight(node);
    updateHeight(newParent);
    return newParent;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rrotation(Node *node) noexcept{
    Node *newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;
    updateHeight(node);
    updateHeight(newParent);
    return newParent;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::llrotation(Node *root) noexcept{
    return rrotation(root);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::lrrotation(Node *root) noexcept{
    root->left = lrotation(root->left);
    return rrotation(root);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rrrotation(Node *root) noexcept{
    return lrotation(root);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rlrotation(Node *root) noexcept{
    root->right = rrotation(root->right);
    return lrotation(root);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::clear(Node *root){
    if(!root)
        return;
    clear(root->left);
    clear(root->right);
    delete root;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::copyTree(Node *root){
    Node *returnNode = nullptr;
    if(root){
        returnNode = new Node(nullptr, nullptr, root->key, root->info, root->height, root->bf);
        returnNode->left = copyTree(root->left);
        returnNode->right = copyTree(root->right);
    }
    return returnNode;
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::contain(const Key& key, Node *root) const{
    if(!root)
        return false;

    if(key > root->key)
        return contain(key, root->right);
    else if(key < root->key)
        return contain(key, root->left);
    else
        return true;
}

template <typename Key, typename Info>
int Dictionary<Key, Info>::_print_t(Node *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->key);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
    s[depth][offset + left + i] = b[i];

if (depth && is_left) {

    for (int i = 0; i < width + right; i++)
        s[depth - 1][offset + left + width/2 + i] = '-';

    s[depth - 1][offset + left + width/2] = '.';

} else if (depth && !is_left) {

    for (int i = 0; i < left + width; i++)
        s[depth - 1][offset - width/2 + i] = '-';

    s[depth - 1][offset + left + width/2] = '.';
}
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::print_t()
{
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(this->root, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}


#endif // DICTIONARY_H
