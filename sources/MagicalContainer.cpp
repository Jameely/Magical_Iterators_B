#include "MagicalContainer.hpp"
#include <iostream>  // Input/output operations
#include <stdexcept> // Standard exceptions, including runtime_error

using namespace std;
namespace ariel
{
    // MagicalContainer class member functions
    void MagicalContainer::addElement(int element)
    {
        elements.push_back(element);
    }

    void MagicalContainer::removeElement(int element)
    {
        // Find and erase the element from the vector
        auto it = std::find(elements.begin(), elements.end(), element);
        if (it == elements.end())
        {
            throw std::runtime_error("Element not found.");
        }
        else{
            elements.erase(it);

        }
    }

    int MagicalContainer::size() const {    return elements.size();     }

    const std::vector<int>& MagicalContainer::getElements() const{      return elements;        }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container): container(container), sortedElements(container.getElements()) , curr(0)
    {
        std::sort(sortedElements.begin(), sortedElements.end());
    }

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : container(other.container), sortedElements(other.sortedElements), iter(sortedElements.begin() + std::distance(other.sortedElements.begin(), other.iter)), curr(other.curr) {
        std::sort(sortedElements.begin(), sortedElements.end());
    }

    MagicalContainer::AscendingIterator::AscendingIterator()
    : container(*(new MagicalContainer())), sortedElements(container.getElements()), iter(sortedElements.begin()), curr(0) {
        std::sort(sortedElements.begin(), sortedElements.end());
    }

    MagicalContainer::AscendingIterator::~AscendingIterator() {}


    MagicalContainer::AscendingIterator::Iterator::Iterator(std::vector<int>::const_iterator iter) : iter(iter) {}
    
    int MagicalContainer::AscendingIterator::getcurr() {
        return this->curr;
    }

