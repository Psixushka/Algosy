#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>


using namespace std;

class Node
{
public:
    Node(int data)
    {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
    int data;
    Node* left;
    Node* right;


};

class AVLNode
{
public:
    AVLNode()
    {
        this->key = key;
        height = 0;
        Left = nullptr;
        Right = nullptr;

    }
    int key;
    int height;
    AVLNode* Left;
    AVLNode* Right;
};


class BinaryTree
{
private:
    Node* root;

public:
    BinaryTree()
    {
        root = nullptr;
    }

    Node* getRoot() {
        return root;
    }

    void insert(int x)
    {
        root = InsertRec(root, x);
    }

    Node* InsertRec(Node* node, int x)
    {
        if (node == nullptr)
        {
            return new Node(x); 
        }

        if (x < node->data) 
        {
            node->left = InsertRec(node->left, x);
        }
        else if (x > node->data)
        {
            node->right = InsertRec(node->right, x);
        }

        return node;
    }


    bool isValidInputChar(char ch)
    {
        return isdigit(ch) || ch == '(' || ch == ')' || ch == ' ';
    }

    void buildTreeFromString(const string& str)
    {
        int cpcount = 0;
        int opcount = 0;
        stringstream ss(str);
        if (!isValidInput(ss.str()))
        {
            cerr << "Invalid input format." << endl;
            return;
        }

        buildTree(ss, root, opcount, cpcount);
    }

    bool isValidInput(const string& str)
    {
        for (char ch : str)
        {
            if (!isValidInputChar(ch))
            {
                return false;
            }
        }
        return true;
    }

    void buildTree(stringstream& ss, Node*& node, int& openParentheses, int& closeParentheses)
    {
        char ch;
        ss >> ch;

        if (ch != '(')
        {
            cerr << "Error: Expected (" << endl;
            return;
        }

        
        int value;
        ss >> value;
        node = new Node(value);

        if (ss.eof())
        {
            cerr << "Error: Unexpected end of input" << endl;
            return;
        }

        if (ss.peek() == ')')
        {
            ss >> ch; 
            closeParentheses++;
            return;
        }

        buildTree(ss, node->left, openParentheses, closeParentheses);

        if (ss.eof())
        {
            cerr << "Error: Unexpected end of input" << endl;
            return;
        }

        if (ss.peek() == ')')
        {
            ss >> ch; 
            closeParentheses++;
            return;
        }

        buildTree(ss, node->right, openParentheses, closeParentheses);

        if (ss.eof())
        {
            cerr << "Error: Unexpected end of input" << endl;
            return;
        }

        if (ss.peek() == ')')
        {
            ss >> ch; 
            closeParentheses++;
        }
        else
        {
            cerr << "Error: Expected )" << endl;
        }
    }

    void DFS(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }

        cout << node->data << " ";

        DFS(node->left);
        DFS(node->right);
    }

    void PrintDFS()
    {
        DFS(root);
        cout << "\n";
    }


};



class AVLTree
{
private:
    AVLNode* root;
public:
    AVLTree()
    {
        root = nullptr;
    }

    AVLNode* getRoot() {
        return root;
    }

    int max(int a, int b)
    {
        if (a < b) {
            return b;
        }
        else return a;

    }

    int GetSize(AVLNode* node)
    {
        if (!node)
        {
            return 0;
        }
        return node->height;
    }

    AVLNode* newNode(int key)
    {
        AVLNode* node = new AVLNode();
        node->key = key;
        node->Left = NULL;
        node->Right = NULL;
        node->height = 1; 
        return(node);
    }

    AVLNode* RRotate(AVLNode* y) 
    {
        AVLNode* x = y->Left;
        AVLNode* T2 = x->Right;

         
        x->Right = y;
        y->Left = T2;
 
        y->height = max(GetSize(y->Left), GetSize(y->Right)) + 1;
        x->height = max(GetSize(x->Left), GetSize(x->Right)) + 1;

    
        return x;

    }

