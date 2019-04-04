#ifndef ULLISTSTR_H
#define ULLISTSTR_H
#include <string>
#define ARRSIZE 10

class ULListStr {
 public:
  struct Item {
    std::string val[ARRSIZE];
    size_t first, last;
    Item *prev;
    Item *next;

    Item(){
      first = last = 0;
      prev = next = NULL;
    }
  };

  ULListStr();
  ~ULListStr();
  size_t size() const;
  bool empty() const;
  void push_back(const std::string& val);
  void pop_back();
  void push_front(const std::string& val);
  void pop_front();
  std::string const & back() const;
  std::string const & front() const;
  void set(size_t pos, const std::string& val);
  std::string& get(size_t pos);
  std::string const & get(size_t pos) const;
  void clear();
  ULListStr (const ULListStr& other);
  ULListStr& operator= (const ULListStr& other);
  ULListStr operator+ (const ULListStr& other) const;
  ULListStr& operator-= (size_t num);
  std::string const & operator[] (size_t loc) const;
  std::string & operator[] (size_t loc);

 private:
  void appendContents(const ULListStr& other);
  std::string* getValAtLoc(size_t loc) const;
  Item* head_;
  Item* tail_;
  size_t size_;
};
#endif
