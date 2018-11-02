# GRPTemplate

C++ Template By GRP.<br>

## 1.GRPStack<br>
```cpp
class GRPStack<T>;
```
```cpp
GRPStack<T>();//create a new stack
void push(); //push a data into the stack
T top();//get the top data
T pop();//pop the top data
bool empty();//if the stack is empty, return true
void clear();//clear the stack
size_t size();//return the stack size
```

## 2.GRPQueue<br>
```cpp
class GRPQueue<T>;
```
```cpp
GRPQueue<T>();//create a new queue
void push(T input);//push a data into the queue
T pop();//pop the head data of the queue
T front();//get the head data
T back();//get the last data
size_t size();//get the size of the queue
bool empty();//if the queue is empty, return true
void clear();//clear the queue
```

## 3.GRPSinNode<br>
```cpp
class GRPSinNode<T>;//single linked list Node
```
```cpp
GRPSinNode<T>(T, *GRPSinNode<T>);//can be invoked by 0/1/2 parameter(s)
```

## 4.GRPDouNode<br>
```cpp
class GRPDouNode<T>;//double linked list Node
```
```cpp
GRPDouNode<T>(T, *GRPDouNode<T>, *GRPDouNode<T>);//can be invoked by 0/1/2/3 parameter(s)
```

## 5.GRPGenList<br>
```cpp
class GRPGenList<T>;//GenList
//广义表的数据结构，代码主要来自于《数据结构 C++面向对象的编程》一书所给出的代码，书上代码中存在隐含BUG，目前已经修复了已知的部分
```
```cpp
//由于该数据结构非常的庞大，故不列出所有的可用外部接口
class GRPGenListItem;//作为返回节点数据的类型
class GRPGenListNode;//作为广义表节点的类型
class GRPGenList;//广义表的模板类
bool head(GRPGenListItem<T> &x);//返回头元素
bool tail(GRPGenList<T> &it);//返回广义表的尾，一定是一个广义表
int length();//返回广义表的长度，此时其实会调用一个private的同名函数进行递归求值
int depth();返回广义表的深度，也会调用一个private的同名函数进行递归求值

void createlist(istream &input, GRPGenListNode<T> *&x);//这是书上给出的构造函数，但是由于其重载了操作符<<，所以采用了输入流的实践，后续我曾采用GRPVector进行代替，并且在其中发现了一处由DSOJ触发的BUG
void remove(GRPGenListNode<T> *it);//删除该节点以及后续的广义表
```

## 6.GRPBinTree<br>

### To be continue.
