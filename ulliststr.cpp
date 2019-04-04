#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"
#define ARRSIZE 10

ULListStr::ULListStr() {
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr(){
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::set(size_t loc, const std::string& val) {
  std::string* ptr = getValAtLoc(loc);
  if(NULL == ptr){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc) {
  std::string* ptr = getValAtLoc(loc);
  if(NULL == ptr){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(NULL == ptr){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear() {
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

void ULListStr::push_back(const std::string& val) {
  if (empty()) { //no items
    Item* it = new Item();
    head_ = it;
    tail_ = it;
    it->val[0] = val;
    it->last++;
  }
  else if (tail_->last == ARRSIZE) { //tail full
    Item* it = new Item();
    tail_->next = it;
    it->prev = tail_;
    tail_ = it;
    it->val[0] = val;
    it->last++;
  }
  else { //tail not full
    tail_->val[tail_->last] = val;
    tail_->last++;
  }
  size_++;
}

void ULListStr::pop_back() {
  if (size_ == 0) return; //list is empty
  if (size_ == 1) { //list has one element remaining
    delete tail_; 
    tail_ = NULL;
    head_ = NULL;
  }
  else if (tail_->last == 1) { //item has one element remaining
    tail_ = tail_->prev;
    delete tail_->next;
    tail_->next = NULL;
  }
  else { //item has multiple elements remaining
    tail_->last--;
  }
  size_--;
}
  
void ULListStr::push_front(const std::string& val) {
  if (empty()) { //no items
    Item* it = new Item();
    head_ = it;
    tail_ = it;
    it->val[0] = val;
    it->last++;
  }
  else if (head_->first == 0) { //head full
    Item* it = new Item();
    it->next = head_;
    head_->prev = it;
    head_ = it;
    it->val[ARRSIZE-1] = val;
    it->last = ARRSIZE;
    it->first = ARRSIZE-1;
  }
  else { //head not full
    head_->val[head_->first-1] = val;
    head_->first--;
  }
  size_++;
}

void ULListStr::pop_front() {
  if (size_ == 0) return; //list is empty
  if (size_ == 1) { //list has one element remaining
    Item* temp = head_;
    delete temp; 
    tail_ = NULL;
    head_ = NULL;
  }
  else if (head_->first == ARRSIZE-1) { //item has one element remaining
    head_ = head_->next;
    delete head_->prev;
    head_->prev = NULL;
  }
  else { //item has multiple elements remaining
    head_->first++;
  }
  size_--;
}

void ULListStr::appendContents(const ULListStr& other) {
  if (other.empty()) return;
  size_t loc_r = 0;
  size_t temp_c = other.head_->first;
  Item* temp = other.head_;
  while (loc_r < other.size_) {
    this->push_back(temp->val[temp_c]);
    loc_r++;
    temp_c++;
    if (temp_c == temp->last) {
      temp = temp->next;
      temp_c = 0;
    }
  }
}
  
std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last-1];
}

std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if (loc >= size_ || loc < 0) return NULL;
  size_t loc_r = 0;
  size_t temp_c = head_->first;
  Item* temp = head_;
  while (loc_r != loc) {
    loc_r++;
    temp_c++;
    if (temp_c == temp->last) {
      temp = temp->next;
      temp_c = 0;
    }
  }
  return &temp->val[temp_c];
}

ULListStr::ULListStr(const ULListStr& other) {
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
  this->appendContents(other);
}

ULListStr& ULListStr::operator=(const ULListStr& other) {
  this->clear();
  this->appendContents(other);
  return *this; 
}

ULListStr ULListStr::operator+(const ULListStr& other) const
{
  ULListStr A(*this);
  A.appendContents(other);
  return A;
}

ULListStr& ULListStr::operator-=(size_t num) {
  for (size_t i = 0; i < num; i++)
    this->pop_back();
  return *this;
}

std::string const & ULListStr::operator[](size_t loc) const
{
  return this->get(loc);
}

std::string & ULListStr::operator[](size_t loc) {
  return this->get(loc);
}
