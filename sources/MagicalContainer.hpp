#ifndef MAGICALCONTAINER_H
#define MAGICALCONTAINER_H

#include <vector>
#include <algorithm>

namespace ariel {

class MagicalContainer {
private:
    std::vector<int> elements;

public:
    // Function to add an element to the container
    void addElement(int element);

    // Function to remove an element from the container
    void removeElement(int element);

    // Function to get the size of the container
    int size() const;

    // Function to get a reference to the elements in the container
    const std::vector<int>& getElements() const;

    class AscendingIterator {
    private:
        MagicalContainer& container;  // Reference to the MagicalContainer object
        std::vector<int> sortedElements;  // Sorted elements of the container
        std::vector<int>::const_iterator iter;  // Iterator pointing to the current element
        int curr;  // Current index

    public:
        // Constructor that takes a reference to the MagicalContainer object
        AscendingIterator(MagicalContainer& container);

        // Copy constructor
        AscendingIterator(const AscendingIterator& Other);

        // Default constructor
        AscendingIterator();

        // Destructor
        ~AscendingIterator();

        class Iterator {
        private:
            std::vector<int>::const_iterator iter;  // Iterator pointing to the current element

        public:
            // Constructor that takes an iterator
            Iterator(std::vector<int>::const_iterator iter);

            // Comparison operator for inequality
            bool operator!=(const Iterator& other) const;

            // Dereference operator
            int operator*() const;

            // Increment operator
            Iterator& operator++();

            // Function to get the underlying iterator
            std::vector<int>::const_iterator getIter() const;
        };

        // Function to get the current index
        int getcurr();

        // Dereference operator
        int operator*();

        // Increment operator
        AscendingIterator& operator++();

        // Comparison operator for equality with Iterator
        bool operator==(const Iterator& other) const;

        // Comparison operator for equality with AscendingIterator
        bool operator==(const AscendingIterator& other) const;

        // Comparison operator for less than
        bool operator<(const AscendingIterator& other) const;

        // Comparison operator for greater than
        bool operator>(const AscendingIterator& other) const;

        // Comparison operator for inequality with Iterator
        bool operator!=(const AscendingIterator& other) const;

        // Comparison operator for inequality with AscendingIterator
        bool operator!=(const Iterator& other) const;

        //Assigment operator
        AscendingIterator& operator=(const AscendingIterator& other);

        // Function to create an iterator pointing to the beginning of the container
        Iterator begin() const;

        // Function to create an iterator pointing to the end of the container
        Iterator end() const;
    };

    class SideCrossIterator {
    private:
        const MagicalContainer& container;  // Reference to the MagicalContainer object
        std::vector<int> crossOrderElements;  // Elements in cross order
        std::vector<int>::const_iterator iter;  // Iterator pointing to the current element
        int numiter;  // Number of iterations

    public:
        class Iterator {
        private:
            std::vector<int>::const_iterator it;  // Iterator pointing to the current element

        public:
            // Constructor that takes an iterator
            Iterator(std::vector<int>::const_iterator iter);

            // Function to get the underlying iterator
            std::vector<int>::const_iterator getIter() const;

            // Comparison operator for inequality
            bool operator!=(const Iterator& other) const;

            // Dereference operator
            int operator*() const;

            // Increment operator
            Iterator& operator++();
        };

        // Constructor that takes a reference to the MagicalContainer object
        SideCrossIterator(const MagicalContainer& cont);

        // Copy constructor
        SideCrossIterator(const SideCrossIterator& Other);

        // Default constructor
        SideCrossIterator();

        // Destructor
        ~SideCrossIterator();

        // Function to get the number of iterations
        int getnumiter();

        // Dereference operator
        int operator*();

        // Increment operator
        SideCrossIterator& operator++();

        // Comparison operator for equality with Iterator
        bool operator==(const Iterator& other) const;

        // Comparison operator for equality with SideCrossIterator
        bool operator==(const SideCrossIterator& other) const;

        // Comparison operator for inequality with SideCrossIterator
        bool operator!=(const SideCrossIterator& other) const;

        // Comparison operator for less than
        bool operator<(const SideCrossIterator& other) const;

        // Comparison operator for greater than
        bool operator>(const SideCrossIterator& other) const;

        // Comparison operator for inequality with Iterator
        bool operator!=(const Iterator& other) const;

        // Assignment operator
        SideCrossIterator& operator=(const SideCrossIterator& other);

        // Function to create an iterator pointing to the beginning of the container
        Iterator begin() const;

        // Function to create an iterator pointing to the end of the container
        Iterator end() const;
    };

    class PrimeIterator {
    private:
        const MagicalContainer& container;  // Reference to the MagicalContainer object
        std::vector<int> primeElements;  // Prime elements of the container
        std::vector<int>::const_iterator it;  // Iterator pointing to the current element
        int curr;  // Current index

        // Function to check if a number is prime
        bool isPrime(int number);

    public:
        // Constructor that takes a reference to the MagicalContainer object
        PrimeIterator(const MagicalContainer& cont);

        // Copy constructor
        PrimeIterator(const PrimeIterator& Other);

        // Default constructor
        PrimeIterator();

        // Destructor
        ~PrimeIterator();

        class Iterator {
        private:
            std::vector<int>::const_iterator it;  // Iterator pointing to the current element

        public:
            // Constructor that takes an iterator
            Iterator(std::vector<int>::const_iterator iter);

            // Function to get the underlying iterator
            std::vector<int>::const_iterator getIter() const;

            // Comparison operator for inequality
            bool operator!=(const Iterator& other) const;

            // Dereference operator
            int operator*() const;

            // Increment operator
            Iterator& operator++();
        };

        // Dereference operator
        int operator*();

        // Increment operator
        PrimeIterator& operator++();

        // Comparison operator for equality with Iterator
        bool operator==(const Iterator& other) const;

        // Comparison operator for equality with PrimeIterator
        bool operator==(const PrimeIterator& other) const;

        // Comparison operator for less than
        bool operator<(const PrimeIterator& other) const;

        // Comparison operator for greater than
        bool operator>(const PrimeIterator& other) const;

        // Comparison operator for inequality with PrimeIterator
        bool operator!=(const PrimeIterator& other) const;

        // Comparison operator for inequality with Iterator
        bool operator!=(const Iterator& other) const;

        // Assignment operator
        PrimeIterator& operator=(const PrimeIterator& other);

        // Function to create an iterator pointing to the beginning of the container
        Iterator begin() const;

        // Function to create an iterator pointing to the end of the container
        Iterator end() const;
    };
};

} // namespace ariel

#endif
