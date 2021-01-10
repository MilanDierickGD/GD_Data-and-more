We all know  .begin()  and  .end(). They have a logical reason to exist! But we also know that Object oriented programming is... not always the best approach. And on top of that, not everything can be made to comply with object oriented design.
‎   ‎   That's why the functions like std::begin(...)  and  std::end  were introduced!

‎   ‎   example:
                                             //C++
std::sort(numbers.begin(), numbers.end());   //98  Only option before C++11
std::sort(begin(vector), end(vector));       //11  Recommended option as of C++11

int numbers[420]{};
//std::sort(numbers.begin(), numbers.end()); //    This is not possible
std::sort(begin(numbers), end(numbers));     //11  Now possible

‎   ‎   begin and end are provided by the standard library to functionally get the begin and end or a standard container.

‎   ‎   Every std container complies and raw arrays do too! It is usefull to keep your code in line with a functional or data oriented code design pattern.

‎   ‎   As you may or may not suspect, these are also available:
‎   ‎   Reverse iterators:             std::rbegin    std::rend     (Go from N to 0, backwards!)
‎   ‎   Const iterators:                std::cbegin     std::cend    (Enforce const!)
‎   ‎   Reverse Const iterators: std::crbegin  std::crend
‎   ‎
‎   ‎   But there's more useful stuff! Here are a couple of examples.

‎   ‎   Example:
size_t const vecSize = size(vector);        //17  returns the size of the container.
size_t const ArrSize = std::size(numbers);  //17  returns the size of a raw array.

auto it0 = cbegin(vector);                  //14  Gets begin iterator to non modifiable data.
advance(it0, 1);                            //98  Increments iterator by N.
auto it1 = next(it0);                       //11  Next accomplishes the same thing, but makes a copy instead
auto it5 = next(it0, 5);                    //11  Default is +1 but you can pick any number. Even negative numbers.
auto it5 = prev(it0);                       //11  But prev is also available!

size_t const steps = distance(it0, it5);    //98  Returns the distance from A to B, useful if you want to turn a find_if result into an index.
bool const isEmpty = empty(vector);         //17  Is empty?
object* pObjArray  = data(vector);          //17  Gets pointer to underlying object array.
object* pObj       = to_address(it0);       //20! Gets pointer to the object the iterator points to. Only as of C++20! For now using '&*it' should work
‎   ‎   Note: We don't always need to write  std::  because of the automatic scope resolution for standard containers and iterators.

‎   ‎   As you can see. These utilities may come in handy! Take a note of them and don't reinvent the wheel every time. It will make your code cleaner, more reliable and safe.
‎   ‎
‎   ‎   For more elaborate information, see the Functions section of this page: [https://en.cppreference.com/w/cpp/header/iterator]
