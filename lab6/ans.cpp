#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

bool insert_fail = 1, erase_fail = 1, enum_fail = 1, find_fail = 1;
vector <pair<string, string>> ans;

class node{
    public:
        string val, key;
        node *left, *right, *parent;
};

class tree{
    public:
    node* root;
    tree():root(NULL){};

    //Leftmost
    node* smallest(node *x){
        while(x->left != NULL){
            x= x->left;
        }
        return x;
    }

    //Rightmost
    node* largest(node *x){
        while(x->right != NULL){
            x= x->right;
        }
        return x;
    }

    //successor
    node* successor(node *x){
        if(x->right != NULL){
            return smallest(x->right);
        }

        node *new_node = x->parent;

        while(new_node != NULL && x == new_node->right){
            x = new_node;
            new_node = new_node->parent;
        }

        return new_node;
    }

    //inorder
    void inorder(node *small, node *large){
        while(small && small->key <= large->key){
            ans.push_back(make_pair(small->key,small->val));
            small = successor(small);
        }
    }

    //levelorder
    void levelorder(){
        queue <node*> q;
        q.push(this->root);

        while(!q.empty()){
            node *current = q.front();

            q.pop();
            //cout << current->key << " ";

            if(current->left != NULL){
                q.push(current->left);
            }
            if(current->right != NULL){
                q.push(current->right);
            }
        }
    }

    //preorder
    void preorder(node *x){
        if(x != NULL){
            cout << x->key << " ";
            preorder(x->left);
            preorder(x->right);
        }
    }

    node *right_rotate(node *x){
        node *y = x->left;  
        x->left = y->right;
        if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
        return y;
    }

    node *left_rotate(node *x){
        node *y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
        return y;
    }

    node* splay(node *root, node *x){
        
        if(root == NULL || root->key == x->key){
            return root;
        }

        //key in left-tree
        if(root->key > x->key){
            if(root->left == NULL) return root;

            //Zig-Zig(left left)
            if(root->left->key > x->key){
                root->left->left = splay(root->left->left, x);
                root = right_rotate(root);
            }
            //Zig-Zag(left right)
            else if(root->left->key < x->key){
                root->left->right = splay(root->left->right, x);
   
                if (root->left->right != NULL)
                    root->left = left_rotate(root->left);
            }

            return (root->left == NULL)? root : right_rotate(root);
        }

        else{
            if(root->right == NULL) return root;

            //Zag-Zig (right left)
            if(root->right->key > x->key){
                root->right->left = splay(root->right->left, x);

                if(root->right->left != NULL){
                    root->right = right_rotate(root->right);
                }
            }

            //Zag-Zag (right right)
            else if(root->right->key < x->key){
                root->right->right = splay(root->right->right, x);
                root = left_rotate(root);
            }

            return (root->right == NULL)? root : left_rotate(root);
        }
    }

    void insert(node *x){
        node * b = NULL;
        node * a = NULL;

        a = root;
        while(a != NULL){
            //cout << a->key << endl;
            b = a;
            if(x->key > a->key){
                
                a = a->right;
            }
            else a = a->left;
        }

        x->parent = b;
        
        if(b == NULL){
            root = x;
            insert_fail = 0;
        }
        else if(x->key < b->key){
            b->left = x;
            insert_fail = 0;
            root = splay(root, x);
        }
        else if(x->key > b->key){
            b->right = x;
            insert_fail = 0;
            root = splay(root, x);
        }
        else{
            insert_fail = 1;
            return;
        }
    }

    void erase(string key){
        node *delete_node = find(key);
        if(delete_node == NULL){
            erase_fail = 1;
            return;
        }

        node *temp;
        if(!delete_node->left){
            temp = delete_node;
            delete_node = delete_node->right;
        }
        else{
            temp = delete_node;
            root = splay(root, delete_node->left);
            delete_node->right = temp->right;
        }

        delete temp;
        erase_fail = 0;
    }