    AVLNode* LRotate(AVLNode* x) 
    {
        AVLNode* y = x->Right;
        AVLNode* T2 = y->Left;

        y->Left = x;
        x->Right = T2;

   
        x->height = max(GetSize(x->Left), GetSize(x->Right)) + 1;
        y->height = max(GetSize(y->Left), GetSize(y->Right)) + 1;

  
        return y;

    }

    int Balance(AVLNode* node)
    {
        return GetSize(node->Left) - GetSize(node->Right);

    }

    AVLNode* insert(AVLNode* node, int key)
    {
        if (!node) {
            return newNode(key);
        }

        if (key < node->key)
        {
            node->Left = insert(node->Left, key);
        }
        else if (key > node->key)
        {
            node->Right = insert(node->Right, key);
        }
        else
        {
            return node; 
        }

       

        node->height = 1 + max(GetSize(node->Left), GetSize(node->Right));

        int balance = Balance(node);

        
        if (balance > 1 && key < node->Left->key)
        {
            return RRotate(node);
        }

        if (balance < -1 && key > node->Right->key)
        {
            return LRotate(node);
        }

        if (balance > 1 && key > node->Left->key)
        {
            node->Left = LRotate(node->Left);
            return RRotate(node);
        }

      
        if (balance < -1 && key < node->Right->key)
        {
            node->Right = RRotate(node->Right);
            return LRotate(node);
        }

        return node;

    }

    void insert(int key)
    {
        root = insert(root, key);
    }

    AVLNode* deleteMin(AVLNode* node) {
        if (node->Left == nullptr)
        {
            return node->Right;
        }
        node->Left = deleteMin(node->Left);
        node->height = 1 + GetSize(node->Left) + GetSize(node->Right);
        return node;
    }

    AVLNode* getMin(AVLNode* node) {

        if (!node->Left)
        {
            return node;
        }
        return getMin(node->Left);
    }


    AVLNode* deleteNode(AVLNode* root, int key)
    {
        if (root == NULL)
            return root;

        if (key < root->key)
            root->Left = deleteNode(root->Left, key);

        else if (key > root->key)
            root->Right = deleteNode(root->Right, key);

        else
        {
            if ((root->Left == NULL) ||
                (root->Right == NULL))
            {
                AVLNode* temp = root->Left ?
                    root->Left :
                    root->Right;

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;
                free(temp);
            }
            else
            {
                AVLNode* temp = minValueNode(root->Right);

                root->key = temp->key;

                
                root->Right = deleteNode(root->Right, temp->key);
            }
        }

        if (root == NULL)
            return root;

          
        root->height = 1 + max(GetSize(root->Left), GetSize(root->Right));

        
        int balance = Balance(root);

       

        
        if (balance > 1 && Balance(root->Left) >= 0)
            return RRotate(root);

         
        if (balance > 1 && Balance(root->Left) < 0) {
            root->Left = LRotate(root->Left);
            return RRotate(root);
        }
       
        if (balance < -1 && Balance(root->Right) <= 0)
            return LRotate(root);

        if (balance < -1 && Balance(root->Right) > 0) {
            root->Right = RRotate(root->Right);
            return LRotate(root);
        }
        return root;
    }

    AVLNode* minValueNode(AVLNode* node)
    {
        AVLNode* current = node;
        while (current->Left)
        {
            current = current->Left;
        }
        return current;
    }

    void deleteNode(int key)
    {
        root = deleteNode(root, key);
    }

    AVLNode* search(AVLNode* root, int key) {
        if (!root || root->key == key) {
            return root;
        }

        if (key < root->key) {
            return search(root->Left, key);
        }
        else {
            return search(root->Right, key);
        }
    }

    AVLNode* search(int key)
    {
        return search(root, key);
    }

