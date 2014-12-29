#ifndef SWAP_H
#define SWAP_H

template <typename T, size_t S>
void swap(array<T,S>& a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}

// This can be replaced by std::swap if #include<algorithm> is added as header in the header that is using it
template <typename T>
void swap(T& t1, T& t2) {
  T temp = t1;
  t1 = t2;
  t2 = temp;
}

#endif // SWAP_H
