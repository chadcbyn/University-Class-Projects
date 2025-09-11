#include <iostream>
#include <string>

#include "p4.h"

using namespace std;

Person::Person()
{
    this->height = 0;
    this->weight = 0;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

Person::Person(string first, string last, int height, int weight)
{
    this->first = first;
    this->last = last;
    this->height = height;
    this->weight = weight;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

std::ostream& operator<<(std::ostream& os, const Person& person)
{
    os << person.first << " " << person.last << ": height=" << person.height << ", weight=" << person.weight << endl;
    return os;
}

PersonList::PersonList()
{
    this->size = 0;
    this->headHeightList = nullptr;
    this->headWeightList = nullptr;
}

int PersonList::getSize()
{
    return size;
}

void PersonList::printByHeight(ostream &os)
{
    Person* curr = headHeightList;
    while (curr) {
        os << *curr;
        curr = curr->nextHeight;
    }
}

void PersonList::printByWeight(ostream &os)
{
    Person* curr = headWeightList;
    while (curr) {
        os << *curr;
        curr = curr->nextWeight;
    }
}

bool PersonList::exists(string first, string last)
{
    bool x = false;
    Person* curr = headHeightList;
    while (curr) {
        if(curr->first == first && curr->last == last) x = true;
        curr = curr->nextHeight;
    }
    return x;
}

int PersonList::getHeight(string first, string last) 
{
    int h = -1;
    Person* curr = headHeightList;
    while (curr) {
        if(curr->first == first && curr->last == last) h = curr->height;
        curr = curr->nextHeight;
    }
    return h;
}

int PersonList::getWeight(string first, string last) 
{
    int w = -1;
    Person* curr = headWeightList;
    while (curr) {
        if(curr->first == first && curr->last == last) w = curr->weight;
        curr = curr->nextWeight;
    }
    return w;
}

bool PersonList::add(string first, string last, int height, int weight)
{
    if (this->exists(first, last))
    {
        return false;
    }
    Person *p = new Person(first, last, height, weight);

	if (!this->headHeightList || p->height > this->headHeightList->height || (p->height == this->headHeightList->height && p->weight < headHeightList->weight)) {
        p->nextHeight = this->headHeightList;
        this->headHeightList = p;
    } 
    else {
        Person* prev = this->headHeightList;
        Person* curr = headHeightList->nextHeight;
        while (curr && ((p->height < curr->height) || ((p->height == curr->height) && (p->weight >= curr->weight)))) {
            prev = curr;
            curr = curr->nextHeight;
        }
        p->nextHeight = curr;
        prev->nextHeight = p;
    }
    if (!this->headWeightList || p->weight < this->headWeightList->weight || (p->weight == this->headWeightList->weight && p->height > headWeightList->height)) {
        p->nextWeight = this->headWeightList;
        this->headWeightList = p;
    } else {
        Person* prev = this->headWeightList;
        Person* curr = headWeightList->nextWeight;
        while (curr && ((p->weight > curr->weight) || ((p->weight == curr->weight) && (p->height <= curr->height)))) {
            prev = curr;
            curr = curr->nextWeight;
        }
        p->nextWeight = curr;
        prev->nextWeight = p;
    }
    this->size++;
	return true;
}

bool PersonList::remove(string first, string last)
{
    if (!this->exists(first, last)) return false;
    Person* curr = this->headHeightList;
    Person* prev = nullptr;
    while (curr != nullptr) {
        if (curr->first == first && curr->last == last) {
            if (prev == nullptr) this->headHeightList = curr->nextHeight;
            else prev->nextHeight = curr->nextHeight;
            break;
        }
        prev = curr;
        curr = curr->nextHeight;
    }
    Person* toDelete = curr;

    curr = this->headWeightList;
    prev = nullptr;
    while (curr != nullptr) {
        if (curr == toDelete) {
            if (prev == nullptr) {
                this->headWeightList = curr->nextWeight;
            } else {
                prev->nextWeight = curr->nextWeight;
            }
            break;
        }
        prev = curr;
        curr = curr->nextWeight;
    }

    delete toDelete;
    this->size--;
    return true;
}

bool PersonList::updateName(string first, string last, string newFirst, string newLast)
{
    if(!this->exists(first,last)) return false;
    Person* curr = headWeightList;
    while (curr) {
        if(curr->first == first && curr->last == last) {
            curr->first = newFirst;
            curr->last = newLast;
        }
        curr = curr->nextWeight;
    }
    return true;
}

bool PersonList::updateHeight(string first, string last, int height)
{
    if(!this->exists(first, last)) return false;
    Person* curr = headHeightList;
    while (curr) {
        if(curr->first == first && curr->last == last) break;
        curr = curr->nextHeight;
    }
    this->remove(first, last);
    this->add(first, last, height, curr->weight);
    return true;
}

bool PersonList::updateWeight(string first, string last, int weight)
{
    if(!this->exists(first, last)) return false;
    Person* curr = headWeightList;
    while (curr) {
        if(curr->first == first && curr->last == last) break;
        curr = curr->nextWeight;
    }
    this->remove(first, last);
    this->add(first, last, curr->height, weight);
    return true;
}

PersonList::~PersonList()
{
    Person* curr = headHeightList;
    while (curr) {
        Person* temp = curr;
        curr = curr->nextHeight;
        delete temp;
    }
    headHeightList = nullptr;
    headWeightList = nullptr; 
}

PersonList::PersonList(const PersonList &src)
{
    this->size = 0;
    this->headHeightList = nullptr;
    this->headWeightList = nullptr;

    Person* curr = src.headHeightList;
    while (curr) {
        this->add(curr->first, curr->last, curr->height, curr->weight);
        curr = curr->nextHeight;
    }
}

const PersonList &PersonList::operator=(const PersonList &src)
{
    if (this != &src) {
        Person* curr = headHeightList;
        while (curr) {
            Person* temp = curr;
            curr = curr->nextHeight;
            delete temp;
        }

        size = src.size;
        headHeightList = nullptr;
        headWeightList = nullptr;

        Person* other = src.headHeightList;
        while (other) {
            this->add(other->first, other->last, other->height, other->weight);
            other = other->nextHeight;
        }
    }
    return *this;
}
