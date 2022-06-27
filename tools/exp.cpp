#include <iostream>
#include <string>
#include <mutex>
#include <set>
#include <memory>
#include <string>
#include <utility>

struct Object {
  int fd;
  std::shared_ptr<std::mutex> mtx;
  std::shared_ptr<std::string> msg;
  Object(int _fd) {
    fd = _fd;
    mtx = std::make_shared<std::mutex>();
    msg = std::make_shared<std::string>();
  }
  bool operator<(const Object& obj)const {
    return fd < obj.fd;
  }
  bool operator==(const Object& obj)const {
    return fd == obj.fd;
  }
};

int main() {
  std::set<Object> objSet;
  objSet.emplace(Object(1));
  auto it = objSet.find(Object(1));
  auto p = it->msg;  // 这里获取指针，就可以直接操作了
  *p += "hello world !";
  std::cout << *(it->msg) << std::endl;
  return 0;
}
