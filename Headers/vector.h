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


      // ==MEMBER FUNCTIONS==
      Vector() {
         create();
      }

      explicit Vector(size_type n, const T& value = T{}) {
         create(n, value);
      }

      Vector(const Vector& a) {
         create(a.begin(), a.end());
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

      Vector& operator=(const Vector& source) noexcept {
         if (this == &source)
            return *this;
         
         uncreate();
         std::swap(a.data, data);
         std::swap(a.avail, avail);
         std::swap(a.limit, limit);
      }


      // ==ELEMENT ACCESS==
      reference at(size_type index) {
         if (index >= size() || index < 0)
            throw std::out_of_range("Index out of range");
         
         return data[index];
      }

      const_reference at(size_type index) const {
         if (index >= size() || index < 0)
            throw std::out_of_range("Index out of range");
         
         return data[index];
      }

      reference operator[](size_type index) {
         if (index >= size() || index < 0)
            throw std::out_of_range("Index out of range");
         
         return data[index];
      }

      const_reference operator[](size_type index) const {
         if (index >= size() || index < 0)
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

      T* data() noexcept {
         return data;
      }

      const T* data() const noexcept {
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

      size_type reserve(size_type newCapacity) {
         if (new_capacity > max_size() || n < 0)
            throw std::out_of_range("Exceeded maximum size limit");
         
         if (newCapacity > capacity()) {
            iterator new_data = alloc.allocate(n);
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

      iterator insert(iterator position, const T& value) {
         if (position < begin() || position > end())
            throw std::out_of_range("Position out of range");
         
         if (avail == limit)
            grow();
         
         iterator it = avail;
         while (it != position) {
            *it = *(it - 1);
            --it;
         }
         *position = value;
         ++avail;
         return position;
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
         if (n > max_size() || n < 0)
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