#include <iostream>
using namespace std;

/*
    korzeniem jest pierwszy element
    do lewej strony dopinamy mniejszy element a wiekszy do prawej
    jezeli kolejny jest rowniez wiekszy to wstawiamy jeszcze nizej na prawa strone
    jezeli jest nizszy to po lewej stronie na kolejnym poziomie

    trzeba przejsc inorder aby posortowac potem
    najpierw lewy element - potem stary - potem prawy
*/

struct Invoice {
    string data;
    unsigned int count;

    Invoice(){}
    Invoice(string data) {
        this->data = data;
        count = 1;
    }
};

struct Tree {
    Invoice invoice;
    Tree* left;
    Tree* right;

    Tree(){}
    Tree(string data) {
        invoice = Invoice(data);
        left = nullptr;
        right = nullptr;
    }

    //działa dobrze - sprawdzone
    void add_node(Tree* new_node) {
        //this to root drzewa
        Tree* current = this;

        while(true) {
            if(current->invoice.data > new_node->invoice.data) {
                //jak nowy jest mniejszy od current node'a
                if(current->left == nullptr) {
                    current->left = new_node;
                    return;
                } else {
                    //schodzimy nizej
                    current = current->left;
                }
            } else if(current->invoice.data < new_node->invoice.data) {
                //jak nowy jest wiekszy od current node'a
                if(current->right == nullptr) {
                    current->right = new_node;
                    return;
                } else {
                    //schodzimy nizej
                    current = current->right;
                }
            } else {
                //jak ten sam element
                current->invoice.count++;
                delete new_node;
                return;
            }
        }
    }

    void print() {
        //this to root drzewa za pierwszym razem
        //current bedzie obecnie najwyzszym prawym jeszcze nie wyswietlonym
        Tree* current = this;
        if(current->left != nullptr) {
            //schodzimy niezej
            current->left->print();
            //wyswietlamy najnizszy z lewej i wracamy do gory
            for(int i=0;i<current->invoice.count;++i) {
                cout<<current->invoice.data<<"\n";
            }
            //jak sie skonczy lewa odnoga
            if(current->right != nullptr) {
                current->right->print();
            }
        } else if(current->right != nullptr) {
            //idziemy w prawo
            //wyswietlamy stary node
            for(int i=0;i<current->invoice.count;++i) {
                cout<<current->invoice.data<<"\n";
            }
            //schodzimy nizej
            current->right->print();
        } else {
            //jak sie skonczy odnoga
            for(int i=0;i<current->invoice.count;++i) {
                cout<<current->invoice.data<<"\n";
            }
        }
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    cin.tie(nullptr);

    //liczba faktur
    int n;

    cin>>n;

    //jak jest 0 faktur
    if(n == 0) {
        return 0;
    }

    //dana faktura
    string invoice;

    //aktualny node
    Tree *node;
    //zapisanie korzenia
    Tree *root;

    cin>>invoice;
    root = new Tree(invoice);

    for(int i=0;i<n-1;++i) {
        cin>>invoice;
        node = new Tree(invoice);
        root->add_node(node);
    }
    root->print();
    return 0;
}