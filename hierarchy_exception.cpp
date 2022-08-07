#include <iostream>
#include <fstream>
#include "Man.h"
using namespace std;

template<typename T>
struct Node {
    T date;
    Node<T>* next = nullptr;
    Node<T>* prev = nullptr;
};

class Exception {
protected:
    string text;
public:
    virtual string what() = 0;
};

class MathException : public Exception {
public:
    MathException() {
        text = "Mathematical error.";
    }
    MathException(string text) {
        this->text = text;
    }
    string what() {
        return text;
    }
};

class DivideByZero :public MathException {
public:
    DivideByZero() :MathException() {
        text = "Error. Divide by 0.";
    }
    string what() {
        return text;
    }
};

class ZeroDegree :public MathException {
public:
    ZeroDegree() : MathException() {
        text = "Number in degree 0. The result is 1.";
    }
    string what() {
        return text;
    }
};

class LackOfSpace :public Exception {
public:
    LackOfSpace() {
        text = "Error. Lack of space.";
    }
    LackOfSpace(string text) {
        this->text = text;
    }
    string what() {
        return text;
    }
};

class ArrayOverflow :public LackOfSpace {
public:
    ArrayOverflow() :LackOfSpace() {
        text = "Error. The array is full";
    }
    string what() {
        return text;
    }
};

class ListOverflow :public LackOfSpace {
public:
    ListOverflow() :LackOfSpace() {
        text = "Error. The list is full";
    }
    string what() {
        return text;
    }
};

class FileException :public Exception {
public:
    FileException() {
        text = "Error when working with a file.";
    }
    FileException(string text) {
        this->text = text;
    }
    string what() {
        return text;
    }
};

class FileNotFound :public FileException {
public:
    FileNotFound() :FileException() {
        text = "Error opening file. File not found";
    }
    string what() {
        return text;
    }
};


void openFile(string path) {
    ifstream in(path);
    if (in.is_open()) {
        cout << "File opened successfully.";
    }
    else throw FileNotFound();
    in.close();
}

class Array { 
    int* data;
    int size;
    int maxSize;
public:
    Array(int size) {
        this->maxSize = size;
        data = new int[maxSize];
    }

    void add(int data) {
        if (this->size >= maxSize) throw ArrayOverflow();
        else {
            this->data[size] = data;
            size++;
        }
    }
    void show() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
    }
};

void checkDivision(float a, float b) {
    if (b == 0) throw DivideByZero();
    else cout << (double)a / b << endl;
}

void degree(int a, int b) {
    if (b == 0) throw ZeroDegree();
    else {
        int result=1;
        for (int i = 0; i < b; i++) {
            result *= a;
        }
        cout << result << endl;
    }
}

template<typename T>
class LinkedList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int size = 0;
    int maxSize = 5;
public:
    LinkedList() {};
    LinkedList(T object) {
        Node<T>* buf = new Node<T>{ object };
        head = buf;
        tail = buf;
        size++;
    }
    void addToHead(T object) {
        if (size >= maxSize) throw ListOverflow();
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



int main()
{
    try {
        checkDivision(5, 8);
        checkDivision(6, 0);

        degree(3, 2);
        degree(5, 0);
        
        Array array(3);
        array.add(19);
        array.add(4);
        array.add(8);
        array.add(90);
        array.show();

        Man man1("Pavel");
        LinkedList<Man> list(man1);
        Man man2("Sveta");
        Man man3("Kirill");
        Man man4("Viktor");
        Man man5("Nina");
        list.addToHead(man2);
        list.addToHead(man3);
        list.addToHead(man4);
        list.addToHead(man5);
        list.print();
        Man man6("Georgy");
        list.addToHead(man6);
        
        openFile("C:\\Users\\w2020\\Desktop\\test1.txt");
    }
    catch (DivideByZero ex) {
        cout << ex.what() << endl;
    }
    catch (ZeroDegree ex) {
        cout << ex.what() << endl;
    }
    catch (ArrayOverflow ex) {
        cout << ex.what() << endl;
    }
    catch (ListOverflow ex) {
        cout << ex.what() << endl;
    }
    catch (FileNotFound ex) {
        cout << ex.what() << endl;
    }
    
}

