#ifndef SLICE_ITER_H
#define SLICE_ITER_H

#include <valarray>

using namespace std;

template <class T> class Slice_iter {
public:
  valarray<T> *v;
  slice s;
  size_t curr; // index of current index

  T &ref(size_t i) const { return (*v)[s.start() + i * s.stride()]; }

public:
  Slice_iter(valarray<T> *vv, slice ss) : v(vv), s(ss), curr(0) {}

  Slice_iter end() {
    Slice_iter t = *this;
    t.curr = s.size(); // index of last_plus_one item
    return t;
  }

  Slice_iter &operator++() {
    curr++;
    return *this;
  }
  Slice_iter operator++(int) {
    Slice_iter t = *this;
    curr++;
    return t;
  }

  T &operator[](size_t i) { return ref(curr = i); } // C style subscripting
  T &operator()(size_t i) {
    return ref(curr = i);
  }                                    // FORTRAN style
                                       // subscripting
  T &operator*() { return ref(curr); } // Current element

  // ver que falta

  ~Slice_iter() {}
};

template <class T>
bool operator==(const Slice_iter<T> &p, const Slice_iter<T> &q) {
  return p.curr == q.curr && p.s.stride() == q.s.stride() &&
         p.s.start() == q.s.start();
}

template <class T>
bool operator!=(const Slice_iter<T> &p, const Slice_iter<T> &q) {
  return !(p == q);
}

template <class T>
bool operator<(const Slice_iter<T> &p, const Slice_iter<T> &q) {
  return p.curr < q.curr && p.s.stride() == q.s.stride() &&
         p.s.start() == q.s.start();
}

template <class T>
bool operator>(const Slice_iter<T> &p, const Slice_iter<T> &q) {
  return !(p < q);
}

template <class T>
inline valarray<T> operator*(double d, const Slice_iter<T> &p) {
  valarray<T> r(p.s.size());
  for (size_t i = 0; i < r.size(); ++i) {
    r[i] = d * p.ref(i);
  }
  return r;
}

template <class T> class CSlice_iter {
public:
  valarray<T> *v;
  slice s;
  size_t curr; // index of current index

  T &ref(size_t i) const { return (*v)[s.start() + i * s.stride()]; }

public:
  CSlice_iter(valarray<T> *vv, slice ss) : v(vv), s(ss), curr(0) {}

  CSlice_iter end() {
    CSlice_iter t = *this;
    t.curr = s.size(); // index of last_plus_one item
    return t;
  }

  CSlice_iter &operator++() {
    curr++;
    return *this;
  }
  CSlice_iter operator++(int) {
    CSlice_iter t = *this;
    curr++;
    return t;
  }

  const T &operator[](size_t i) {
    return ref(curr = i);
  } // C style
    // subscripting
  const T &operator()(size_t i) {
    return ref(curr = i);
  }                                          // FORTRAN style subscripting
  const T &operator*() { return ref(curr); } // Current element

  // Ver que falta

  ~CSlice_iter() {}
};

template <class T>
bool operator==(const CSlice_iter<T> &p, const CSlice_iter<T> &q) {
  return p.curr == q.curr && p.s.stride() == q.s.stride() &&
         p.s.start() == q.s.start();
}

template <class T>
bool operator!=(const CSlice_iter<T> &p, const CSlice_iter<T> &q) {
  return !(p == q);
}

template <class T>
bool operator<(const CSlice_iter<T> &p, const CSlice_iter<T> &q) {
  return p.curr < q.curr && p.s.stride() == q.s.stride() &&
         p.s.start() == q.s.start();
}

template <class T>
bool operator>(const CSlice_iter<T> &p, const CSlice_iter<T> &q) {
  return !(p < q);
}

template <class T>
inline valarray<T> operator*(double d, const CSlice_iter<T> &p) {
  valarray<T> r(p.s.size());
  for (size_t i = 0; i < r.size(); ++i) {
    r[i] = d * p.ref(i);
  }
  return r;
}

#endif // SLICE_ITER_H
