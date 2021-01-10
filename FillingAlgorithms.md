### Filling algorithms

Sometimes, A lot of our time is taken up by figuring out a way to do a certain task. And occasionally, these are: modifying a range in some way or another. Luckily there are some useful algorithms provided by the standard library!

##
Small note: *A 'Range' refers to the set of values in between the first and last iterator we use. Usually it'll be the whole container, but that is not always the case!*

For illustrative purposes, I'll be using this array in my examples. These algorithms are not exclusive to `int` or `array` but this makes it easy to understand.
```c++
std::array<int, 100> numbers{};
```

## Fill
Fill range with the same value:
```c++
std::fill(begin(numbers), end(numbers), 13);
```

## Generate
Fill a range with a value returned by a function, lambda, functor, etc...
```c++
std::generate(begin(numbers), end(numbers), rand);  // A function, rand() in this case.  I.e fill the range with random values.
std::generate(
     begin(numbers), end(numbers),
     [i = 0] () mutable { return ++i; }
);                                                  // A lambda.  Here it increments 'i' with every call. Range will end up being: 1, 2, 3, 4, ..., N 
```

## Iota
You see how we tried to make 1, 2, 3, 4, ...? There's an algorithm for that!
```c++
std::iota(begin(numbers), end(numbers), 1);         // Fill range with incremented values. Here 1 is our first value, but can be anything. Result: 1, 2, 3, 4, ..., N
```
As you can see, and I repeat. Don't reinvent the wheel. :)     (Note: iota resides inside <numeric>)

##
I hope these functions can help you to easily construct a range of values without trying, possibly failing, to make your own raw loops. They, again, make your code robust and more reliable!
