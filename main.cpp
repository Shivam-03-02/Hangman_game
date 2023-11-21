#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    Node* lchild;
    string data;
    Node* rchild;
    int height;


};

class AVL{
public:
    Node* root;

    AVL(){ root = nullptr; }

    int NodeHeight(Node* p);
    int BalanceFactor(Node* p);
    Node* LLRotation(Node* p);
    Node* RRRotation(Node* p);
    Node* LRRotation(Node* p);
    Node* RLRotation(Node* p);

    Node* rInsert(Node* p, string key);
    void minsert(Node *p,string key);
    void Inorder(Node* p);
    void Inorder(){ Inorder(root); }
    Node* getRoot(){ return root; }
    Node *search_movie(Node *p,string movie);
};

int AVL::NodeHeight(Node *p) {
    int hl;
    int hr;

    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;

    return hl > hr ? hl + 1 : hr + 1;
}

int AVL::BalanceFactor(Node *p) {
    int hl;
    int hr;

    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;

    return hl - hr;
}

Node* AVL::LLRotation(Node *p) {
    Node* pl = p->lchild;
    Node* plr = pl->rchild;

    pl->rchild = p;
    p->lchild = plr;

    p->height = NodeHeight(p);
    pl->height = NodeHeight(pl);

    if (root == p){
        root = pl;
    }
    return pl;
}

Node* AVL::RRRotation(Node *p) {
    Node* pr = p->rchild;
    Node* prl = pr->lchild;

    pr->lchild = p;
    p->rchild = prl;

    p->height = NodeHeight(p);
    pr->height = NodeHeight(pr);

    if (root == p){
        root = pr;
    }
    return pr;
}

Node* AVL::LRRotation(Node *p) {
    Node* pl = p->lchild;
    Node* plr = pl->rchild;

    pl->rchild = plr->lchild;
    p->lchild = plr->rchild;

    plr->lchild = pl;
    plr->rchild = p;

    pl->height = NodeHeight(pl);
    p->height = NodeHeight(p);
    plr->height = NodeHeight(plr);

    if (p == root){
        root = plr;
    }
    return plr;
}

Node* AVL::RLRotation(Node *p) {
    Node* pr = p->rchild;
    Node* prl = pr->lchild;

    pr->lchild = prl->rchild;
    p->rchild = prl->lchild;

    prl->rchild = pr;
    prl->lchild = p;

    pr->height = NodeHeight(pr);
    p->height = NodeHeight(p);
    prl->height = NodeHeight(prl);

    if (root == p){
        root = prl;
    }
    return prl;
}

Node* AVL::rInsert(Node *p, string key) {
    Node* t;
    if (p == nullptr){
        t = new Node;
        t->data = key;
        t->lchild = nullptr;
        t->rchild = nullptr;
        t->height = 1;
        return t;
    }

    if (key < p->data){
        p->lchild = rInsert(p->lchild, key);
    } else if (key > p->data){
        p->rchild = rInsert(p->rchild, key);
    }

    p->height = NodeHeight(p);

    if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) {
        return LLRotation(p);
    } else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1){
        return LRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1){
        return RRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1){
        return RLRotation(p);
    }

    return p;
}

void AVL::Inorder(Node *p) {
    if (p){
        Inorder(p->lchild);
        cout << p->data << ", " << flush;
        Inorder(p->rchild);
    }
}
Node*AVL::search_movie(Node *p,string movie)
{
    bool flag;
    if(p==NULL)
    {
        flag=false;
    }
    else
    {

    if(p->data==movie)
    {
        flag=true;
    }
    else
    {
        rInsert(p,movie);
    }
    if(flag==false&&p->lchild!=NULL)
    {
        search_movie(p->lchild,movie);
    }
    if(flag==false&&p->rchild!=NULL)
    {
        search_movie(p->rchild,movie);
    }
    }
    return p;

}



int lives_count=6;

void lives(int index)
{
    if(index==0)
    {
        lives_count-=1;
    }
}

int substring_matching(char input,string answer,string &masked)
{
    int flag = 0;
    for(long long unsigned int i=0;i<answer.size();i++)
    {
        if(answer[i]==input && masked[i]=='_')
        {masked[i] = input; flag = 1;}
    }
    return flag;
}

int generateHash(string s,int mod) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    int len = s.length();
    unsigned long long int key = 0;

    for (int i=len-1; i>=0; i--) {
        key += pow(int(s[i]) - int('a'), i);
        key%=mod;
        // cout<<s<<" Key is: "<<key<<endl;
    }
    return key;
}

class HashTable {
    int capacity;
    int curlen;
    vector<string> hashtable;

    public:

    HashTable(): capacity(2003), curlen(0) {
        vector<string> mytable(capacity,"");
        hashtable = mytable;
    }

    void push(string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        long long int key;
        if (s.empty()) return;
        key = generateHash(s,capacity) % capacity;

        for (int i=0; i<capacity; i++) {
            if (hashtable[(key + i) % capacity] == "") {
                hashtable[(key+i)%capacity] = s;
                break;
            }
        }
        curlen++;
    }

    void print() {
        for (int i=0; i<capacity; i++) {
            if (hashtable[i] != "") cout<<i<<" "<<hashtable[i]<<", ";
        }
        cout<<endl;
    }
};


