//
//  main.cpp
//  Reverse Iterator
//
//  Created by Angel Munoz on 2/26/26.
//



#include <cstddef>
#include <memory>
#include <iostream>

using namespace std;

template <typename T>
class SimpleVec {
public:
   
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;

    
    using iterator       = pointer;
    using const_iterator = const_pointer;

    
    class reverse_iterator;
   
    class const_reverse_iterator;

    
    SimpleVec() : data_(nullptr), size_(0), capacity_(0) {}
    explicit SimpleVec(size_type n, const T& val = T())
        : data_(nullptr), size_(0), capacity_(0)
    {
        reserve(n);
        for (size_type i = 0; i < n; ++i) {
            push_back(val);
        }
    }

    

    ~SimpleVec() { delete[] data_; }

    // ---------- capacity ----------
    size_type size() const noexcept { return size_; }
    size_type capacity() const noexcept { return capacity_; }
    bool empty() const noexcept { return size_ == 0; }

    void reserve(size_type new_cap) {
        if (new_cap <= capacity_) return;
        T* new_data = new T[new_cap];
        for (size_type i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

    void resize(size_type new_size, const T& val = T()) {
        if (new_size > capacity_) reserve(new_size);
        for (size_type i = size_; i < new_size; ++i) {
            data_[i] = val;
        }
        size_ = new_size;
    }

    // ---------- element access ----------
    reference operator[](size_type i) { return data_[i]; }
    const_reference operator[](size_type i) const { return data_[i]; }

    reference at(size_type i) {
        if (i >= size_) throw out_of_range("SimpleVec::at");
        return data_[i];
    }
    const_reference at(size_type i) const {
        if (i >= size_) throw out_of_range("SimpleVec::at");
        return data_[i];
    }

    
    iterator begin() noexcept { return data_; }
    iterator end() noexcept { return data_ + size_; }
    const_iterator begin() const noexcept { return data_; }
    const_iterator end() const noexcept { return data_ + size_; }
    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend() const noexcept { return end(); }

    
    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }
    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }
    const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    const_reverse_iterator crend()   const noexcept { return rend(); }

    // ---------- modifiers ----------
    void push_back(const T& value) {
        if (size_ == capacity_) {
            // grow by doubling (or 1 if empty)
            size_type new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
            reserve(new_cap);
        }
        data_[size_++] = value;
    }

  
    class reverse_iterator {
    public:
        // iterator traits
        using iterator_type = iterator;
        using value_type      = T;
        using difference_type = ptrdiff_t;
        using pointer         = T*;
        using reference       = T&;

        
        explicit reverse_iterator(iterator it) : current(it) {}

        
        iterator base() const { return current; }

        
        reference operator*() const {
            iterator tmp = current;
            --tmp;                // step back to the element we are “pointing” to
            return *tmp;
        }

        pointer operator->() const { return &(operator*()); }

        
        reference operator[](difference_type n) const {
            // *this + n gives the iterator at offset n, then deref
            return *(*this + n);
        }

       
        reverse_iterator operator+(difference_type n) const {
            // moving “backwards” in the underlying sequence means moving the
            // base iterator forward.
            return reverse_iterator(current - n);
        }

        reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(current + n);
        }

        
        difference_type operator-(const reverse_iterator& other) const {
            // note the order: underlying iterators are reversed,
            // so the sign is flipped.
            return other.current - current;
        }

        
        
        reverse_iterator& operator++() {
            --current;
            return *this;
        }

        
        reverse_iterator operator++(int) {
            reverse_iterator tmp = *this;
            --current;
            return tmp;
        }

        
        reverse_iterator& operator--() {
            ++current;
            return *this;
        }

        
        reverse_iterator operator--(int) {
            reverse_iterator tmp = *this;
            ++current;
            return tmp;
        }

        
        bool operator==(const reverse_iterator& other) const {
            return current == other.current;
        }
        bool operator!=(const reverse_iterator& other) const {
            return current != other.current;
        }

    private:
        iterator current;   // points **one past** the element the reverse_iterator refers to
    };

    
    class const_reverse_iterator {
    public:
        using iterator_type = const_iterator;
        using value_type      = T;
        using difference_type = ptrdiff_t;
        using pointer         = const T*;
        using reference       = const T&;

        explicit const_reverse_iterator(const_iterator it) : current(it) {}

        const_iterator base() const { return current; }

        reference operator*() const {
            const_iterator tmp = current;
            --tmp;
            return *tmp;
        }

        pointer operator->() const { return &(operator*()); }

        reference operator[](difference_type n) const {
            return *(*this + n);
        }

        const_reverse_iterator operator+(difference_type n) const {
            return const_reverse_iterator(current - n);
        }

        const_reverse_iterator operator-(difference_type n) const {
            return const_reverse_iterator(current + n);
        }

        difference_type operator-(const const_reverse_iterator& other) const {
            return other.current - current;
        }

        const_reverse_iterator& operator++() { --current; return *this; }
        const_reverse_iterator operator++(int) { const_reverse_iterator t = *this; --current; return t; }
        const_reverse_iterator& operator--() { ++current; return *this; }
        const_reverse_iterator operator--(int) { const_reverse_iterator t = *this; ++current; return t; }

        bool operator==(const const_reverse_iterator& o) const { return current == o.current; }
        bool operator!=(const const_reverse_iterator& o) const { return current != o.current; }

    private:
        const_iterator current;
    };

private:
    T*         data_;
    size_type  size_;
    size_type  capacity_;
};


int main() {
    SimpleVec<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    
    cout << "Forward:  ";
    for (auto it = v.begin(); it != v.end(); ++it)
        cout << *it << ' ';
    cout << '\n';
    
    cout << "Reverse:  ";
    for (auto it = v.rbegin(); it != v.rend(); ++it)
        cout << *it << ' ';
    cout << '\n';
    
    
    auto it = v.rbegin();
    cout << "*rbegin()      = " << *it << '\n';
    cout << "*(rbegin()+1)  = " << *(it + 1) << '\n';
    cout << "rbegin()[2]    = " << it[2] << '\n';
    auto it2 = v.rend() - 1;
    
}
