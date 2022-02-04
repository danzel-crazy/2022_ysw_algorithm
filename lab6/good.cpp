#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool insert_fail = 0, erase_fail = 0, enum_fail = 0, find_fail = 0;
vector <pair<string, string>> ans;

struct Node {
	string key, value; // holds the key and value
	Node *parent; // pointer to the parent
	Node *left; // pointer to left child
	Node *right; // pointer to right child
};

typedef Node* node;

class splay_tree{
    private:
        void inorder(node x, string small, string large) {
            if (x != nullptr && x->key >= small &&x->key <= large) {
                inorder(x->left, small, large);
                ans.push_back(make_pair(x->key, x->value));
                inorder(x->right, small, large);
            } 
	    }

        void new_inorder(node small, node large){
            while(small && small->key <= large->key){
                ans.push_back(make_pair(small->key,small->value));
                small = successor(small);
            }
        }

        //search operation
        node search(node x, string key){
            if(x == nullptr || key == x->key){
                return x;
            }

            if(key < x->key){
                return search(x->left, key);
            }
            else{
                return search(x->right, key);
            }
        }

        //delete operation
        void del(node x, string key){
            node temp = nullptr;
            node s, r;

            while(x != nullptr){
                if(x->key == key){
                    temp = x;
                }

                if(x->key <= key){
                    x = x->left;
                }
                else{
                    x = x->right;
                }
            }

            if(temp == nullptr){
                erase_fail = 1;
                //cout << 1 << endl;
                return;
            }
            
            split(temp,s,r);
            if(s->left){
                s->left->parent = nullptr;
            }
            root = join(s->left, r);
            delete(s);
            s = nullptr;
        }

        //rotate left by node x
        void left_rotate(node x){
            node y = x->right;  //y will b the parent of x
            x->right = y->left; // move y->left to x

            if(y->left != nullptr){ //if y->left is nil, ignore
                y->left->parent = x;
            }
            y->parent = x->parent; //refresh y->parent

            if(x->parent == nullptr){ //y becone root 
                this->root = y;
            }
            else if(x == x->parent->left){ //if y is not root
                x->parent->left = y;
            }
            else{
                x->parent->right = y; 
            }

            y->left = x;
            x->parent = y;
        }

        //rotate right by node x
        void right_rotate(node x){
            node y = x->left;
            x->left = y->right;

            if(y->right != nullptr){
                y->right->parent = x;
            }

            y->parent = x->parent;

            if(x->parent == nullptr){
                this->root = y;
            }
            else if(x == x->parent->left){
                x->parent->left = y;
            }
            else{
                x->parent->right = y;
            }
            y->right = x;
            x->parent = y;
        }

        //main port of splay tree
        void splay(node x){
            while(x->parent){
                if(x->parent->parent == nullptr){
                    if(x == x->parent->left){ 
                        right_rotate(x->parent);  //Zig
                    }
                    else{   
                        left_rotate(x->parent);  //Zag
                    }
                }
                else if(x == x->parent->left && x->parent == x->parent->parent->left){ //Zig-Zig
                    right_rotate(x->parent);
                    right_rotate(x->parent);
                }
                else if(x == x->parent->left && x->parent == x->parent->parent->right){ //Zag-Zig
                    right_rotate(x->parent);
                    left_rotate(x->parent);
                }
                else if(x == x->parent->right && x->parent == x->parent->parent->right){ //Zag-Zag
                    left_rotate(x->parent);
                    left_rotate(x->parent);
                }
                else{ //Zig-Zag
                    left_rotate(x->parent);
                    right_rotate(x->parent);
                }
            }
        }

        node join(node s, node t){
            if(!s){
                return t;
            }

            if(!t){
                return s;
            }

            node x = maximum(s);
            splay(x);
            x->right = t;
            t->parent = x;
            return x;
        }

        void split(node &x, node &s, node &t){
            splay(x);
            if(x->right){
                t = x->right;
                t->parent = nullptr;
            }
            else{
                t = nullptr;
            }

            s = x;
            s->right = nullptr;
            x = nullptr;
        }


    public:
        node root;

        splay_tree(){
            root = nullptr;
        }

        node successor(node x){
            if(x->right != nullptr){
                return minimum(x->right);
            }

            node y = x->parent;
            while(y != nullptr && x == y->right){
                x = y;
                y = y->parent;
            }
            return y;
        }

        node search_tree(string key){
            node x = search(this->root, key);
            if(x){
                splay(x);
            }
            return x;
        }

