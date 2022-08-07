#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T date;
    Node<T>* next = nullptr;
    Node<T>* prev = nullptr;
};

template<typename T>
class LinkedList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int size = 0;
    int maxSize = 7;
public:
    LinkedList() {};
    LinkedList(T object) {
        Node<T>* buf = new Node<T>{ object };
        head = buf;
        tail = buf;
        size++;
    }
    void addToHead(T object) {
        if (size >= maxSize) throw "list is full";
        else {
            if (size == 0) { 
                Node<T>* buf = new Node<T>{ object };
                head = tail = buf;
                size++;
            }
            else {
                Node<T>* buf = new Node<T>{ object, head };
                head->prev = buf;
                head = buf;
                size++;
            }
        }
        
    }

    void addToTail(T object) {
        if (size >= maxSize) throw "list is full";
        else {
            if (head != nullptr) {
                Node<T>* buf = new Node<T>{ object,nullptr,tail };
                tail->next = buf;
                tail = buf;
                size++;
            }
            else {
                Node<T>* buf = new Node<T>{ object };
                head = tail = buf;
                size++;
            }
        }
        
    }

    void addToIndex(T object, int index) {
        if (size >= maxSize) throw "list is full";
        else {
            Node<T>* buf = head;
            for (int i = 1; i < index; i++) {
                buf = buf->next;
            }
            Node<T>* buf2 = new Node<T>{ object };
            buf2->next = buf->next;
            buf->next->prev = buf2;
            buf->next = buf2;
            size++;
        } 
    }

    void delFromHead() {
        if (size == 0) throw "list is empty";
        else {
            Node<T>* buf = head; 
            head = head->next;
            delete buf;
            size--;
        }
    }

    void delFromTail() {
        if (head == tail) delFromHead();
        Node<T>* buf = head;
        while (buf->next != tail) buf = buf->next; 
        buf->next = nullptr;
        delete tail;
        tail = buf;
        size--;
    }

    void deleteFromIndex(int index) {
        if (size == 0) throw "list is empty";
        Node<T>* buf = head;
        Node<T>* buf2 = buf;
        for (int i = 1; i < index; i++) {
            buf2 = buf;
            buf = buf->next;
        }
        buf2->next = buf->next;
        delete buf;
        size--;
    }

    void print() {
        if (size != 0) {
            Node <T>* buf = head;
            while (true) {
                cout << buf->date << " ";
                if (buf->next == nullptr) break;
                buf = buf->next;
            }
            cout << endl;
        }
        else throw "list is empty";
    }
};

class Man {
    string name;
public:
    Man(string name) {
        this->name = name;
    }
    friend ostream& operator<<(ostream& out, Man& man) {
        out << man.name;
        return out;
    }
};

int main()
{
    Man man1("Alex");
    Man man2("Alex2");
    Man man3("Alex3");
    Man man4("Alex4");
    Man man5("Alex5");
    LinkedList<Man> list1(man1);
    try {
        list1.print();
        list1.delFromHead();
        //list1.print(); попытка печати пустого списка
        cout << endl;
        //list1.delFromHead(); попытка удаления из пустого списка
        list1.addToHead(man2);
        list1.addToHead(man3);
        list1.addToHead(man4);
        list1.addToHead(man5);
        list1.print();

        Man man6("Anna");
        list1.addToTail(man6);
        list1.print();

        list1.delFromHead();
        list1.print();

        list1.delFromTail();
        list1.print();

        Man man7("Fedor");
        list1.addToHead(man7);
        list1.print();

        Man man8("Nik");
        list1.addToIndex(man8, 3);
        list1.print();

        Man man9("Oleg");
        Man man10("Maria");
        Man man11("Kristina");
        list1.addToHead(man9);
        list1.print();
        list1.deleteFromIndex(2);
        list1.print();
        list1.addToHead(man10);
        list1.print();
        list1.addToHead(man11);
        list1.print();
        Man man12("Erik");
        list1.addToHead(man12); //попытка добавления в переполненный список
        list1.print();
    }
    catch (const char* str) {
        cout << str;
    }
    

}




