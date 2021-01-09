# Automatic scope resolution

*Most likely, you never thought about it but you can use a scoped  function/operator  outside of it's namespace without typing it out.
How?*

## Example:
```c++
namespace scoped
{
    struct Inside{};

    template<typename T>  // functions
    void function(T);

    template<typename T>  // operators
    T operator + (T);
}

struct Outside{};

void example()
{
    Outside o{};
    scoped::Inside i{};

    scoped::function(o);    // Ok
    scoped::function(i);    // Ok
    //function(o);          // Cannot resolve function
    function(i);            // Ok: Automatic scope resolution
    
    //+o;                   // Cannot resolve operator
    +i;                     // Ok
    scoped::operator+(o);   // Ok
}
```
Here,  function  is defined inside  namespace scoped 

When an object is used as a function parameter, the compiler also searches for matching functions inside its namespace scope

Where is this useful?
For example:  `begin(vector)`. It'd be a bit long to write `std::begin(vector)`. Because we are programmers and hate typing, this feature comes in handy!    (more about begin tomorrow!)

This also works for operators!
You probably didn't realize that, yet I'm sure you've been making use and have been relying on this feature all along!