        node minimum(node x){
            while(x->left != nullptr){
                x = x->left;
            }
            return x;
        }

        node maximum(node x){
            while(x->right != nullptr){
                x = x->right;
            }
            return x;
        }

        void insert(string key, string value){
            if(search_tree(key) != nullptr){
                insert_fail = 1;
                return;
            } 

            node x = new Node;
            x->parent = nullptr;
            x->left = nullptr;
            x->right = nullptr;
            x->key = key;
            x->value = value;

            node a = nullptr;
            node b = this->root;

            while(b != nullptr){
                a = b;
                if(x->key < b->key){
                    b = b->left;
                }
                else{
                    b = b->right;
                }
            }

            x->parent = a;
            if(a == nullptr){
                root = x;
            }
            else if(x->key < a->key){
                a->left = x;
            }
            else{
                a->right = x;
            }

            splay(x);

            insert_fail = 0;
        }
        
        void deletenode(string key){
            del(this->root, key);
        }

        void clear(node x){
            if(x != nullptr){
                clear(x->left);
                clear(x->right);
                delete x;
                x = nullptr;
            }
        }

        void enums(string k1, string k2){
            node large = search_tree(k2);
            node small = search_tree(k1);
            //cout << small->key << " " << large->key << endl;
            
            if(small == nullptr){
                small = minimum(this->root);
                splay(small);
            }
            if(large == nullptr){
                large = maximum(this->root);
            }
            else if(small == large){
                ans.push_back(make_pair(small->key, small->value));
                return;
            }
            //inorder(this->root, small->key, large->key);
            new_inorder(small, large);
        }
};

int main(){ 
    ifstream infile;
    infile.open("input.txt");
    ofstream outfile;
    outfile.open("output.txt");
        int constarint = 300000;
        splay_tree a;
        string command, num, key, val;
        string key1 , val1, key2, val2;
        
        while(infile >> command){
            //erase
            if(command == "ERASE"){
                infile >> key;
                string tkey = key.substr(4, key.size()-1);
                //cout << tkey << endl;
                node ans = a.search_tree(tkey);
                if(ans == nullptr){
                    outfile << "ERASE " << tkey << " FAIL!" << "\n";
                }
                else{
                    a.deletenode(tkey);
                    if(erase_fail){
                        outfile << "ERASE " << tkey << " FAIL!" << "\n";
                        //cout << "ERASE " << tkey << " FAIL!" << "\n";
                    }
                
                    else{
                        outfile << "ERASE " << tkey << " SUCCESS!" << "\n";
                        //cout << "ERASE " << tkey << " SUCCESS!" << "\n";
                    }
                }
                
            }

            //insert
            else if(command == "INSERT"){  
                infile >> key >> val;
                string tkey = key.substr(4, key.size()-1);
                string tval = val.substr(6, val.size()-1);
                //cout << tkey << " " << tval << endl;
                if(constarint--){
                    a.insert(tkey, tval);
                    if(insert_fail){
                        outfile << "INSERT " << tkey << " FAIL!" << '\n'; 
                        //cout << "INSERT " << tkey << " FAIL!" << '\n'; 
                    }
                    else{
                        outfile << "INSERT " << tkey << " SUCCESS!" << '\n';
                        //cout << "INSERT " << tkey << " SUCCESS!" << '\n';
                    }
                }
                else{
                    outfile << "INSERT " << tkey << " FAIL!" << '\n';
                    //cout << "INSERT " << tkey << " FAIL!" << '\n';
                }
            }

            //search
            else if(command == "FIND"){
                infile >> key;
                string tkey = key.substr(4, key.size()-1);
                
                node ans = a.search_tree(tkey);
                if(ans != nullptr){
                    outfile << "FIND " << ans->key << ":" <<  ans->value << "!"  << '\n'; 
                    //cout << "FIND " << ans->key << ":" <<  ans->value << "!"  << '\n'; 
                }
                else{
                    outfile << tkey << " NOT FOUND!"  << '\n';
                    //cout << tkey << " NOT FOUND!"  << '\n';
                }
            }

            //enum
            else if(command == "ENUM"){
                infile >> key1 >> key2;

                string tkey1 = key1.substr(4, key1.size()-1);
                //cout << tkey << endl;
                string tkey2 = key2.substr(4, key2.size()-1);
                
                a.enums(tkey1,tkey2);
                for(auto v :ans){
                    outfile << "ENUM " << v.first << ":" << v.second << "\n";
                    //cout << "ENUM " << v.first << ":" << v.second << "\n";
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