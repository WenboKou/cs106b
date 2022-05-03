// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "VectorPatientQueue.h"

VectorPatientQueue::VectorPatientQueue() {
    // TODO: write this constructor
    timestap = 0;
}

VectorPatientQueue::~VectorPatientQueue() {
    // TODO: write this destructor
}

void VectorPatientQueue::clear() {
    // TODO: write this function
    myqueue.clear();
}

string VectorPatientQueue::frontName() {
    // TODO: write this function
    int queue_length =  myqueue.size();
    if (queue_length == 0) {
        throw "There's no patient now.";
    }
    int tmp = 0;
    for (int i = 1; i < queue_length; i++) {
        if (myqueue[tmp].priority > myqueue[i].priority) {
            tmp = i;
        } else if (myqueue[tmp].priority == myqueue[i].priority) {
            if (myqueue[tmp].timestap > myqueue[i].timestap) {
                tmp = i;
            }
        }
    }
    string name = myqueue[tmp].name;
    return name;
}

int VectorPatientQueue::frontPriority() {
    // TODO: write this function
    int queue_length =  myqueue.size();
    if (queue_length == 0) {
        throw "There's no patient now.";
    }
    int tmp = 0;
    for (int i = 1; i < queue_length; i++) {
        if (myqueue[tmp].priority > myqueue[i].priority) {
            tmp = i;
        } else if (myqueue[tmp].priority == myqueue[i].priority) {
            if (myqueue[tmp].timestap > myqueue[i].timestap) {
                tmp = i;
            }
        }
    }
    int priority = myqueue[tmp].priority;
    return priority;
}

bool VectorPatientQueue::isEmpty() {
    // TODO: write this function
    return myqueue.isEmpty();
}

void VectorPatientQueue::newPatient(string name, int priority) {
    // TODO: write this function
    Patient curr;
    curr.name = name;
    curr.priority = priority;
    curr.timestap = this->timestap;
    this->timestap++;
    myqueue.add(curr);
}

string VectorPatientQueue::processPatient() {
    // TODO: write this function
    int queue_length =  myqueue.size();
    if (queue_length == 0) {
        throw "There's no patient now.";
    }
    int tmp = 0;
    for (int i = 1; i < queue_length; i++) {
        if (myqueue[tmp].priority > myqueue[i].priority) {
            tmp = i;
        } else if (myqueue[tmp].priority == myqueue[i].priority) {
            if (myqueue[tmp].timestap > myqueue[i].timestap) {
                tmp = i;
            }
        }
    }
    string name = myqueue[tmp].name;
    myqueue.remove(tmp);
    return name;
}

void VectorPatientQueue::upgradePatient(string name, int newPriority) {
    // TODO: write this function
    int queue_length =  myqueue.size();
    if (queue_length == 0) {
        throw "There's no patient now.";
    }
    int tmp = -1;
    for (int i = 0; i < queue_length; i++) {
        if (myqueue[i].name == name) {
            if (tmp != -1) {
                if (myqueue[i].priority < myqueue[tmp].priority) {
                    tmp = i;
                }
            } else {
                tmp = i;
            }
        }
    }
    if (tmp == -1) {
        throw "The patient is not already in the queue.";
    }
    if (myqueue[tmp].priority < newPriority) {
        throw "The patient already has a more urgent priority.";
    }
    myqueue[tmp].priority = newPriority;
}

string VectorPatientQueue::toString() {
    // TODO: write this function
    //return myqueue.toString();
    if (myqueue.isEmpty()) {
        return "{}";
    }
    stringstream buffer;
    buffer << "{";
    for (int i = 0; i < myqueue.size() - 1; i++) {
        buffer << myqueue[i].priority << ":" << myqueue[i].name << ", ";
    }
    buffer << myqueue[myqueue.size() - 1].priority << ":" << myqueue[myqueue.size() - 1].name;
    buffer << "}";
    return buffer.str();
}