    void CurrentLevelCheck(AVLNode* root, int l)
    {
        if (root == nullptr) {
            return;
        }
        if (l == 0) {
            cout << root->key << " ";
        }
        else if (l > 0)
        {
            CurrentLevelCheck(root->Left, l - 1);
            CurrentLevelCheck(root->Right, l - 1);
        }

    }
    void BFS(AVLNode* root)
    {
        int h = GetSize(root);
        for (int l = 0; l < h; l++)
        {
            CurrentLevelCheck(root, l);
        }
    }

    void preorderIterative() {
        preorderIterative(root);
        cout << "\n";
    }

    void preorderIterative(AVLNode* root)
    {
        if (root) {

      
            if (!(root->Left) && !(root->Right)) {
                cout << root->key << endl;
                return;
            }

  
            vector<AVLNode*> list;
            list.push_back(root);


            AVLNode* L = root->Left;
            while (L->Left) {
                list.push_back(L);
                L = L->Left;
            }
            queue<AVLNode*> q;
            q.push(root);
            while (!q.empty()) {
                AVLNode* temp = q.front();
            q.pop();
            if (!(temp->Left) && !(temp->Right)) {
                list.push_back(temp);
            }
            if (temp->Left) {
                q.push(temp->Left);
            }
            if (temp->Right) {
                q.push(temp->Right);
            }
        }

   
            vector<AVLNode*> list_r;
            AVLNode* R = root->Right;
            while (R->Right) {
                list_r.push_back(R);
                R = R->Right;
            }

         
            reverse(list_r.begin(), list_r.end());

         
            list.insert(list.end(), list_r.begin(),
                list_r.end());

        
            for (auto i : list) {
                cout << i->key << " ";
            }
            cout << endl;
            return;
        }
    }

    void BFS() {
        BFS(root);
        cout << "\n";
    }

    void DFSPrefix() {
        DFSPrefix(root);
        cout << "\n";
    }

    void DFSInfix() {
        DFSInfix(root);
        cout << "\n";
    }

    void DFSPostfix() {
        DFSPostfix(root);
        cout << "\n";
    }
    void DFSPrefix(AVLNode* node) {
        if (!node) return;
        cout << node->key << " ";
        DFSPrefix(node->Left);
        DFSPrefix(node->Right);
    }

    void DFSInfix(AVLNode* node) {
        if (!node) return;

        DFSInfix(node->Left);
        cout << node->key << " ";
        DFSInfix(node->Right);
    }

    void DFSPostfix(AVLNode* node) {
        if (!node) return;

        DFSPostfix(node->Left);
        DFSPostfix(node->Right);
        cout << node->key << " ";
    }
};

void AVLFromBin(Node* binaryNode, AVLTree& avlTree)
{
    if (binaryNode)
    {
        avlTree.insert(binaryNode->data);
        AVLFromBin(binaryNode->left, avlTree);
        AVLFromBin(binaryNode->right, avlTree);
    }
}


int main()
{
    setlocale(0, "rus");
    AVLTree avl;
    BinaryTree tree;
    string inputString;
    ifstream inputFile("laba.txt");
    string line;
    getline(inputFile, line);

    if (!tree.isValidInput(line))
    {
        cerr << "Ошибка" << endl;
        return 1;
    }

    tree.buildTreeFromString(line);

    AVLFromBin(tree.getRoot(), avl);

    cout << "Обход бинарного дерева  ";
    tree.PrintDFS();

    cout << "\nОбход дерева АВЛ в ширину ";
    avl.BFS();

    cout << "\nПрефиксный обход дерева в глубину ";
    avl.DFSPrefix();

    cout << "\nИнфиксный обход дерева в глубину ";
    avl.DFSInfix();

    cout << "\nПостфиксный обход дерева в глубину ";
    avl.DFSPostfix();

    cout << "\nИтеративный обход границ:";
    avl.preorderIterative();

    return 0;
}