# Return Semantics

I was curious how does C++ handle function return values. Does it copy, move, or do I need to make proper decision based on my use case.

## Conclusion

I guess the most suitable answer is that I need to handle them based on my use case. It feels like **too much** how many variants there are. For example, sometimes it calls constructor when return value is `return Foo{}`, but when I create, modify and return that value, it moves it. I guess it makes sense because. It seems that rule of six is there because of this.

Therefore I guess that if I want to write good C++ program I would need to setup linter and strict flags to warn me about missusing features of C++ and shooting myself in the leg.
