Today I will elaborate a bit more on uncommon operators. Ones that you might encounter and make you wonder. What does this do?

‎   ‎   Here I will discus the following operators:  +  ~  ?:  , 


‎   ‎   First up: +
‎   ‎   You probably know about -var. it's as simple as saying -1 * var, it negates the value. This works for all fundamental types (char, int, float, ...) and it can also be overloaded for other types.
‎   ‎   But did you know +var also exists? But what does it do? Well, mathematically, ... nothing.  This operator has been added to complement the - operator. Some people might see a use for it and that's why it has been added, it can thus be overloaded if you wish to!
‎   ‎   Are there any built in uses for this operator? Yes!
auto const lambda = [] (int value) { return value * value; };     // Simple lambda, a square as an example
auto const functionPointer = +lambda;                             // operator+  will return the raw function pointer to the lambda's internal function
‎   ‎   When calling + on a lambda, we'll get a function pointer to the internal function. Most likely you won't be needing this, but if you ever see this. This is what it does!

‎   ‎   Next up: ~
‎   ‎   This operator is a bitwise operator. You probably know what !var does, it will flip the variable from 0 to 1 and vice versa. ~ does the same thing, but for all bits.
~'\xF0';   // a character '11110000' will be transformed to '00001111'
~0xF00F;   // an integer '1111000000001111' will be transformed to '0000111111110000'
~0ull;     // a ull '0' will be transformed to '18446744073709551615'. This is probably the fastest way to get the maximum integral value :)
‎   ‎   As you can see. It's a bitwise_not operation. And that, logically, is only possible for integral types (char, int, ...).  But if you want to, this operator is also overloadable for other types.
‎
‎   ‎   Now:   ? : 
‎   ‎   Most of you probably know this one. but for those who don't, let me explain:
int val{};
if (test) val = 13;
else      val = 7 ;
‎   ‎   Here we can see a conditional value being set to  val . But there's a couple of things that aren't very great with this approach.
‎   ‎   Not imediatly initialising a variable causes the code to be slower and it also makes to code longer. So is there anything we could do to make it better? Yes, here we have  ?: :
int const val{ test ? 13 : 7 };
   ‎   test ? true : false  is like a compact if statement! It allows is to properly initialise  val  and even set it const: win-win situation. And it's even shorter :)
   ‎   This works for any type, as long as the test returns a boolean, and the true/false result are of the same type.


‎   ‎   The (in?)famous:  ,
‎   ‎   This one may make you wonder. What is this thing? Even for me it took a long time before I figured out it even was a thing. So here I'll save you the hassle of looking it up.
‎   ‎   The comma operator is used in the following manner:
‎   ‎
‎   ‎   Imagine we have this:
statement 1;
statement 2;
‎   ‎   We can write is like this too:
statement 1, statement 2;
‎   ‎   What's the difference. At first, nothing special. Both statements are executed in normal order. To illustrate the point of , a bit better:
int val = (print("hello"), 13);
‎   ‎   What the , does is execute both statements, But it only returns the result of the second statement.
‎   ‎   First, print is executed and "hello" is printed, this function might return something, but it is disregarded.
‎   ‎   Secondly, 13 is executed (that is, nothing) and returns (guess what) 13.
‎   ‎   The comma operator thus returns the latter (13). so the int  val is set to 13.
‎   ‎   So what we did was squeeze a debug print statement into a line where, without the ,, it would never fit in.
‎   ‎   Another place where the comma operator finds use is in fold expressions or for loops:
[](auto ... args)
{
    (..., print(args));               // Will form:   print(arg_1), print(arg_2), ...    Which is pretty much equal to:    print(arg_1); print(arg_2); ...
};
for (int i, j; i * j < N; ++i, ++j)   // here we can put ++i and ++j into the same statement because of the ',' operator. Pretty handy if you have 2 incrementing values in a single loop.
‎   ‎   Since the , acts like a ; . we can use it to execute multiple statements in place where we can normally put only a single statement.
‎   ‎   One more note:  the comma operator has the lowest precedence of all operators.


‎   ‎   I hope this post was helpful and next time you see these operators you'll know what they are :)

‎   ‎   More information found here: [https://en.cppreference.com/w/cpp/language/operator_precedence]
‎   ‎   It shows all operators and their relative precedence.
