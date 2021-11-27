// Normal Syntax;

let i = 1;
loop (i, 15) {
    let mod3 = i;
    let mod5 = i;
    mod(mod3, 3);
    mod(mod5, 5);
    ifeq(mod3,0) 
    {
        ifeq(mod5, 0)
        {
            print(Fizzbuzz);
        }
        ifneq(mod5, 0)
        {
            print(Fizz);
        }
    }
    ifeq(mod5, 0)
    {
        ifneq(mod3, 0)
        {
            print(Buzz);
        }
    }
    ifneq(mod3, 0)
    {
        ifneq(mod5, 0)
        {
            print(i);
        }
    }
}

// Compressed Syntax. IDK why anyone would ever use this. Just here to show that the parser isn't super strict on syntax.;

let i=1;let mod3=0;let mod5=0;loop (i,15){mod3 = i;mod5 = i;mod(mod3,3);mod(mod5,5);ifeq(mod3,0){ifeq(mod5,0){print(Fizzbuzz)}ifneq(mod5,0){print(Fizz)}}ifeq(mod5,0){ifneq(mod3,0){print(Buzz)}}ifneq(mod3,0){ifneq(mod5,0){print(i)}}}
