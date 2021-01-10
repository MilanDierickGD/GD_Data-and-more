You most likely know what lambdas are and probably also used them form time to time. Using them as function arguments for algorithms is a very common thing. But that's not all they can do for you.
‎   ‎   Lambdas can also be used to avoid repeating the same code multiple times. Here I will explain more use cases and some more features lambdas offer you.

‎   ‎   Sometimes a piece of code is so small you don't want to make a whole sperate function for it, or you just want to keep the code in one place and don't litter it around. That's a fair point and lambdas can help you with this too:
void ModifyTriangle(Triangle& triangle)
{
    auto const modify =
        [](Vertex& vertex)
        {
            vertex.w *= exp(vertex.y) / sqrt(vertex.x) * log(vertex.z);  // this doesn't really matter, just imagine some weird line of code
        };

    modify(triangle.x);
    modify(triangle.y);
    modify(triangle.z); 
}
‎   ‎   Here we have some code that would be bothersome to copy three times. so we made a simple lambda and used that one three times instead. It makes the code a little bit simpler and easier to correct if our code is bugged.

‎   ‎   Lambdas also have this in their declaration: []. This is their capture clause.
‎   ‎   We can put a lot if thing in here, here's a couple of examples of what can be done:
auto const a = [var]  () { /*... var + 1 ...*/ }; // capture by value.
auto const b = [&var] () { /*... ++var   ...*/ }; // capture by reference.
auto const c = [=]    () { /*... var + 1 ...*/ }; // capture everything by value.      * (see footnote)
auto const d = [&]    () { /*... ++var   ...*/ }; // capture everything by reference.
auto const e = [this] () { /*... ++m_Var ...*/ }; // captures 'this' pointer; I.e. capture object by reference!
auto const f = [*this]() { /*...m_Var + 1...*/ }; // captures entire object by value!
‎   ‎   These are some common captures you probably know about. Do note the difference between captures by value and reference!
‎   ‎   Value        :  is copied! This copy cannot be modified!                      (Lambda may outlive the variables it copied)
‎   ‎   Reference:  is referenced! referenced variable can be modified!   (Lambda must not outlive the variables it references !!! )

‎   ‎   Whenever you capture  this  : You don't have to write  this->m_Var  out full. You may leave out  this->  and just use  m_Var. But this may lead to confusion! See the next paragraph:

‎   ‎   * There is one thing to note here. Concerning the  [=]  capture.
‎   ‎   This capture captures all variables by value, that includes this. But now take a look at what [this] does: It only copies the pointer and via that pointer you can modify the values of the class members.
‎   ‎   That is not what you would expect from "capture by value"! And on top of that. this may be destroyed before the lambda is destroyed, not good!
‎   ‎   As of C++20, the this capture will be explicitly excluded from [=] and an explicit capture [=, this] will be required. Or, the "capture by value" as it should be: [=, *this]. The latter actually copies it and thus is allowed to outlive the original object.
‎   ‎   Keep this in mind as it currently leads to confusion!

‎   ‎   As for  [&]  , nothing changes. It also captures this, but as a reference, being able to modify the original object is what you would expect :)

‎   ‎   This then was the first part of the lambdas features I'll be covering. I hope this refreshes your mind, gives you some ideas and forms a decent basis for what's still left to explain.

‎   ‎   Lambdas are one of the most sophisticated things in C++. So I'll be spreading it out a bit :) 
‎   ‎   More about lambda captures and their states tomorrow!


To see if you got it, try solving this:
//  What value will main() return?

int& Add(int      & i) { return i += 1; }
int  Add(int const& i) { return i +  1; }

struct Struct
{
    int m_Value;

    int Function() noexcept
    {
        auto const lambda = [=] { return Add(m_Value); };
        return lambda();
    }
};

int main()
{
    Struct object{ 7 };
    return object.Function() + object.m_Value;
}

I will post the solution tomorrow.
JL07/12/2020
The correct answer of yesterdays question is:   16     Don't know why? Take a look at what [=] does with this.  m_Value is not const and thus modified outside the lambda !!!

  ‎   Lambda expressions (cont)

‎   ‎   As we've seen in class today, Lambdas are function objects. For every lambda we write, the compiler actually constructs a class with some variables and the all important  operator().
‎   ‎   You probably already know about this; But Like I just said. Lambdas also have member variables. You already know part of this, it's the references and values I discussed yesterday. But we define anything really, Here I'll explain more.

auto const a = [i = 0, j = 0  ]       () { /* ... */ }; // a variable 'i' and 'j'. Both with value 0. Type is 'int'.
auto const b = [i = sqrt(var) ]       () { /* ... */ }; // We can also use functions. 'i' will be the root of 'var'.
auto const c = [obj = std::move(obj)] () { /* ... */ }; // We know about capture by value. But what if we can't 'copy' the object? We can 'move' it in as well!
auto const d = [&a, b, i = 0, j = /*...*/] (){/*...*/}; // We can combine any type of capture we want.

‎   ‎   There's one thing however. You cannot modify any of these inside the lambda. That is the default behaviour. But we can make it modifiable if we want to. The keyword for this is:  mutable 
auto a = [i = 0] () mutable { return ++i; };            // every time we call the lambda, we modify 'i'.
‎‎‎   ‎   mutable  allows you to change it's member variables, this includes all 'captures by value' as well. But the cost of this is that the lambda cannot be declared  const  any longer.

‎‎   ‎   Defining all kinds of captures isn't the only thing lambdas can do. They can also accept any kind of parameter type by making use of the auto keyword:
auto const a = [] (auto const& container) { return size(container) * sizeof(container[0]); };  // Gets you the size, in bytes, of any container you pass it
‎   ‎   As you can see this is very helpful in cases where you want to use some form of template function, but actually writing a template function would be too much work.
‎   ‎   A lambda like this easily solves this and allows you to make simple but versatile little functions.

‎   ‎   Now you might think. Why are you writing sizeof(vec[0])? The thing is that, while you can use any type, the template parameters can't be used. So that's why.
‎   ‎   But soon, as of C++20, templates will also be added to lambdas! It will look like to this:
auto const a = [] (auto const& i)  { return sizeof(i) * 8; }; // A simple example of calculating the size in bits of a type
auto const b = [] <typename T> (T) { return sizeof(T) * 8; }; // The same. A possibility as of C++20.
‎   ‎   I'm not going to say too much about this, but do know they're coming, should you ever see one.

‎   ‎   Finally. Lambdas, being a function, have a return type. Usually this is automatically determined by what you return. But you can also specify it yourself. Either to guard yourself from making a mistake or, in case of polymorphism for example, cast it to a different type.
auto const a = [] () -> std::pair<bool, int> { return { true, 7 }; }; // Now we can just return '{...}' without writing the type
‎   ‎   (Tomorrow i'll talk a bit more about this special way of defining a return type)

‎   ‎   As you can see. Lambdas have a lot of capabilities. It might be handy to know these so you are not writing some unnecessary code which will most likely be prone to bugs. So try a lambda next time :)

‎   ‎   I hope this may help you.

