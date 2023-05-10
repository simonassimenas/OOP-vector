
# OOP - Vector class

## Aprašymas

## Vektorių funkcijų palyginimas

### size()
```
std::vector<int> native;

native.push_back(1);
native.push_back(2);
native.push_back(3);
native.push_back(4);

std::cout << "Native vector size: " << native.size() << std::endl;
```
Išvestis: 4
```
Vector<int> custom;

custom.push_back(1);
custom.push_back(2);
custom.push_back(3);
custom.push_back(4);

std::cout << "Custom vector size: " << custom.size() << std::endl;
```
Išvestis: 4

### capacity()
```
std::vector<int> native;

native.reserve(222);

std::cout << "Native vector capacity: " << native.capacity() << std::endl;
```
Išvestis: 222
```
Vector<int> custom;

custom.reserve(333);

std::cout << "Custom vector capacity: " << custom.capacity() << std::endl;
```
Išvestis: 333

### max_size()
```
std::vector<int> native;

std::cout << "Native vector max size: " << native.max_size() << std::endl;
```
OUTPUT: 4611686018427387903

```
Vector<int> custom;
std::cout << "Custom vector max size: " << custom.max_size() << std::endl;
```
OUTPUT: 4611686018427387903

### front()
```
std::vector<int> native;
Vector<int> custom;

std::cout << "Native vector front: " << native.front() << std::endl;
std::cout << "Custom vector front: " << custom.front() << std::endl;
```
Išvestis (native): 1
Išvestis (custom): 1

### at()
```
std::vector<int> native;
Vector<int> custom;

std::cout << "Native vector at 2: " << native.at(2) << std::endl;
std::cout << "Custom vector at 2: " << custom.at(2) << std::endl << std::endl;
```
Išvestis (native): 3
Išvestis (custom): 3

### pop_back()
```
std::vector<int> native;
Vector<int> custom;

for (auto i : native)
    std::cout << i << " ";
std::cout << std::endl;

for (auto i : custom)
    std::cout << i << " ";
std::cout << std::endl << std::endl;

native.pop_back();
custom.pop_back();
custom.pop_back();

for (auto i : native)
    std::cout << i << " ";
std::cout << std::endl;

for (auto i : custom)
    std::cout << i << " ";
std::cout << std::endl << std::endl;
```
Išvestis: 

1 2 3 4 
1 2 3 4 

1 2 3
1 2

## push_back() greitaveikos palyginimas

| Elementų sk.         | 10'000   | 100'000  | 1'000'000 | 10'000'000 | 100'000'000 |
|----------------------|----------|----------|-----------|------------|-------------|
| std::vector (Native) | 0.000091 | 0.000668 | 0.007168  | 0.068054   | 0.496691    |
| Vector (Custom)      | 0.000076 | 0.000520 | 0.004227  | 0.048650   | 0.478698    |

## Atminties perskirstymo palyginimas

```
std::vector<int> native;
Vector<int> custom;

int countNative = 0;
int countCustom = 0;

for (int i = 1; i <= sz; ++i){
    if(native.size() == native.capacity())
        countNative++;
    
    native.push_back(i);
}

for (int i = 1; i <= sz; ++i){
    if(custom.size() == custom.capacity())
        countCustom++;
    
    custom.push_back(i);
}

std::cout << "Native vector reallocated: " << countNative << " times." << std::endl;
std::cout << "Custom vector reallocated: " << countCustom << " times." << std::endl << std::endl;
```
Išvestis:

Native vector reallocated 28 times.
Custom vector reallocated 28 times.

## Programos veikimo palyginimas

| Studentų sk.         | 100'000  | 1'000'000 | 10'000'000 |
|----------------------|----------|-----------|------------|
| std::vector (Native) | 0.528724 | 5.620732  | 55.70447   |
| Vector (Custom)      | 0.577765 | 5.707632  | 56.68246   |