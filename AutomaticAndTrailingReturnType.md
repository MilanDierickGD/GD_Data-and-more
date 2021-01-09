When defining a function, we have to specify a return type. But there's also a way to let this happen automatically. And as you might guess,  auto  is the keyword to use here.

‎   ‎   Here's an example:
template <typename Container>
auto MiddleIterator(Container& container)
{
    return next(begin(container), size(container) / 2);     // Will end up with an iterator to the middle of the container
}
‎   ‎   Here's a rather simple example of an auto return type. Let's, for example, say we call this function with a vector if integers,  std::vector<int> . This will be the type of  Container . The function will do it's job calling  begin ,  size  and  next .
‎   ‎   It will eventually end up with an iterator to the container's middle element, which we return. The compiler spots this and assigns that type as return type to this function.

‎   ‎   Not only can this function handle a vector of integers, but any std container there is! Imagine what we would have to write if we couldn't use an automatically deduced type.

‎   ‎   An  auto  return type is also used for something else: Trailing return type. Take a look at the return type of our lambda yesterday, this is the same concept but for ordinary functions!
auto GetRand() -> int     // Equal to:  'int GetRand()'
{
    return rand();
}
‎   ‎   This is a simple example, here we just say the function returns an  int , but at the end rather than the beginning.
‎
‎   ‎   Now you may ask yourself, why is this a thing?
‎   ‎   At first it may not seem that useful over the ordinary way, apart from that it may sometimes be cleaner for template meta programming. The reason it's there is so that we can use the function arguments to form a type we need. I'll show an example:
template <typename Container>
auto MiddleIterator(Container& container) -> decltype(begin(container))  // decltype gives the type of it's arguments, in this case: the return type of 'begin(container)', an iterator.
{
    return next(begin(container), size(container) / 2);  // because we now defined our return type, we can be assured that a wrong type will not be returned, if we ever made a mistake.
}
‎   ‎   This is the same function as the top one, but now we do specify the return type more clearly, that is: "The type of what 'begin(container)' returns". This way we guard ourselves if we ever return the wrong thing that could potentially break our code.
‎   ‎   This method of defining our return type allowed us to use the variable container to call functions. Whereas before, we couldn't have used it apart from some black magic.
‎   ‎
‎   ‎   You probably won't be using this feature all too often. But if you ever encounter one in the wild, or was wondering how a lambda return works, I hope this post may answer those questions.

‎   ‎   If you have a remark, please let me know. I'm always looking for ways to make my posts more helpful and complementary to what people are seeking information about. Thank you.
