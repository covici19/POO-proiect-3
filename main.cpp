// DICTIONAR - TEMA 3 POO
#include <iostream>
using namespace std;

template <class K, class V>
class node
{
    K key;
    V val;
    node <K, V>*left, *right;
    int height;
public:
    node()
    {
        left = right = NULL;
        height = 1;
        /*
        val = ;
        key = ;
        */
    }
    node(K k, V v)
    {
        key = k;
        val = v;
        left = right = NULL;
        height = 1;
    }
    void print()
    {
        cout<<endl<<key<<"  ->  "<<val;
    }
    /*
    void setHeight(int h)
    {
        height = h;
    }
*/
    /*
    K getKey();
    V getValue();
    node <K, V>* getLeft();
    node <K, V>** getRight()
    {
        return &right;
    }
    int getHeight();
    */
    template <class Kprim, class Vprim> friend class Dictionary;
};

template <class K, class V>
class Dictionary
{
    node <K, V> *root;
public:
    Dictionary()
    {
        root=NULL;
    }
    Dictionary(const Dictionary &d)
    {
        this->root = d.root;
    }
    bool isempty ();
    int max(int,int);
    int getheight(node<K, V>*);
    node <K, V> *insert(node <K, V> *rnode, K key, V val);
    void insertPair(K key, V value);
    node <K, V> *rightRotate(node <K, V>*);
    node <K, V> *leftRotate(node <K, V>*);
    int getbalance(node<K, V>*);
    V findvalue (K key);
    void inorder();
    void inorderRec(node <K, V>*);
    template <class Kprim,class Vprim>
    friend ostream &operator << (ostream &out, Dictionary <K, V> &d);
    V operator[](const K);
    void delAll();
    node<K, V>* del(node<K, V>*, K);
    node<K, V>* nodmin(node<K, V>*);
    void delnode(K key);
};
template <class K,class V>
bool Dictionary <K, V> ::isempty()
{
    if(root == NULL) return true;
    return false;
}
template <class K,class V>
int Dictionary <K, V> ::max(int a,int b)
{
    return (a>b)?a:b;
}

template <class K,class V>
int Dictionary <K, V>::getheight(node <K, V>*n)
{
    if(n == NULL)
        return 0;
    else
        return n->height;
}
template <class K,class V>
int Dictionary <K, V> ::getbalance(node <K, V> *n)
{
    if(n == NULL)
        return 0;
    else
        return (getheight(n->left)-getheight(n->right));
}

template <class K, class V>
V Dictionary <K, V> :: findvalue (K key)
{
    node <K, V> *n = root;
    while(n->key != key)
    {
        if(key < n->key) n = n->left;
        else if(key > n-> key) n = n->right;
        else if (key == n->key) break;
    }
    return n->val;
}

template <class K,class V>
node <K, V>* Dictionary <K, V>::rightRotate(node <K, V> *y)
{
    node<K, V> *x = y->left;
    node<K, V> *xr = x->right;

    x -> right = y;
    y -> left = xr;

    y->height = max(getheight( y->left ),getheight(y -> right)) + 1;
    x->height = max(getheight( x->left ),getheight(x -> right)) + 1;
    return x;
}
template <class K,class V>
node<K, V>* Dictionary<K, V>::leftRotate(node<K, V> *y)
{
    node<K, V> *x = y->right;
    node<K, V> *t2 = x->left;

    x->left = y;
    y->right = t2;

    y->height = max(getheight( y->left ),getheight(y -> right)) + 1;
    x->height = max(getheight( x->left ),getheight(x -> right)) + 1;

    return x;
}
template <class K,class V>
node<K, V>* Dictionary <K, V>::insert(node<K, V> *rnode, K key, V val)
{
    if(rnode == NULL)
        return new node <K, V>(key, val);

    if(key < rnode->key)
        rnode->left = insert(rnode -> left, key, val);
    else if(key > rnode->key)
        rnode->right = insert(rnode -> right, key, val);
    else if(key == rnode -> key) //overwrite prev value
    {
        rnode -> val = val;
        return rnode;
    }
    else
        return rnode;

    rnode->height = 1 + max(getheight(rnode->left), getheight(rnode->right));
    int balance = getbalance(rnode);

//LL
    if(balance > 1 && key < rnode->left->key)
        return rightRotate(rnode);

//RR
    if(balance < -1 && key > rnode->right->key)
        return leftRotate(rnode);

//LR
    if(balance > 1 && key > rnode->left->key)
    {
        rnode->left = leftRotate(rnode->left);
        return rightRotate(rnode);
    }

//RL
    if(balance < -1 && key < rnode->right->key)
    {
        rnode->right = rightRotate(rnode->right);
        return leftRotate(rnode);
    }

    return rnode;

}
template <class K,class V>
void Dictionary <K, V>::inorder()
{
    inorderRec(root);
}
template <class K,class V>
void Dictionary <K, V>::inorderRec(node <K, V> *n)
{
    if(n)
    {
        inorderRec(n->left);
        n->print();
        inorderRec(n->right);
    }
}
template <class K, class V>
ostream &operator << (ostream &out, Dictionary <K, V> &d)
{
    if(d.isempty() == true) cout<< endl <<"Empty"<<endl;
    else
    d.inorder();
}
template <class K, class V>
V Dictionary <K, V>::operator[](const K key)
{
    return this->findvalue(key);
}
template <class K, class V>
void Dictionary<K, V> :: delAll()
{
    Dictionary <K, V> d;
    *this = d;
}
template <class K,class V>
void Dictionary <K, V>::insertPair(K key,V val)
{
    root = insert(root, key, val);
}
template <class K, class V>
node<K, V>* Dictionary<K, V> :: nodmin(node<K, V>* nnode)
{
    node<K, V>* n = nnode;
    while (n->left != NULL)
        n = n->left;

    return n;
}

