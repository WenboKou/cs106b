// heappatientqueue.cpp
// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "HeapPatientQueue.h"

HeapPatientQueue::HeapPatientQueue() {
    // TODO: write this constructor
    capacity = 5;
    head = new Patient[capacity];
    size = 1;
}

HeapPatientQueue::~HeapPatientQueue() {
    // TODO: write this destructor
    delete [] head;
}

void HeapPatientQueue::clear() {
    // TODO: write this function
    delete [] head;
    capacity = 5;
    head = new Patient[capacity];
    size = 1;
}

string HeapPatientQueue::frontName() {
    // TODO: write this function
    if (head[1].name == "") {
        throw "The queue does not contain any patients.";
    }
    return head[1].name;
}

int HeapPatientQueue::frontPriority() {
    // TODO: write this function
    if (head[1].name == "") {
        throw "The queue does not contain any patients.";
    }
    return head[1].priority;
}

bool HeapPatientQueue::isEmpty() {
    // TODO: write this function
    return (head[1].name == "");
}

void HeapPatientQueue::bubbleup() {
    int parent = (size / 2);
    int index = size;
    while (parent >= 1) {
        if (head[parent].priority > head[index].priority) {
            // exchange
            Patient tmp = head[size];
            head[size] = head[parent];
            head[parent] = tmp;
            index = parent;
            parent = (index / 2);
        } else {
            break;
        }
    }
}

void HeapPatientQueue::newPatient(string name, int priority) {
    // TODO: write this function
    if (size == capacity) {
        // The array is full, double its capacity;
        Patient *newhead = new Patient[capacity*2];
        for (int i = 1; i <= capacity; i++) {
            newhead[i] = head[i];
        }
        delete [] head;
        head = newhead;
        capacity *= 2;
    }
    head[size].name = name;
    head[size].priority = priority;
    bubbleup();
    size++;
}

void HeapPatientQueue::bubbledown() {
    int index = 1;
    while (index < size) {
        Patient tmp1;
        Patient tmp2;
        if (index*2 < size) {
            if (head[index].priority > head[2*index].priority) {
                tmp1 = head[2*index];
            }
        }
        if (index*2 + 1 < size) {
            if (head[index].priority > head[2*index+1].priority) {
                tmp2 = head[2*index+1];
            }
        }
        if (tmp1.name == "" && tmp1.name == "") {
            break;
        } else if (tmp1.name == "" && tmp2.name != "") {
            head[2*index+1] = head[index];
            head[index] = tmp2;
            index = 2*index+1;
        } else if (tmp1.name != "" && tmp2.name == "") {
            head[2*index] = head[index];
            head[index] = tmp1;
            index = 2*index;
        } else {
            if (tmp2.priority < tmp1.priority) {
                head[2*index+1] = head[index];
                head[index] = tmp2;
                index = 2*index+1;
            } else {
                head[2*index] = head[index];
                head[index] = tmp1;
                index = 2*index;
            }
        }
    }
}

string HeapPatientQueue::processPatient() {
    // TODO: write this function
    if (head[1].name == "") {
        throw "The queue does not contain any patients.";
    }
    string output = head[1].name;
    head[1].name = "";
    if (head[2].name != "") {
        head[1] = head[size - 1];
        size--;
        bubbledown();
    }
    return output;   // this is only here so it will compile
}

void HeapPatientQueue::upgradePatient(string name, int newPriority) {
    // TODO: write this function
    if (head[1].name == "") {
        throw "The queue does not contain any patients.";
    }
    int tmp = -1;
    for (int i = 1; i < size; i++) {
        if (head[i].name == name) {
            if (head[i].priority < newPriority) {
                throw "The given patient already has a more urgent priority than the given new priority";
            } else {
                if (tmp != -1) {
                    if (head[tmp].priority > head[i].priority) {
                        tmp = i;
                    }
                } else {
                    tmp = i;
                }
            }
        }
    }
    if (tmp == -1) {
        throw "The queue does not contain any patients.";
    } else {
        head[tmp].priority = newPriority;
        Patient middle = head[tmp];
        head[tmp] = head[1];
        head[1] = middle;
        bubbledown();
    }
}

string HeapPatientQueue::toString() {
    // TODO: write this function
    if (head[1].name == "") {
        return "{}";
    }
    stringstream buffer;
    buffer << "{";
    for (int i = 1; i < size - 1; i++) {
        buffer << head[i].priority << ":" << head[i].name << ", ";
    }
    buffer << head[size - 1].priority << ":" << head[size - 1].name;
    buffer << "}";
    return buffer.str();
}