ariel::MagicalContainer::AscendingIterator& ariel::MagicalContainer::AscendingIterator::operator++()
{
    if (curr >= sortedElements.size()) {
        throw std::runtime_error("Attempted to increment beyond the end of the iterator");
    }
    // cout << sortedElements.end().base()<<endl;
    if (iter != sortedElements.end()) {
        ++iter;
        ++curr;
    }
    if(curr == sortedElements.size()){
        iter = sortedElements.end();
    }
    
    return *this;
}

    int MagicalContainer::AscendingIterator::operator*() {
        return sortedElements[static_cast<size_t>(getcurr())];
    }

    ariel::MagicalContainer::AscendingIterator::Iterator& ariel::MagicalContainer::AscendingIterator::Iterator::operator++()
    {
        ++iter;
        return *this;
    }

    
    int MagicalContainer::AscendingIterator::Iterator::operator*() const{
        return *iter;
    }    

    std::vector<int>::const_iterator MagicalContainer::AscendingIterator::Iterator:: getIter() const{
        return iter;
    }         

    bool MagicalContainer::AscendingIterator::operator==(const Iterator& other) const
    {
        return this->iter == other.getIter();
    }

    bool MagicalContainer::AscendingIterator::Iterator::operator!=(const Iterator& other) const {
        return !(iter == other.iter);
    }

    bool MagicalContainer::AscendingIterator::operator!=(const Iterator& other) const {
        return !(iter == other.getIter());
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const
    {
        return curr == other.curr && sortedElements.size() == other.sortedElements.size();
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
        return (sortedElements == other.sortedElements) && (curr < other.curr);
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
        return (curr > other.curr) && (sortedElements == other.sortedElements);
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
        return (sortedElements != other.sortedElements) || (curr != other.curr);
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other)
    {
        if (this->container.elements != other.container.elements){
                throw std::runtime_error("Attempted to increment beyond the end of the iterator");

        }
        if (this != &other)
        {
            container = other.container;
            sortedElements = other.sortedElements;
        }
        return *this;
    }

MagicalContainer:: AscendingIterator::Iterator MagicalContainer::AscendingIterator::begin() const 
{
    return Iterator(sortedElements.begin());
}

ariel::MagicalContainer::AscendingIterator::Iterator ariel::MagicalContainer::AscendingIterator::end() const
{
    return Iterator(sortedElements.end());
    
}



    // SideCrossIterator class member functions
    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& cont)
        : container(cont), crossOrderElements(cont.getElements()), numiter(0) {
        std::sort(crossOrderElements.begin(), crossOrderElements.end());
        std::vector<int> temp;
        temp.reserve(crossOrderElements.size());

        std::size_t mid = crossOrderElements.size() / 2;
        for (std::size_t i = 0; i < mid; ++i) {
            temp.push_back(crossOrderElements[i]);
            temp.push_back(crossOrderElements[crossOrderElements.size() - 1 - i]);
        }
        if (crossOrderElements.size() % 2 != 0) {
            temp.push_back(crossOrderElements[mid]);
        }

        crossOrderElements = std::move(temp);
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
        : container(other.container), crossOrderElements(other.crossOrderElements), iter(other.iter), numiter(other.numiter) 
    {
        std::sort(crossOrderElements.begin(), crossOrderElements.end());
        std::vector<int> temp;
        temp.reserve(crossOrderElements.size());

        std::size_t mid = crossOrderElements.size() / 2;
        for (std::size_t i = 0; i < mid; ++i) {
            temp.push_back(crossOrderElements[i]);
            temp.push_back(crossOrderElements[crossOrderElements.size() - 1 - i]);
        }
        if (crossOrderElements.size() % 2 != 0) {
            temp.push_back(crossOrderElements[mid]);
        }

        crossOrderElements = std::move(temp);
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator()
        : container(*(new MagicalContainer())), crossOrderElements(container.getElements()), iter(crossOrderElements.begin()), numiter(0) 
    {
                std::sort(crossOrderElements.begin(), crossOrderElements.end());
        std::vector<int> temp;
        temp.reserve(crossOrderElements.size());

        std::size_t mid = crossOrderElements.size() / 2;
        for (std::size_t i = 0; i < mid; ++i) {
            temp.push_back(crossOrderElements[i]);
            temp.push_back(crossOrderElements[crossOrderElements.size() - 1 - i]);
        }
        if (crossOrderElements.size() % 2 != 0) {
            temp.push_back(crossOrderElements[mid]);
        }

        crossOrderElements = std::move(temp);
    }

    MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

    MagicalContainer::SideCrossIterator::Iterator::Iterator(std::vector<int>::const_iterator iter): it(iter){ }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++()
    {
        if (numiter >= crossOrderElements.size()) {
                throw std::runtime_error("Attempted to increment beyond the end of the iterator");
            }
            if (iter != crossOrderElements.end()) {
                ++iter;
                ++numiter;
            }
            if(numiter == crossOrderElements.size()){
                iter = crossOrderElements.end();
            }
            
            return *this;
    }

    int MagicalContainer::SideCrossIterator::getnumiter(){
        return this->numiter;
    }


    int MagicalContainer::SideCrossIterator::operator*()
    {
        return crossOrderElements[static_cast<size_t>(getnumiter())];
        
    }

    ariel::MagicalContainer::SideCrossIterator::Iterator& ariel::MagicalContainer::SideCrossIterator::Iterator::operator++()
    {
        ++it;
        return *this;
    }

    
    int MagicalContainer::SideCrossIterator::Iterator::operator*() const{
        return *it;
    } 

    std::vector<int>::const_iterator MagicalContainer::SideCrossIterator::Iterator:: getIter() const
    {
        return it;
    } 

    bool MagicalContainer::SideCrossIterator::operator==(const Iterator& other) const
    {
        return this->iter == other.getIter();
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const Iterator& other) const
    {
        return !(iter == other.getIter());

    }

    bool MagicalContainer::SideCrossIterator::Iterator::operator!=(const Iterator& other) const {
        return !(it == other.it);
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const
    {
        return (this->crossOrderElements==other.crossOrderElements) && (this->numiter==other.numiter);

    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const
    {
        return (this->crossOrderElements!=other.crossOrderElements) || (this->numiter!=other.numiter);

    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const
    {
        return (this->crossOrderElements==other.crossOrderElements) && (this->numiter<other.numiter);

    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const
    {
        return (this->crossOrderElements==other.crossOrderElements) && (this->numiter>other.numiter);

    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other)
    {
        if (this->container.elements != other.container.elements){
            throw std::runtime_error("Attempted to increment beyond the end of the iterator");
        }
        if (this != &other) {
            crossOrderElements = other.crossOrderElements;
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator::Iterator MagicalContainer::SideCrossIterator::begin() const
    {
        return Iterator(crossOrderElements.begin());
    }

    MagicalContainer::SideCrossIterator::Iterator MagicalContainer::SideCrossIterator::end() const
    {
        return Iterator(crossOrderElements.end());
    }


    // PrimeIterator class member functions
    MagicalContainer::PrimeIterator::PrimeIterator(const ariel::MagicalContainer &cont):container(cont),curr(0)
    {

        for (size_t i = 0; i < cont.size(); i++)
        {
            if (isPrime((this->container.getElements())[i]))
            {
                this->primeElements.push_back((this->container.getElements())[i]);
            }
            
        }
                std::sort(primeElements.begin(), primeElements.end());

    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
        : container(other.container), primeElements(other.primeElements), it(other.it), curr(other.curr)
    {

        for (size_t i = 0; i < other.container.size(); i++)
        {
            if (isPrime((this->container.getElements())[i]))
            {
                this->primeElements.push_back((this->container.getElements())[i]);
            }
            
        }
                std::sort(primeElements.begin(), primeElements.end());

    }

    MagicalContainer::PrimeIterator::PrimeIterator()
        : container(*(new MagicalContainer())), primeElements(), it(primeElements.begin()), curr(0)
    {
        for (int element : container.getElements())
        {
            if (isPrime(element))
            {
                primeElements.push_back(element);
            }
        }
    }

    MagicalContainer::PrimeIterator::~PrimeIterator(){ }


    bool MagicalContainer::PrimeIterator::isPrime(int number)
    {
        if (number < 2)
        {
            return false;
        }

        for (int i = 2; i <= number / 2; ++i)
        {
            if (number % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    MagicalContainer::PrimeIterator::Iterator::Iterator(std::vector<int>::const_iterator iter)
        : it(iter)
    {
    }

    ariel::MagicalContainer::PrimeIterator& ariel::MagicalContainer::PrimeIterator::operator++()
    {
        if (curr >= primeElements.size()) {
            throw std::runtime_error("Attempted to increment beyond the end of the iterator");
        }
        if (it != primeElements.end()) {
            ++it;
            ++curr;
        }
        if(curr == primeElements.size()){
            it = primeElements.end();
        }
        
        return *this;
    }

    int MagicalContainer::PrimeIterator::operator*()
    {
        return primeElements[static_cast<size_t>(curr)];
        
    }
    
    std::vector<int>::const_iterator MagicalContainer::PrimeIterator::Iterator:: getIter() const
    {
        return it;
    } 

    ariel::MagicalContainer::PrimeIterator::Iterator& ariel::MagicalContainer::PrimeIterator::Iterator::operator++()
    {
        ++it;
        return *this;
    }

    
    int MagicalContainer::PrimeIterator::Iterator::operator*() const{
        return *it;
    } 

    bool MagicalContainer::PrimeIterator::operator==(const Iterator& other) const
    {
        return this->it == other.getIter();
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const
    {
        return (this->primeElements==other.primeElements && this->curr==other.curr);

    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const
    {
        return (this->primeElements==other.primeElements ) && (this->curr<other.curr);

    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const
    {
        return (this->primeElements==other.primeElements ) && (this->curr>other.curr);

    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const
    {
        return (this->primeElements!=other.primeElements) || (this->curr!=other.curr);

    }

    bool MagicalContainer::PrimeIterator::operator!=(const Iterator& other) const
    {
        return !(it == other.getIter());
    }

    bool MagicalContainer::PrimeIterator::Iterator::operator!=(const Iterator& other) const {
        return !(it == other.it);
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other)
    {
        if (this->container.elements != other.container.elements){
            throw std::runtime_error("Attempted to increment beyond the end of the iterator");
        }    
        if (this != &other) {
            primeElements = other.primeElements;
        }
        return *this;
    }


    MagicalContainer::PrimeIterator::Iterator MagicalContainer::PrimeIterator::begin() const
    {
        return Iterator(primeElements.begin());
    }

    MagicalContainer::PrimeIterator::Iterator MagicalContainer::PrimeIterator::end() const
    {
        return Iterator(primeElements.end());
    }
} // namespace ariel
