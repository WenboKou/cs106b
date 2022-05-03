// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "LinkedListPatientQueue.h"
#include <string>
#include <iostream>
#include <sstream>

LinkedListPatientQueue::LinkedListPatientQueue() {
    // TODO: write this constructor
    head = nullptr;

}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    // TODO: write this destructor
    delete head;
}

void LinkedListPatientQueue::clear() {
    // TODO: write this function
    head = nullptr;
}

string LinkedListPatientQueue::frontName() {
    // TODO: write this function
    if (head == nullptr) {
        throw "The queue does not contain any patients.";
    }
    string output = head->name;
    return output;
}

int LinkedListPatientQueue::frontPriority() {
    // TODO: write this function
    if (head == nullptr) {
        throw "The queue does not contain any patients.";
    }
    int output = head->priority;
    return output;
}

bool LinkedListPatientQueue::isEmpty() {
    // TODO: write this function
    return (head == nullptr);
}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    // TODO: write this function
    if (head == nullptr) {
        head = new PatientNode;
        head->name = name;
        head->priority = priority;
    } else {
        if (head->priority > priority) {
            head = new PatientNode(name, priority, head);
        } else {
            PatientNode* tmp = head->next;
            PatientNode* front = head;
            while (tmp != nullptr) {
                if (tmp->priority > priority) {
                    front->next = new PatientNode(name, priority, tmp);
                    break;
                }
                front = front->next;
                tmp = tmp->next;
            }
            if (tmp == nullptr) {
                front->next = new PatientNode(name, priority, nullptr);
            }
        }
    }
}

string LinkedListPatientQueue::processPatient() {
    // TODO: write this function
    if (head == nullptr) {
        throw "The queue does not contain any patients.";
    }
    string output = head->name;
    head = head->next;
    return output;
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
    // TODO: write this function
    if (head == nullptr) {
        throw "The queue does not contain any patients.";
    }
    if (head->name == name) {
        if (head->priority < newPriority) {
            throw "The given patient is present in the queue and already has a more urgent priority.";
        } else {
            head->priority = newPriority;
        }
    } else {
        PatientNode* tmp = head->next;
        PatientNode* front = head;
        PatientNode* loc = nullptr;
        while (tmp != nullptr) {
            if (front->priority >= newPriority & newPriority >= tmp->priority) {
                loc = front;
            }
            if (tmp->name == name) {
                if (tmp->priority < newPriority) {
                    throw "The given patient is present in the queue and already has a more urgent priority.";
                } else {
                    tmp->priority = newPriority;
                    front->next = tmp->next;
                }
                break;
            }
            tmp = tmp->next;
            front = front->next;
        }
        if (tmp == nullptr) {
             throw "The given patient is not already in the queue.";
        }
        if (loc == nullptr) {
            tmp->next = head;
            head = tmp;
        } else {
            tmp->next = loc->next;
            loc->next = tmp;
        }
    }
}

string LinkedListPatientQueue::toString() {
    // TODO: write this function
    if (head == nullptr) {
        return "{}";
    }
    stringstream buffer;
    buffer << "{";
    PatientNode* tmp = head;
    while (tmp->next != nullptr) {
        buffer << *tmp << ", ";
        tmp = tmp->next;
    }
    buffer << *tmp;
    buffer << "}";
    return buffer.str();
}
