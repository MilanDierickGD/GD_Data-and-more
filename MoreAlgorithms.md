You have probably come across the task of modifying every element in a range, or taking a value out of every element in a range and calculating a grand total. For these common tasks, std is there for your!

‎   ‎   - Modify a range:
std::transform(
    begin(numbers), end(numbers), // range
    begin(numbers),               // destination (the same range in this case)
    [](float const a) { return a * a; } // a function or lambda
);
‎   ‎   When  numbers  is  1, 2, 3, 4, ... . This statement will transform it to  1, 4, 9, 16, ... .
‎   ‎   Here we modify the range itself, but the output can be a different range too. See next example:

‎   ‎   What if we wanted to transform based on two different values?  transform  supports this too:
std::transform(
    begin(numbers), end(numbers), // range 1
    begin(otherNumbers),          // range 2
    begin(moreNumbers),           // destination
    [](float const a, float const b) { return b / a; }
);  // Same principle, but now we use 2 values to calculate the result.
‎   ‎   Here we divide  numbers  by  otherNumbers  and put the result into  moreNumbers. Requirement is that range 2 and the destination range is at least as long as range 1.

‎‎   ‎   - Go through a range, perform an operation and take the result with you as you go:
std::accumulate(begin(numbers), end(numbers), 0)   // By default: 'total = total + value'. Imagine a "Sum(numbers)" function
std::accumulate(
     begin(numbers), end(numbers), // range
     std::string{ "range=" },      // initial total
     [](std::string total, int const value) { return total + char(value); } // type of total may be of a different type
); // Here we use our own operation. Same principle as above, but here we use 'string + char'
‎   ‎   If  numbers was to be 1, 2, 3, 4. We would end up with 10; I.e.  0+1+2+3+4 . and the next line would result in... a weird string, but you get the point.  ("range=����"  to be exact)

‎   ‎   In some languages, this is called reduce.
‎   ‎   Very important to note!!!  std::reduce  is not what you think it is!  It does have a similar behaviour, however, it passes through the ranges in an unspecified order to save time. That means that for non-commutative operations, notably 'a - b', behaviour is undefined!
‎   ‎   Anyway, I won't get into reduce with detail here...

‎   ‎   As you could see in our last  transform  example, we wrote a lambda to implement a division. But did we really have to do that?  No. We could have used this instead:
std::divide<float>{};   // std functor that has an operator()(T a, T b) that returns the division 'a/b'.
‎   ‎   No need to write our own. And of course the other default operations are available too:
std::plus       // addition
std::minus      // substraction
std::multiplies // multiplication
std::divides    // division
std::modulus    // remainder / modulo
std::negate     // negation (only requires 1 argument)
‎   ‎   There's some more as well, check out the functional header.

‎   ‎   I hope this was okay enough to understand and be helpful in the future. Fewer raw loops will make your code straight forward and ultimately easier to maintain.

‎   ‎   More info found here: [https://en.cppreference.com/w/cpp/algorithm/transform] [https://en.cppreference.com/w/cpp/algorithm/accumulate] [https://en.cppreference.com/w/cpp/header/functional #Function objects]
‎   ‎   There's also much more! I'll occasionally be covering them, but if really want more, I recommend this talk: [https://www.youtube.com/watch?v=2olsGf6JIkU]

‎   ‎   For any remarks or clarifications, don't hesitate to ask, whether I'd be me or anybody else.  :)
