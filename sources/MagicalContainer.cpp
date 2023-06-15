#include "MagicalContainer.hpp"
#include <iostream>  // Input/output operations
#include <stdexcept> // Standard exceptions, including runtime_error

using namespace std;
#include "MagicalContainer.hpp"

namespace ariel {

    // Constructor
    MagicalContainer::MagicalContainer() :Elements() , vecPrime(){ }

    // Add an element to the container
    void MagicalContainer::addElement(int element) {
        if (isPrime(element)) {
            auto it = lower_bound(vecPrime.begin(), vecPrime.end(), element);
            if (it == vecPrime.end() || *it != element) {
                vecPrime.insert(it, element);
            }
        }
        auto it = lower_bound(Elements.begin(), Elements.end(), element);
        if (it == Elements.end() || *it != element) {
            Elements.insert(it, element);
        }
    }

    // Remove an element from the container
    void MagicalContainer::removeElement(int element) {
        if (isPrime(element)) {
            auto it = lower_bound(vecPrime.begin(), vecPrime.end(), element);
            if (it != vecPrime.end() && *it == element) {
                vecPrime.erase(it);
            }
        }

        auto it = std::lower_bound(Elements.begin(), Elements.end(), element);
        if (it != Elements.end() && *it == element) {
            Elements.erase(it);
            return;
        }
        throw std::runtime_error("Element not found!!!");
    }

    // Get the size of the container
    size_t MagicalContainer::size() const {
        return Elements.size();
    }

    // Get the elements of the container
    const vector<int> &MagicalContainer::getElements() const {
        return Elements;
    }

    // Check if a number is prime
    bool MagicalContainer::isPrime(int number) {
        if (number < 2) {
            return false;
        }
        if (number ==  2){
            return true;
        }
        for (int i = 2; i <= sqrt(number); ++i) {
            if (number % i == 0) {
                return false;
            }
        }
        return true;
    }

    // Constructor
    MagicalContainer::Iterator::Iterator(IteratorType iterType) : iterType(iterType)
    {

    }

    // Destructor
    MagicalContainer::Iterator::~Iterator()
    {

    }

    // Constructor
    MagicalContainer::Iterator::Iterator():iterType(IteratorType::ASCENDING)
    {

    }

    // AscendingIterator Constructor
    MagicalContainer::AscendingIterator::AscendingIterator(): Iterator(IteratorType::ASCENDING), curr(0),container(*new MagicalContainer())
    {

    }