/*bool compare(string s1,string s2)
{
    int sum1=0,sum2=0;
    long long unsigned int size;
    if(s1.size()>=s2.size())
    {size=(s1.size());}
    else
    {size=(s2.size());}
    for(long long unsigned int i=0;i<size;i++)
    {
     if(i<s1.size())
       {sum1+=s1[i];}
     if(i<s2.size()) {
            sum2+=s2[i];
    }
    }
    if(sum1<sum2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
*/

int size = 0;

void movie_count(Node *root){
    if(root!=NULL)
    {
        size++;
        movie_count(root->lc);
        movie_count(root->rc);
    }
}

Node* level_order(Node *root,int i)
{
    queue<Node*> q;
   q.push(root);
   while(!q.empty())
   {
      if(i<=0)
      {break;}
q.push(q.front()->lc);
q.push(q.front()->rc);
   if(q.front()!=NULL)
       {i--;}
       q.pop();

   }
   return q.front();

}

string rand_movie(Node* root)
{
    movie_count(root);
    int index=rand()%size;
    return (level_order(root,index))->name;

}

string remove_consonants(string str)
{
    for(long long unsigned int i=0;i<str.size();i++)
    {
        if(str[i]!='a' && str[i]!='e' && str[i]!='i' && str[i]!='o' && str[i]!='u')
        {
          str[i]='_';
        }
    }
    return str;
}

int main()
{
    vector<string> movies{"The Exorcist",
"Inception",
"Catch Me If You Can",
"The Lord of the Rings",
"Interstellar",
"Jurassic Park",
"Avengers: Infinity War",
"harry potter and half blood prince",
"lost",
"Inside Out",
"godfather",
"Blade Runner",
"Ratatouille",
"The Terminator",
"The Incredibles",
"The Amazing Spiderman",
"Gully Boy",
"Yeh Jawaani Hai Deewani",
"Hum Aapke Hain Kaun",
"Gangs of Wasseypur",
"Sardar Udham",
"Zindagi Na Milegi Dobara",
"Bajrangi Bhaijaan",
"Dilwale Dulhania Le Jayenge",
"Tiger Zinda Hai",
"Chennai Express",
"Prem Ratan Dhan Payo",
"Bhool Bhulaiyaa",
"Tanu Weds Manu",
"Thugs Of Hindostan",
"Toilet Ek Prem Katha"};



      HashTable *table = new HashTable();
    string s1 = "Harry Potter";
    for (auto movie: movies) {
        table->push(movie);
    }
    table->print();


     AVL tlr;
    tlr.root = tlr.rInsert(tlr.root, "exorcist");
    tlr.root = tlr.rInsert(tlr.root, "inception");
    tlr.root = tlr.rInsert(tlr.root, "catch me if you can");
    tlr.root = tlr.rInsert(tlr.root, "the lord of the rings");
    tlr.root = tlr.rInsert(tlr.root, "interstellar");
    tlr.root = tlr.rInsert(tlr.root, "jurassic park");
    tlr.root = tlr.rInsert(tlr.root, "avengers infinity war");
    tlr.root = tlr.rInsert(tlr.root, "harry potter and half blood prince");
    tlr.root = tlr.rInsert(tlr.root, "lost");
    tlr.root = tlr.rInsert(tlr.root, "inside out");
    tlr.root = tlr.rInsert(tlr.root, "godfather");
    tlr.root = tlr.rInsert(tlr.root, "blade runner");
    tlr.root = tlr.rInsert(tlr.root, "ratatouille");
    tlr.root = tlr.rInsert(tlr.root, "the terminals");
    tlr.root = tlr.rInsert(tlr.root, "the incredibles");
    tlr.root = tlr.rInsert(tlr.root, "the amazing spider man");
    tlr.root = tlr.rInsert(tlr.root, "gully boy");
    tlr.root = tlr.rInsert(tlr.root, "yeh jawaani hai deewani");
    tlr.root = tlr.rInsert(tlr.root, "hum aapke hai kaun");
    tlr.root = tlr.rInsert(tlr.root, "gangs of wasseypur");
    tlr.root = tlr.rInsert(tlr.root, "sardar uddham");
    tlr.root = tlr.rInsert(tlr.root, "zindagi na milegi dobara");
    tlr.root = tlr.rInsert(tlr.root, "bajrangi bhaijan");
    tlr.root = tlr.rInsert(tlr.root, "dilwale dulhaniya le jayenge");
    tlr.root = tlr.rInsert(tlr.root, "tiger zinda hai");
    tlr.root = tlr.rInsert(tlr.root, "chennai express");
    tlr.root = tlr.rInsert(tlr.root, "prem ratan dhan payo");
    tlr.root = tlr.rInsert(tlr.root, "bhool bhulaiya");
    tlr.root = tlr.rInsert(tlr.root, "tanu weds manu");
    tlr.root = tlr.rInsert(tlr.root, "thugs of hindostan");
    tlr.root = tlr.rInsert(tlr.root, "toilet ek prem katha");


         cout<<remove_consonants(rand_movie(tlr.root));

    string movie;
    cin>>movie;
    tlr.search_movie(tlr.getRoot(),movie);
    tlr.Inorder();
    cout << endl;
    cout << tlr.root->data << endl;

    return 0;
}
