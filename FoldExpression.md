Yesterday I discussed variadic templates. But what are parameter packs without things that expand them? Today's topic will be fold expressions!

‎   ‎   Let me show you a simple but powerful example and will hopefully illustrate the point:
template <typename ... Values>
auto Sum(Values const& ... values)
{
    return ( ... + values );   // Fold expression
}
‎   ‎   So what is happening here?
‎   ‎   A fold expression will unfold a parameter pack and place the given operator between the parameters. So what this happens is this:
(... + pack) // will form  vvv                                                                                               If pack is:  1, 2, 3, 4, 5
((( param_1 + param_2 ) + param_3 ) + ... )    // Wrapped in parenthesis to guarantee order of operations                    (((( 1 + 2 ) + 3 ) + 4 ) + 5 )
‎   ‎   And as you may suspect. This is not limited to +. We can use any operator we like!

‎   ‎   There's also a couple of different ways to do a fold expression. Here are a couple of them:
( pack + ... )            // Same as before but reversed order:                        ( ... + ( Pn-2 + ( Pn-1 + Pn  ))      ( 1 + ( 2 + ( 3 + ( 4 + 5 ))))
( value + ... + pack )    // Same as before but with an initial value place up front:  ((( value + P1 ) + P2 ) + ...  )      ((((( X + 1 ) + 2 ) + 3 ) + 4 ) + 5 )
( pack + ... + value )    // Same but, again, reversed order:                          ( ... + ( Pn-1 + ( Pn + value ))      ( 1 + ( 2 + ( 3 + ( 4 + ( 5 + X )))))
‎   ‎   What which one does might confuse you so when in doubt, look it up.

‎   ‎   A nice way to show what we can do would be this useful function:
template <typename ... Values>
void Print(Values const& ... values)
{
    (std::cout << ... << values);   // Expands to:  (((std::cout << val_1) << val_2) << val_3) << ...
}
‎   ‎   Pretty nice, isn't it? :)
‎
‎   ‎   As I also explained yesterday, we can first call a function or do an operation before expanding the parameter pack. If we combine this with the fold expression, we can do even more useful things:
template <typename Type, typename ... Rest>
bool AnyOf(Type const& value, Rest const& ... others)
{
    return ( ... || (value == others) );   // Here we compare each 'others' value to our first 'value'. With the || operator we check if any is true. An any_of like algorithm!
}

‎   ‎   These were only two examples. But I ensure you that much more is very well possible!

‎   ‎   But there's more! A lambda can also have a parameter pack. This gives us the potential to write even shorter functions:‎
auto const sum  = [] (auto const& ... vals) { return (... + vals); };                   // Same as the very first example. But now just one, easy to read, line!
auto const avg  = [] (auto const& ... vals) { return (... + vals) / sizeof...(vals); }; // Calculate the avarage
auto const psum = [] (auto const& ... vals) { return 1 / (... + (1 / vals); };          // Calculate parallel sum

‎   ‎   I hope this feature may help to write some nice code that helps you avoid repetitive code. I actually use it from time to time as it offers some nice solutions with only a few lines of code.
‎   ‎   Till next time :)

‎   ‎   More information found here: [https://en.cppreference.com/w/cpp/language/fold]