template <class K, class V>
node<K, V>* Dictionary <K, V> :: del(node<K, V>* rnode, K key)
{
    if (rnode == NULL)
        return rnode;

    if ( key < rnode->key )
        rnode->left = del(rnode->left, key);

    else if( key > rnode->key )
        rnode->right = del(rnode->right, key);
    else
    {
        if( (rnode->left == NULL) ||
            (rnode->right == NULL) )
        {
            node<K, V> *temp = rnode->left ? rnode->left : rnode->right;
            if (temp == NULL)
            {
                temp = rnode;
                rnode = NULL;
            }
            else
            *rnode = *temp;
            free(temp);
        }
        else
        {
            node<K, V>* temp = nodmin(rnode->right);
            rnode->key = temp->key;
            rnode->right = del(root->right, temp->key);
        }
    }
    if (rnode == NULL)
    return rnode;

    rnode->height = 1 + max(getheight(rnode->left), getheight(rnode->right));
    int balance = getbalance(rnode);

 //LL
    if (balance > 1 && getbalance(rnode->left) >= 0)
        return rightRotate(rnode);
 //LR
    if (balance > 1 && getbalance(rnode->left) < 0)
    {
        rnode->left = leftRotate(rnode->left);
        return rightRotate(rnode);
    }

 //RR
    if (balance < -1 && getbalance(rnode->right) <= 0)
        return leftRotate(rnode);

 //RL
    if (balance < -1 && getbalance(rnode->right) > 0)
    {
        rnode->right = rightRotate(rnode->right);
        return leftRotate(rnode);
    }

    return rnode;
}
template <class K,class V>
void Dictionary <K, V>::delnode(K key)
{
    root = del(root, key);
}

int main()
{
    Dictionary <int, string> d1;
    Dictionary <string, string> d2;

    d2.insertPair("q","qwerty");
    d2.insertPair("P","poo");
    d2.insertPair("a","amandina");
    d2.insertPair("/","comment");
    d2.insertPair("5","cinci");

    cout<<"Afisare d2:"<<endl;
    cout<<d2;
    cout<<endl<<endl<<"Valoarea accesata cu cheia P este: "<< d2.findvalue("P")<<endl;
    cout<<"d2[5] = "<<d2["5"]<<endl;
    cout<<endl<<"Stergerea tuturor elementelor din d2";
    d2.delAll();
    cout<<d2;
    cout<<endl;

    d1.insertPair(10,"10");
    d1.insertPair(30,"30");
    d1.insertPair(40,"40");
    d1.insertPair(50,"50");
    d1.insertPair(25,"25");

    cout<<"Afisare d1:"<<endl<<d1;
    cout<<endl;
    cout<<endl<<"Stergem elementului cu cheia 40 si adaugam elementul (10, 20)"<<endl;
    d1.insertPair(10,"20"); //suprascrie prima valoare
    d1.delnode(40);
    cout<<d1;

    return 0;
}
