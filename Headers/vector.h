#include <memory>
#include <algorithm>

template <class T>
class Vector {
   public:
      typedef T* iterator;
      typedef const T* const_iterator;
      typedef ptrdiff_t difference_type;
      typedef size_t size_type;
      typedef T value_type;
      typedef value_type &reference;
      typedef const value_type &const_reference;

      // ==CONSTRUCTORS && DESTRUCTOR==
      Vector() {
         create();
      }

      explicit Vector(size_type n, const T& value = T{}) {
         create(n, value);
      }

      Vector(const Vector& source) {
         create(source.begin(), source.end());
      }

      Vector(Vector&& source) noexcept : data{source.data}, avail{source.avail}, limit{source.limit} {
         source.data = source.avail = source.limit = nullptr;
      }

      ~Vector() {
         uncreate();
      }

      Vector& operator=(const Vector& source) {
         if (this == &source)
            return *this;
         
         uncreate();
         create(source.begin(), source.end());
         return *this;
      }

      Vector& operator=(Vector&& source) noexcept {
         if (this == &source)
            return *this;
         
         uncreate();
         std::swap(source.data, data);
         std::swap(source.avail, avail);
         std::swap(source.limit, limit);
      }


      // ==ELEMENT ACCESS==
      reference at(size_type index) {
         if (index >= size())
            throw std::out_of_range("Index out of range");
         
         return data[index];
      }

      const_reference at(size_type index) const {
         if (index >= size())
            throw std::out_of_range("Index out of range");
         
         return data[index];
      }

      reference operator[](size_type index) {
         if (index >= size())
            throw std::out_of_range("Index out of range");
         
         return data[index];
      }

      const_reference operator[](size_type index) const {
         if (index >= size())
            throw std::out_of_range("Index out of range");
         
         return data[index];
      }

      reference front() {
         return *data;
      }

      const_reference front() const {
         return *data;
      }

      reference back() {
         return *(avail - 1);
      }

      const_reference back() const {
         return *(avail - 1);
      }

      T* eData() noexcept {
         return data;
      }

      const T* eData() const noexcept {
         return data;
      }


      // ==ITERATORS==
      iterator begin() noexcept {
         return data;
      }

      const_iterator begin() const noexcept {
         return data;
      }

      const_iterator cbegin() const noexcept {
         return data;
      }

      iterator end() noexcept {
         return avail;
      }

      const_iterator end() const noexcept {
         return avail;
      }

      const_iterator cend() const noexcept {
         return avail;
      }

      iterator rbegin() noexcept {
         return avail - 1;
      }

      const_iterator rbegin() const noexcept {
         return avail - 1;
      }

      const_iterator crbegin() const noexcept {
         return avail - 1;
      }

      iterator rend() noexcept {
         return data - 1;
      }

      const_iterator rend() const noexcept {
         return data - 1;
      }

      const_iterator crend() const noexcept {
         return data - 1;
      }


      // ==CAPACITY==
      bool empty() const {
         if (data == nullptr)
            return true;
         else
            return false;
      }

      size_type size() const {
         return avail - data;
      }

      size_type max_size() const {
         return std::numeric_limits<size_type>::max() / sizeof(T);
      }

      void reserve(size_type newCapacity) {
         if (newCapacity > capacity()) {
            iterator new_data = alloc.allocate(newCapacity);
            iterator new_avail = std::uninitialized_copy(data, avail, new_data);
            uncreate();
            data = new_data;
            avail = new_avail;
            limit = data + newCapacity;
         }
      }

      size_type capacity() const {
         return limit - data;
      }

      void shrink_to_fit() {
         if (size() < capacity()) {
            iterator new_data = alloc.allocate(size());
            iterator new_avail = std::uninitialized_copy(data, avail, new_data);
            uncreate();

            data = new_data;
            avail = new_avail;
            limit = data + size();
         }
      }

      // ==MODIFIERS==
      void clear() {
         uncreate();
      }

      void push_back(const T& value) {
         if (avail == limit)
            grow();
         
         unchecked_append(value);
      }

      void emplace_back(const T& value) {
         if (avail == limit)
            grow();
         
         unchecked_append(value);
      }

      void pop_back() {
         if (data == avail)
            throw std::out_of_range("Vector is empty");
         
         alloc.destroy(--avail);
      }

      void resize(size_type n, const T& value = T{}) {
         if (n > max_size())
            throw std::out_of_range("Exceeded maximum size limit");
         
         if (n > size()) {
            if (n > capacity())
               reserve(n * 2);
            
            while (size() < n) {
               unchecked_append(value);
            }
         }
         else if (n < size()) {
            while (size() > n)
               pop_back();
         }
      }

      void swap(Vector& other) noexcept {
         std::swap(data, other.data);
         std::swap(avail, other.avail);
         std::swap(limit, other.limit);
      }


      // ==NON-MEMBER FUNCTIONS==
      bool operator==(const Vector<T>& rhs) {
         if (size() != rhs.size()) {
            return false;
         }
         for (auto i = 0; i < size(); ++i) {
            if (eData()[i] != rhs.eData()[i]) {
                  return false;
            }
         }
         return true;
      }

      bool operator!=(const Vector<T>& rhs) {
         return *this != rhs;
      }

      bool operator<(const Vector<T>& rhs) {
         return *this < rhs;
      }

      bool operator>(const Vector<T>& rhs) {
         return *this > rhs;
      }

      bool operator<=(const Vector<T>& rhs) {
         return *this <= rhs;
      }

      bool operator>=(const Vector<T>& rhs) {
         return *this >= rhs;
      }

      void swap(Vector<T>& lhs, Vector<T>& rhs) {
         lhs.swap(rhs);
      }

   
   private:
      iterator data;
      iterator avail;
      iterator limit;

      std::allocator<T> alloc;

      void create() {
         data = avail = limit = nullptr;
      }

      void create(size_type n, const T& value) {
         if (n > max_size())
            throw std::out_of_range("Exceeded maximum size limit");
         
         data = alloc.allocate(n);
         limit = avail = data + n;
         std::uninitialized_fill(data, limit, value);
      }

      void create(const_iterator begin, const_iterator end) {
         data = alloc.allocate(end - begin);
         limit = avail = std::uninitialized_copy(begin, end, data);
      }

      void uncreate() {
         if (data) {
            iterator it = avail;
            while (it != data)
               alloc.destroy(--it);
            
            alloc.deallocate(data, limit - data);
         }
         data = limit = avail = nullptr;
      }

      void grow() {
         size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));
         iterator new_data = alloc.allocate(new_size);
         iterator new_avail = std::uninitialized_copy(data, avail, new_data);
         uncreate();

         data = new_data;
         avail = new_avail;
         limit = data + new_size;
      }

      void unchecked_append(const T& value) {
         alloc.construct(avail++, value);
      }
};
template<class T>
class allocator {
  public:
    T* allocate(size_t);
    void deallocate(T*, size_t);
    void construct(T*, const T&);
    void destroy(T*);
};