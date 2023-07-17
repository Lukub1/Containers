using namespace s21;

template <typename T>
vector<T>::vector() : arr(nullptr), m_size(0), m_capacity(0) {}

template <typename T>
vector<T>::vector(size_type n) try : arr(new T[n]), m_size(n), m_capacity(n) {
  for (size_type i = 0; i < m_size; i++) arr[i] = 0;
  std::cout << std::endl;
} catch (int &e) {
  if (arr) delete[] arr;
  e = 1;
  throw std::invalid_argument("vector(n), exception");
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : vector(items.size()) {
  std::copy(items.begin(), items.end(), begin());
}

template <typename T>
vector<T>::vector(const vector &v) {
  m_size = v.m_size;
  m_capacity = v.m_size;
  if (v.begin()) {
    arr = new T[m_size];
    std::copy(v.begin(), v.end(), begin());
  } else {
    arr = nullptr;
  }
}

template <typename T>
vector<T>::vector(vector &&v)
    : arr(v.arr), m_size(v.m_size), m_capacity(v.m_capacity) {
  v.arr = nullptr;
  v.m_size = 0;
}

template <typename T>
void vector<T>::destroy() {
  if (arr) delete[] arr;
}

template <typename T>
vector<T>::~vector() {
  destroy();
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&v) {
  destroy();
  arr = v.arr;
  m_size = v.m_size;
  m_capacity = v.m_capacity;
  v.arr = nullptr;
  return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(const vector &v) {
  auto temp_v = v;
  if (temp_v.size() > size()) {
    if (temp_v.capacity() > m_capacity) m_capacity = temp_v.capacity();
    value_type *newarr = new value_type[temp_v.size()];
    std::copy(temp_v.begin(), temp_v.end(), newarr);
    delete[] arr;
    arr = newarr;
  } else {
    m_size = temp_v.size();
    std::copy(temp_v.begin(), temp_v.end(), begin());
  }
  m_size = temp_v.size();
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= m_size) {
    throw std::out_of_range("n >= size");
  }
  return arr[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return arr[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  return arr[0];
}

template <typename T>
typename vector<T>::reference vector<T>::front() {
  return arr[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  return arr[m_size - 1];
}

template <typename T>
typename vector<T>::reference vector<T>::back() {
  return arr[m_size - 1];
}

template <typename T>
typename vector<T>::iterator vector<T>::data() {
  return arr;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return arr;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return arr;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return arr + m_size;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return arr + m_size;
}

template <typename T>
bool vector<T>::empty() {
  return m_size == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return m_size;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return m_capacity;
}

template <typename T>
template <typename iterator_type>
typename vector<T>::iterator vector<T>::insert(iterator_type pos,
                                               const_reference value) {
  T *newarr = nullptr;
  if (size() + 1 > capacity()) {
    newarr = new T[m_size + 1];
  } else {
    newarr = begin();
  }
  auto nai = newarr;
  auto i = begin();
  for (; i != pos; i++, nai++) {
    *nai = *i;
  }
  *nai = value;
  T *res = nai;
  nai++;
  for (; i != end(); i++, nai++) {
    *nai = *i;
  }
  if (newarr != begin()) {
    delete[] arr;
    arr = newarr;
  }
  m_size++;
  if (m_capacity < m_size) m_capacity = m_size;
  return res;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (capacity() < size) {
    m_capacity = size;
    T *newarr = new T[m_capacity];
    std::copy(begin(), end(), newarr);
    delete[] arr;
    arr = newarr;
  }
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size() != capacity()) {
    m_capacity = m_size;
    T *newarr = new T[m_size];
    std::copy(begin(), end(), newarr);
    delete[] arr;
    arr = newarr;
  }
}

template <typename T>
void vector<T>::clear() {
  m_size = 0;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  T *newarr = new T[m_capacity];
  auto nai = newarr;
  auto i = begin();
  for (; i != pos; i++, nai++) {
    *nai = *i;
  }
  i++;
  for (; i != end(); i++, nai++) {
    *nai = *i;
  }
  delete[] arr;
  arr = newarr;
  m_size--;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename T>
void vector<T>::pop_back() {
  m_size--;
}

template <typename T>
void vector<T>::swap(vector &other) {
  auto size_temp = m_size;
  auto capacity_temp = m_capacity;
  auto array_temp = arr;
  m_size = other.size();
  m_capacity = other.capacity();
  arr = other.begin();
  other.m_capacity = capacity_temp;
  other.m_size = size_temp;
  other.arr = array_temp;
}

template <class T>
typename vector<T>::size_type vector<T>::max_size() {
  return static_cast<size_type>(pow(2.0, 64.0) /
                                static_cast<T>(sizeof(value_type))) /
             2 -
         1;
}