    // AscendingIterator Constructor
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) :Iterator(IteratorType::ASCENDING), container(container) ,curr(0)
    {

    }

    // AscendingIterator Constructor
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, size_t index) :Iterator(IteratorType::ASCENDING), container(container), curr(index) 
    {

    }

    // AscendingIterator Destructor
    MagicalContainer::AscendingIterator::~AscendingIterator() 
    {
        // Implementation
    }

    // AscendingIterator Copy Constructor
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) :container(other.container),curr(other.curr)
    {

    }

    // AscendingIterator Assignment Operator
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {
        if (*this != other) {
            if (&container != &other.container) {
                throw runtime_error("Error with operator=() :: AscendingIterator !");
            }
        
        this->curr=other.curr;
        }
        return *this;
    }

    // Check if two AscendingIterators are equal
    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
        return (this->container.Elements == other.container.Elements && this->curr == other.curr );
    }

    // Check if two AscendingIterators are not equal
    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
        return !(*this == other);
    }

    // Compare two AscendingIterators (greater than)
    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
        return (this->container.Elements == other.container.Elements && this->curr > other.curr );
    }

    // Compare two AscendingIterators (less than)
    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {
        return (this->container.Elements == other.container.Elements && this->curr < other.curr );
    }

    // Check if an AscendingIterator is equal to another Iterator
    bool MagicalContainer::AscendingIterator::operator==(const Iterator &other) const 
    {
        const auto &otherAscendingIterator = dynamic_cast<const AscendingIterator&>(other);
        return (*this == otherAscendingIterator && this->getIterType() == other.getIterType());
    }

    // Check if an AscendingIterator is not equal to another Iterator
    bool MagicalContainer::AscendingIterator::operator!=(const Iterator &other) const
    {
        return !(*this==other);
    }

    // Compare an AscendingIterator to another Iterator (greater than)
    bool MagicalContainer::AscendingIterator::operator>(const Iterator &other) const
    {
        const auto &otherAscendingIterator = dynamic_cast<const AscendingIterator&>(other);
        return (*this > otherAscendingIterator && this->getIterType() == other.getIterType());
    }

    // Compare an AscendingIterator to another Iterator (less than)
    bool MagicalContainer::AscendingIterator::operator<(const Iterator &other) const 
    {
        const auto &otherAscendingIterator = dynamic_cast<const AscendingIterator&>(other);
        return (*this < otherAscendingIterator && this->getIterType() == other.getIterType());   
    }

    // Dereference the AscendingIterator
    int MagicalContainer::AscendingIterator::operator*() const {
        if (curr < 0 || curr >= container.size()) {
        throw runtime_error("out of bound operator*()");
        }
        return (this->getContainer().getElements())[this->curr];
    }

    // Increment the AscendingIterator
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        if (++curr > container.size()) {
            throw runtime_error("out of bouns with operator++()");
        }
    return *this;
    }

    // Get the beginning iterator
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return AscendingIterator(container, 0);
    }

    // Get the ending iterator
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        return AscendingIterator(container, container.size());
    }

    // Get the container associated with the AscendingIterator
    MagicalContainer &MagicalContainer::AscendingIterator::getContainer() const {
        return this->container;
    }

    // Get the index associated with the AscendingIterator
    size_t MagicalContainer::AscendingIterator::getIndex() const {
        return this->curr;
    }

    // SideCrossIterator Default Constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator() 
        : Iterator(IteratorType::SIDE_CROSS), iters(0), front(0), back(container.size()-1),container(*new MagicalContainer())
    {
        
    }

    // SideCrossIterator Constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) 
        :Iterator(IteratorType::SIDE_CROSS), container(container) ,iters(0), front(0), back(container.size()-1)
    {
        if(container.Elements.size() == 0 ){
            this->back =0;
        }
    }

    // SideCrossIterator Constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, size_t frontIndex, size_t backIndex) 
        :Iterator(IteratorType::SIDE_CROSS), container(container), front(frontIndex), back(backIndex) 
    {

    }

    // SideCrossIterator Destructor
    MagicalContainer::SideCrossIterator::~SideCrossIterator() 
    {

    }

    // SideCrossIterator Copy Constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
        :container(other.container), front(other.front) , back(other.back), iters(other.iters)
    {

    }

    // SideCrossIterator Assignment Operator
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
        if (*this != other) {
            if (&container != &other.container) {
                throw runtime_error("Error with operator=() :: SideCrossIterator!!!");
            }
        
        this->front=other.front;
        this->back=other.back;
        this->iters=other.iters;
        }
        return *this;
    }

    // Check if two SideCrossIterators are equal
    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {
        return (this->container.Elements == other.container.Elements && this->front == other.front && this->back == other.back );
    }

    // Check if two SideCrossIterators are not equal
    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
        return !(*this==other);
    }

    // Compare two SideCrossIterators (greater than)
    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
        // The iterator closer to the middle is considered "greater"
        return (min(front, back) > min(other.front, other.back) && this->container.getElements() == other.container.getElements()) ;   
    }

    // Compare two SideCrossIterators (less than)
    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const 
    {
        // The iterator closer to the middle is considered "greater"
        return (max(front, back) < max(other.front, other.back) && this->container.getElements() == other.container.getElements());    
    }

    // Check if a SideCrossIterator is equal to another Iterator
    bool MagicalContainer::SideCrossIterator::operator==(const Iterator &other) const {
        const auto &otherSideCrossIterator = dynamic_cast<const SideCrossIterator &>(other);
        return *this == otherSideCrossIterator && container.getElements() == otherSideCrossIterator.container.getElements();
    }

    // Check if a SideCrossIterator is not equal to another Iterator
    bool MagicalContainer::SideCrossIterator::operator!=(const Iterator &other) const 
    {

        const auto &otherSideCrossIterator = dynamic_cast<const SideCrossIterator &>(other);
        return *this != otherSideCrossIterator && container.getElements() == otherSideCrossIterator.container.getElements();
    }

    // Compare a SideCrossIterator to another Iterator (greater than)
    bool MagicalContainer::SideCrossIterator::operator>(const Iterator &other) const 
    {
        const auto &otherSideCrossIterator = dynamic_cast<const SideCrossIterator &>(other);
        return *this > otherSideCrossIterator && container.getElements() == otherSideCrossIterator.container.getElements();
    }

    // Compare a SideCrossIterator to another Iterator (less than)
    bool MagicalContainer::SideCrossIterator::operator<(const Iterator &other) const 
    {
        const auto &otherSideCrossIterator = dynamic_cast<const SideCrossIterator &>(other);
        return *this < otherSideCrossIterator && container.getElements() == otherSideCrossIterator.container.getElements();
    }

    // Dereference the SideCrossIterator
    int MagicalContainer::SideCrossIterator::operator*() const {
        if (front > back) {
            throw runtime_error("Error with operator*(): out of bounds");
        }
        // even count of iters -->>, return from the front.
        // odd count of iters -->>,  return from the back.
        if (iters % 2 == 0) {
            return container.Elements[front];
        } else {
            return container.Elements[back];
        }
    }
    // Increment the SideCrossIterator
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        if (front > back) {
            throw runtime_error("Error with operator++(): out of bounds.");
        }
        // even count of iters -->>, increment front.
        // odd count of iters -->>,  increment the back.
        if (iters % 2 == 0) {
            front++;
        } 
        else {
            back--;
        }
        iters++;
        return *this;
    }

    // Get the beginning iterator
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return {container, 0, container.size() - 1};
    }

    // Get the ending iterator
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        size_t mid = (container.size() + 1) / 2;
        if (mid == 0) {
            return {container, mid, mid};
        }
        return {container, mid, mid - 1};
    }

    // Get the container associated with the SideCrossIterator
    MagicalContainer &MagicalContainer::SideCrossIterator::getContainer() const {
        return this->container;
    }

    // Get the front index associated with the SideCrossIterator
    size_t MagicalContainer::SideCrossIterator::getFrontIndex() const {
        return this->front;
    }

    // Get the back index associated with the SideCrossIterator
    size_t MagicalContainer::SideCrossIterator::getBackIndex() const {
        return this->back;
    }

    // PrimeIterator Constructor
    MagicalContainer::PrimeIterator::PrimeIterator() 
        :Iterator(IteratorType::PRIME) , container(*new MagicalContainer()) , index(0)
    {
        
    }

    // PrimeIterator Constructor
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) 
        : Iterator(IteratorType::PRIME) , container(container),index(0)
    {
        
    }

    // PrimeIterator Constructor
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, size_t index) 
        :Iterator(IteratorType::PRIME) ,container(container), index(index)
    {

    }

    // PrimeIterator Copy Constructor
    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
        :Iterator(IteratorType::PRIME) ,container(other.container), index(other.index)
    {

    }

    // PrimeIterator Destructor
    MagicalContainer::PrimeIterator::~PrimeIterator() 
    {
    
    }

    // PrimeIterator Assignment Operator
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) 
    {
        if (*this != other) {
            if (&container != &other.container) {
                throw runtime_error("Error with operator=()::PrimeIterator");
            }
            index = other.index;
        }
        return *this;
    }

    // Check if two PrimeIterators are equal
    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const 
    {
        return (this->container.vecPrime == other.container.vecPrime && index == other.index);
    }

    // Check if two PrimeIterators are not equal
    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const 
    {
        return !(*this == other);    
    }

    // Compare two PrimeIterators (greater than)
    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
        return (this->container.vecPrime == other.container.vecPrime && index > other.index);
    }

    // Compare two PrimeIterators (less than)
    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {
        return (this->container.vecPrime == other.container.vecPrime && index < other.index);
    }

    // Check if a PrimeIterator is equal to another Iterator
    bool MagicalContainer::PrimeIterator::operator==(const Iterator &other) const 
    {
        const auto &otherPrimeIterator = dynamic_cast<const PrimeIterator &>(other);
        return *this == otherPrimeIterator && this->getIterType() == other.getIterType();
    }

    // Check if a PrimeIterator is not equal to another Iterator
    bool MagicalContainer::PrimeIterator::operator!=(const Iterator &other) const 
    {
        const auto &otherPrimeIterator = dynamic_cast<const PrimeIterator &>(other);
        return *this != otherPrimeIterator && this->getIterType() == other.getIterType();
    }

    // Compare a PrimeIterator to another Iterator (greater than)
    bool MagicalContainer::PrimeIterator::operator>(const Iterator &other) const 
    {
        const auto &otherPrimeIterator = dynamic_cast<const PrimeIterator &>(other);
        return *this > otherPrimeIterator && this->getIterType() == other.getIterType();
    }

    // Compare a PrimeIterator to another Iterator (less than)
    bool MagicalContainer::PrimeIterator::operator<(const Iterator &other) const 
    {
        const auto &otherPrimeIterator = dynamic_cast<const PrimeIterator &>(other);
        return *this < otherPrimeIterator && this->getIterType() == other.getIterType();
    }

    // Dereference the PrimeIterator
    int MagicalContainer::PrimeIterator::operator*() const {
        if (index < 0 || index >= container.vecPrime.size()) {
            throw runtime_error("Error out of bounds with operator*()::PrimeIterator");
        }
        return container.vecPrime[index];
    }

    // Increment the PrimeIterator
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if (++index > container.vecPrime.size()) {
            throw runtime_error("Error out of bounds with operator++()::PrimeIterator");
        }
        return *this;
    }

    // Get the beginning iterator
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return PrimeIterator(container, 0);
    }

    // Get the ending iterator
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        return PrimeIterator(container, container.vecPrime.size());
    }

    // Get the container associated with the PrimeIterator
    MagicalContainer &MagicalContainer::PrimeIterator::getContainer() const {
        return container;
    }

    // Get the index associated with the PrimeIterator
    size_t MagicalContainer::PrimeIterator::getIndex() const {
        return index;
    }

} // namespace ariel

