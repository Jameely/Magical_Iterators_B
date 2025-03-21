#ifndef MAGICAL_ITERATORS_MAGICALCONTAINER_HPP
#define MAGICAL_ITERATORS_MAGICALCONTAINER_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>
#include "cmath"

using namespace std;
namespace ariel {

    class MagicalContainer {
    private:
        vector<int> Elements;
        vector<int> vecPrime;
        static bool isPrime(int number);

    public:
        MagicalContainer();
        void addElement(int element);
        void removeElement(int element);
        size_t size() const;
        const vector<int> &getElements () const;

        enum class IteratorType { A, S, P };

        class Iterator {
        private:
            IteratorType iterType;
        public:
            Iterator(IteratorType iterType);
            Iterator() ;
            ~Iterator();
                       
            Iterator &operator=(const Iterator &other) = default;           
            Iterator& operator=(Iterator&& other) = default;       

            virtual bool operator==(const Iterator& other) const =0 ;
            virtual bool operator!=(const Iterator& other) const =0;
            virtual bool operator>(const Iterator& other) const  =0;
            virtual bool operator<(const Iterator& other) const  =0;         

             IteratorType getIterType() const {return iterType;};
        };
        class AscendingIterator : public Iterator{
        private:
            MagicalContainer &container;
            size_t curr;
        public:
            AscendingIterator();
            AscendingIterator(MagicalContainer &container);
            AscendingIterator(MagicalContainer &container, size_t index);

            ~AscendingIterator();

            AscendingIterator(const AscendingIterator &other);                          
            AscendingIterator(AscendingIterator &&) noexcept = delete;                 
            AscendingIterator &operator=(const AscendingIterator &other);                
            AscendingIterator &operator=(AscendingIterator &&) noexcept = delete;      

            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            bool operator>(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;

            bool operator==(const Iterator& other) const override;
            bool operator!=(const Iterator& other) const override;
            bool operator>(const Iterator& other) const  override;
            bool operator<(const Iterator& other) const  override;

            int operator*() const;

            AscendingIterator &operator++();

            AscendingIterator begin();
            AscendingIterator end();

            MagicalContainer &getContainer() const;
            size_t getCurr() const;

        };

        class SideCrossIterator : public Iterator {
        private:
            MagicalContainer &container;
            size_t front, back;
            int iters = 0;

        public:
            SideCrossIterator();
            SideCrossIterator(MagicalContainer &container);
            SideCrossIterator(MagicalContainer &container, size_t frontIndex, size_t backIndex);

            ~SideCrossIterator();

            SideCrossIterator(const SideCrossIterator &other);                          
            SideCrossIterator(SideCrossIterator &&) noexcept = delete;                  
            SideCrossIterator &operator=(const SideCrossIterator &other);              
            SideCrossIterator &operator=(SideCrossIterator &&) noexcept = delete;       

            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;

            bool operator==(const Iterator& other) const override;
            bool operator!=(const Iterator& other) const override;
            bool operator>(const Iterator& other) const  override;
            bool operator<(const Iterator& other) const  override;

            int operator*() const;

            SideCrossIterator &operator++();

            SideCrossIterator begin();
            SideCrossIterator end();

            MagicalContainer &getContainer() const;
            size_t getFront() const;
            size_t getBack() const;
        };

     

        class PrimeIterator : public Iterator{
        private:
            MagicalContainer &container;
            size_t in;
        public:
            PrimeIterator();
            PrimeIterator(MagicalContainer &container);
            PrimeIterator(MagicalContainer &container, size_t index);
            PrimeIterator(const PrimeIterator &other);
            ~PrimeIterator();
            PrimeIterator(PrimeIterator &&) noexcept = delete;

            PrimeIterator &operator=(PrimeIterator &&) noexcept = delete;
            PrimeIterator &operator=(const PrimeIterator &other);

            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            bool operator>(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;

            bool operator==(const Iterator& other) const override;
            bool operator!=(const Iterator& other) const override;
            bool operator>(const Iterator& other) const  override;
            bool operator<(const Iterator& other) const  override;

            int operator*() const;

            PrimeIterator &operator++();

            PrimeIterator begin();
            PrimeIterator end();

            MagicalContainer &getContainer() const;
            size_t getInd() const;
        };
    };
}
#endif //MAGICAL_ITERATORS_MAGICALCONTAINER_HPP
