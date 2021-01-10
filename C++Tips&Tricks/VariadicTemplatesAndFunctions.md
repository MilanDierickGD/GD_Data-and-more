You are probably familiar with the problem of being limited by how many parameters a function can take. And for every different set of arguments, a new one has to be defined.
‎   ‎   This problem is solved by variadic templates!
‎   ‎
‎   ‎   Where might you need a variable amount of arguments? It could be a  Sum  function, or  Max  function....  Here's a simple example:
template<typename ... Args>           //  A variable amount of arguments, packed under the name 'Args'
auto MakeArray(Args const& ... args)  //  '...' expansion is put inbetween the type and name
{
    return std::array{ args... };     //  To unpack 'args' we secceed it with '...'    (spaces don't matter)
}      //  Small note: Element type and size of array can automatically be deduced by the compiler  (As of C++17)
‎   ‎   Here I showed a simple example of how basic variadic templates are defined and used. Nothing special going on besides us making a simple array.
‎   ‎   But iff you were wondering:  args...  will be expanded to  args_1, arg_2, arg_3, ... .

   ‎   One thing though, is that we can't really use Args as a type to name a variable. So if we want some more type information, (or when we are working with C++14), We can expand our template with what we need:
template<typename Type, typename ... Rest>                //  We add one parameter at the front
auto MakeVector(Type const& first, Rest const& ... rest)  //  Which we use as our first argument type
{
    return std::vector<Type>{ first, rest... };           //  So now we explicitly define the type of our vector to be the type of our first given argument
}

   ‎
‎   ‎   The above shown functions can be used as follows:
auto arr  = MakeArray(1, 2, 3, 4, 5);          // Our first example
auto vecL = MakeVector(1.0, 2.f, 3);           // Here the first argument is a double
auto vecF = MakeVector<float>(1e6, .2f, 3.l);  // Or we can be a bit more explicit.

‎   ‎   One thing you might notice is an implicit cast warning, such as 'double to float' or something. So to solve this, we might want to modify our arguments first before we pass it along. We can do this:
/* ... */ static_cast<Type>(pack) ... /* ... */   // Here we first pass the pack to static_cast, and afterwards we exapand it.
/* ... */ (pack + 1) ... /* ... */                // Here we add 1 to every argument
/* ... */ sqrt(pack) ... /* ... */                // Here we call a function for every argument
‎   ‎   Long story short, you can do whatever you want: Put the expansion at the end and you're good!

‎   ‎   The examples I have shown so far might not seem that useful. That may be true, the thing is it becomes much more useful when paired with other features, such as recursive functions! Here they make a lot more sense and they can be damn useful.
‎   ‎   Tomorrow I'll show a different feature that combines with this and allow you to do even more things.

‎   ‎   Here's an example of a function I use a lot of times:  Max
template<typename Common>
auto Max(Common const& first, Common const& second)
{
    return std::max(first, second);
}

template<typename Common, typename ... Rest>
auto Max(Common const& first, Common const& second, Rest const& ... rest)
{
    return Max( std::max(first, second), rest ... );
}
‎   ‎   With this relatively simple function we can calculate the maximum value of a set of values we enter. Very useful in quite a few situations, now we don't have to worry about the amount of numbers we pass in.
‎   ‎   We rely on the bottom function for the most part as is continuously calls itself, but every time it does so, it has one argument less. So eventually we end up with our base case of 2 arguments which will call the upper function and end the recurse.
‎   ‎
‎   ‎   These parameter packs can be used to call all sorts of functions. We could use them to construct a vector or make a simple, useful and recursive algorithm. But much more as well! Play around a bit and you'll see what it's capable of.

‎   ‎   One more thing I'll explain is how to get the size of the pack. Perhaps unsurprisingly, this can be done using: sizeof 
sizeof...(pack)   // Gives you the count of parameters
‎   ‎   But do not confuse it with this:
sizeof(pack)...   // Expands to:   sizeof(param1), sizeof(param2), sizeof(param3), ...
sizeof(pack)      // Error: you must use 'sizeof...'

‎   ‎   Tomorrow I'll present some more capabilities of variadic templates and what you can do with them. I promise you, the most simple and elegant Sum() function!  :)

‎   ‎   More information found here: [https://en.cppreference.com/w/cpp/language/parameter_pack]
