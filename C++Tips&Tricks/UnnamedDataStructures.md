We all know  struct ,  class ,  enum  and other type defining items such as  using  and  typedef . All of them are used to give a data structure, or more commonly referred to as 'Type', a distinct name.
‎   ‎   But are types really required to have their own name?  Not necessarily!

‎   ‎   A common data structure might an object that holds two equal sub objects. I assume most most people might write something like this:
struct ObjectData {
    int   i;
    float f;
};
struct Object {
    ObjectData a, b;
};
‎   ‎   Or, when the underlying structure is not relevant:
struct Object {
    struct ObjectData {
        int   i;
        float f;
    };
    ObjectData a, b;
};

‎   ‎   In the case where  ObjectData  has no real meaning outside of defining only the members  a  and  b , naming it might seem a little bit redundant. And, in fact, can be left out:
struct Object {
    struct {     // unnamed struct
        int   i;
        float f;
    } a, b;
};

‎   ‎   All of the above shown structures are the same. We can, in all three cases, call  object.a.i  or any other member in the same fashion.

‎   ‎   Before I go on, there's another feature I'll elaborate upon that unnamed structures offer:
struct Object {
    struct {
        int   i;
        float f;
    };           // note wed don't name any variable;
};
‎   ‎   As seen here. When an unnamed structure is declared within another structure and is not used to declare a variable. It's members can accessed though the parent structure. What that means is basically this:
Object obj{};    // Of type 'Object'
obj.i;           // Here we can access 'i' as if it was defined in Object itself
‎
   ‎   So, looking at these features. What can we do with it?
‎   ‎   Take a look at the following point structure:
struct Point {
    union {                 // unnamed union
        float data[3];
        struct {            // unnamed struct
            float x, y, z;
        };
    };
};

‎   ‎   What's the unique thing about this?
‎   ‎   This structure allowed us to either write  point.data[0]  or  point.x  and both of those would give us the same number.
‎   ‎   It may be useful in a handful of ways. Having the convenience of simply using x, y and z in our code, or passing data to a function expecting a pointer to 3 floats. All of this without doing much fancy stuff.

‎   ‎   Another convenient way to use this is in a situation where you are dealing with a strange data structure. A place where it once helped me a lot was when reading an index buffer of a triangle strip. Let me show you:
void RenderStrip(std::vector<int> const& indeces)
{
    union Face {
        int const *pos;        // Pointer to the first index
        struct {
            int x, y, z;       // Structure to help me get index x, y, and z
        } const *const index;
    };

    int const *const begin{ data(indeces) };           // Begin of indeces
    int const *const end{ begin + size(indeces) - 3 }; // End   of indeces

    for (Face face{ begin }; face.pos < end; ++face.pos)         // Here we use 'face.pos' to go over the array
        RenderFace(face.index->x, face.index->y, face.index->z); // And 'face.index' to access the indeces.
}

‎   ‎   As you can see, it enables you to do a lot of things where, otherwise, you would write some very weird code. But now we can, in only a few lines, achieve something that would otherwise need a lot of indecipherable code.

‎   ‎   That was it for today and I hope this may help you in the future.
‎   ‎   And again. I'm always open to questions. Thank you and till next time! :)
