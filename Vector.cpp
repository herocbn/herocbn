/*************************************************************************
    > File Name: Vector.cpp
    > Author: cbn
    > Mail: cbn@hust.edu.cn 
    > Created Time: 2022年07月06日 星期三 01时04分14秒
 ************************************************************************/

#include <iostream>
#include <algorithm>

class vector {
private:
    int _size; // 元素的个数
    int _capacity; // 容量
    double *_list; //指向 new 分配的资源
    enum {
        SPACE_CAPACITY = 4
    }; // 初始容量

    // 内存分配（分配器简化处理）
    //每次空间不够的时候,就重新获得2倍于当前容量的空间
    void resize(int newSize) {
      if (newSize > _capacity) {
        ReAllocate(newSize + 1);
      }
      _size = newSize;
    }

    // 重新分配空间
    void ReAllocate(int newCapacity) {
      // 新容量比当前 size 的小，则不进行操作
      if (newCapacity < _size) return;

      // 获取新的空间
      double *oldArray = _list;
      _list = new double[newCapacity];

      // 拷贝数据
      for (int k = 0; k < _size; k++) {
        _list[k] = oldArray[k];
      }
      _capacity = newCapacity;

      // 释放旧的数据
      delete[] oldArray;
    }

public:
    // 用 explicit 避免隐式类型转换
    explicit vector(int size = 0) : _size(size), _capacity(size + SPACE_CAPACITY) {
      _list = new double[_capacity];
    }

    // copy constructor
    vector(const vector &rhs) : _list(NULL) {
      operator=(rhs);
    }

    ~vector() {
      delete[] _list;
    }

    const vector &operator=(const vector &rhs) {
      // 如果是本身的话就不用再操作了
      if (this == &rhs) return *this;

      delete[] _list;
      _size = rhs.size();
      _capacity = rhs.capacity();

      _list = new double[capacity()];

      // 拷贝元素
      for (int k = 0; k < _size; k++) {
        _list[k] = rhs._list[k];
      }
    }

    // 输出
    friend std::ostream &operator<<(std::ostream &os, const vector &v) {
      for (int k = 0; k < v.size(); k++) {
        os << v[k] << " ";
      }

      return os;
    }

    // 输入
    friend std::istream &operator>>(std::istream &is, vector &v) {
      // TODO: 仍有改进的余地
      double num;
      is >> num;
      v.push_back(num);

//      std::string line;
//      std::getline(std::cin, line);
//      std::cout << "line: " << line << "/n";

      return is;
    }

    vector operator+(const vector &v) {
      const int size = std::max(this->size(), v.size());
      vector Z;
      int val = 0;
      for (int i = 0;i < size; i++) {
        val = (this -> _size >= i ? _list[i] : 0) + (v.size() >= i ? v[i] : 0);
        Z.push_back(val);
      }

      return Z;
    }

    vector operator-(const vector &v) {
      const int size = std::max(this->size(), v.size());
      vector Z;
      int val = 0;
      for (int i = 0;i < size; i++) {
        val = (this -> _size >= i ? _list[i] : 0) - (v.size() >= i ? v[i] : 0);
        Z.push_back(val);
      }

      return Z;
    }

    vector operator*(const vector &v) {
      const int size = std::max(this->size(), v.size());
      vector Z;
      int val = 0;
      for (int i = 0;i < size; i++) {
        val = (this -> _size >= i ? _list[i] : 0) * (v.size() >= i ? v[i] : 0);
        Z.push_back(val);
      }

      return Z;
    }

    vector operator/(const vector &v) {
      const int size = std::max(this->size(), v.size());
      vector Z;
      double val = 0;
      for (int i = 0;i < size; i++) {
        val = (this -> _size >= i ? _list[i] : 0) / (v.size() >= i ? v[i] : 0);
        Z.push_back(val);
      }

      return Z;
    }


    // 在数组的最后添加一个数据
    void push_back(const double &x) {
      if (_size == _capacity) {
        resize(_size + 1);
      }

      _list[_size++] = x;
    }

    void pop_back() {
      _size -= 1;
    }

    // 属性接口
    int size() const { return _size; }

    int capacity() const { return _capacity; }

    bool empty() const { return size() == 0; }

    const int &back() const { return _list[_size - 1]; }

    // 通过 [] 操作符访问属性
    double &operator[](int index) { return _list[index]; }

    const double &operator[](int index) const { return _list[index]; }

};


int main(int argc, char *argv[]) {
  const int columns = 4;

  vector X;
  std::cout << "请输入向量 X 的数值(空格分隔):" << std::endl;
  for (int i = 0;i < columns; i++) {
      std::cin >> X;
  }
  std::cout << "X: " << X << '\n';
  std::cout << '\n';

  std::cout << "请输入向量 Y 的数值(空格分隔):" << std::endl;
  vector Y;
  for (int i = 0;i < columns; i++) {
    std::cin >> Y;
  }
  std::cout << "Y: " << Y << '\n';
  std::cout << '\n';

  vector Z = X + Y;
  std::cout << "X + Y: " << Z << '\n';

  vector A = X - Y;
  std::cout << "X - Y: " << A << '\n';

  vector B = X * Y;
  std::cout << "X * Y: " << B << '\n';

  vector C = X / Y;
  std::cout << "X / Y: " << C << '\n';

  return 0;
}