    node* find(string key){
        node *current = root;
        
        while(current != NULL && key != current->key){  
            if(key < current->key){
                current = current->left;
            }
            else{
                current = current->right;
            }
        }
        if(current == NULL){
            return current;
        }
        else{
            find_fail = 0;
            root = splay(root, current);
            return current;
        }
    }

    void print(string a, string b){
        node* small = find(a);
        node* large = find(b);

        if(small == NULL){
            node* small = smallest(root);
        }
        if(large == NULL){
            node *large = largest(root);
        }
        if(small == NULL && large == NULL){
            enum_fail = 1;
            return;
        }
        else if(small == large){
            ans.push_back(make_pair(small->key, small->val));
            return;
        }

        inorder(small, large);
    }

    //delete postorder
    void clear(node* x){
        if(x != NULL){
            preorder(x->left);
            preorder(x->right);
            delete x;
            x = NULL;
        }
    }
};

node* newNode(string key, string val)
{
    node* Node = new node();
    Node->val = val;
    Node->key = key;
    Node->left = Node->right = Node->parent = NULL;
    return Node;
}

int main(){
    ifstream infile;
    infile.open("input.txt");
    ofstream outfile;
    outfile.open("tryout.txt");
        int constarint = 300000;
        tree a;
        string command, num, key, val;
        string key1, val1, key2, val2;

        
        while(infile >> command){
            //erase
            if(command == "ERASE"){
            infile >> key;
            

            string tkey(key.begin()+4, key.end());
            //cout << tkey << endl;
            a.erase(tkey);
            
            if(!erase_fail){
                outfile << "ERASE " << tkey << " SUCCESS!" << "\n"; 
                //cout << "ERASE " << tkey << " SUCCESS!" << "\n"; 
            }
            else{
                outfile << "ERASE " << tkey << " FAIL!" << "\n"; 
                //cout << "ERASE " << tkey << " FAIL!" << "\n"; 
            }

            // cout << "pre: ";
            // a.preorder(a.root);
            // cout << "\n";
            }

            //insert
            else if(command == "INSERT"){
                
                infile >> key >> val;

                string tkey(key.begin()+4, key.end());
                //cout << tkey << endl;
                string tval(val.begin()+6, val.end());

                if(constarint--){
                    node* x = newNode(tkey, tval);
                    a.insert(x);

                    if(!insert_fail){
                        outfile << "INSERT " << x->key << " SUCCESS!" << '\n';
                        //cout << "INSERT " << x->key << " SUCCESS!" << '\n';
                    }
                    else{
                        outfile << "INSERT " << x->key << " FAIL!" << '\n';
                        //cout << "INSERT " << x->key << " FAIL!" << '\n';
                        delete x;
                    }
                }
                else{
                    outfile << "INSERT " << tkey << " FAIL!" << '\n';
                }
                
                // cout << "pre: ";
                // a.preorder(a.root);
                // cout << "\n";
            }

            //search
            else if(command == "FIND"){
                infile >> key;

                string tkey(key.begin()+4, key.end());
                
                node* ans = a.find(tkey);
            
                if(ans == NULL){
                    outfile << tkey << " NOT FOUND!"  << '\n';
                    //cout << tkey << " NOT FOUND!"  << '\n';
                }
                else{
                    outfile << "FIND " << ans->key << ":" <<  ans->val << "!"  << '\n';
                    //cout << "FIND " << ans->key << ":" <<  ans->val << "!"  << '\n';
                }
            }

            //enum
            else if(command == "ENUM"){
                infile >> key1 >> key2;

                string tkey1(key1.begin()+4, key1.end());
                //cout << tkey << endl;
                string tkey2(key2.begin()+4, key2.end());
                a.print(tkey1, tkey2);

                for(auto v :ans){
                    outfile << "ENUM " << v.first << ":" << v.second << "\n";
                }
                ans.clear();
            }

            else if(command == "CLEAR"){
                a.clear(a.root);
            }
        }

    infile.close();
    outfile.close();
    return 0;
}