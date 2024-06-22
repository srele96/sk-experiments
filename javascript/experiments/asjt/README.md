# ASJT - A Stupid Javascript Tool

'A Stupid Javascript Tool' built using webpack. It implements tenant overriding in a weird way.

## References

- https://medium.com/@prateekbh/my-experience-writing-a-webpacks-child-compiler-plugin-a1237c175947
- https://github.com/webpack-contrib/terser-webpack-plugin/blob/master/src/index.js#L157
- https://github.com/webpack/webpack/blob/main/lib/DefinePlugin.js#L423
- https://github.com/webpack/webpack/blob/main/lib/node/CommonJsChunkLoadingPlugin.js
- https://github.com/uber/stylist/blob/master/sample/library/src/main/java/com/uber/stylist/mylibrary/MyUtils.java

## How does this help me?

By working through unfamiliar concept, making brain cell connections on how to make the implementation work. Learning new ideas that help us implement tenant overriding using webpack plugin. Working through thouse will help me feel familiar the next time I see similar thing. Even if the tenant overriding is in the bigger project, I might feel _"Oh, I've seen that already. It's just much bigger here. Now it's all about solving a problem. Not about learning the concept"._

By working through as many topics that cause _confusion_ and _questions_ we improve our knowledge. That knowledge can be transfered to working on bigger projects. Big projects are made up of many small ideas. A house of cards is made of many individual cards, but put together it's a house. A large project might implement the tenant overriding system differently. However the tenant, the plugins, the building blocks might be similar. The next time I have to edit the code on tenant overriding system, I will have easier time understanding it. I already have experience and some familiar ideas on how I did that. Tackling new problems is much easier if we have some ideas of similar situations before. Recognition is what allows us to solve unfamiliar problems.

What does it mean to understand? A flower is red. A flower has petals. A flower has a nice smell. A flower grows in the fields. A garden of flowers. Each of us has just now thought of a flower. Someone may have thought about a light shade of red. Someone else might have thought about a dark shade of red. Each of us has thought of a different mental image of a shade of red, a flower petal, smell, field, and garden. Maybe if two of us have been at the same garden have just now thought of the same garden. What does it mean to understand? I would define it as mental maping of the _thing_ we hear to a mental image stored in our permanent memory. Now if I say _a bug under the bed in my room_ only I understand what bug I am talking about. You can imagine the description of that bug, but if you are lucky you might get close or even guess what kind of bug it is. How do we obtain memories? Through the things we do, we have to be immersed in them. Ever had a car crash? A first time kiss? Overflowing of sensations has made our being to retain those memories. The more sensations, the more colorful is our understanding. In the same way, the more sensations we feel during implementation of tenant overriding for example, in many different ways, the more memories we obtain. Now the next time I see a code that implements it, I will recognize that code in a blink of an eye. A pattern recognition! I could not have read the chunk of 50 lines of code in 1 second. It's thanks to the memory! Let's define understanding as being able to describe a certain topic colorfully using different terms. To obtain a real understanding of certain programming topic, such as in this sample tenant overriding problem, the solution, webpack concepts that allow us to make it work, we need to be able to map many different ideas to it. Experiences. Now, with that out of the way, below is the description of the topics this GitHub repository covers.

### Building ideas is like a maze

I don't know where I am and I don't know how far the exit is. I am experimenting, trying out various ideas.

- Is it working?
- Should I try another one?
- Should I expand on the current one?
- How far should I backtrack to explore another path?
- Should I build one of the previous paths to my current state?

Even being unsure on what I'm trying to achieve reduces the change of success. What if I don't know how the exit looks like? What if an exit is a rock and I'm looking for a door. The rock is supposed to open a door for me. But I keep looking for a door. There are no doors. I spend months looking for a door, and then it hits me. How does the exit look like? I never thought abuot that. Such an idea occured to me while looking for a way to modify the source code of a module. I've read somewhere that `buildModule` hook can access the code. The `_source` was empty. My modules have code in them. A day later: "Wait a minute, what if the `buildModule` is not supposed to have a code? What if it's a little later stage of module build up?". That answered my question.

## ChatGPT gives as good answer as good question

I have noticed something strange. As I need some funtionality within nvim for example, search within a file, clear search term, edit search term, go to line, etc, ChatGPT gave me the correct answers. I asked ChatGPT to give me a code to insert the code into the module and I believe he gave me similar code to dependencyFactories, dependecyTemplates, parser hook, .addDependency, etc... If he gives me a really good approximations of the solution to the problems that I list, why is it that those approximations do not work?

Perhaps I should not be looking for alternative solutions, but rather an understanding of why the solution isn't working, then patch up the solution and continue researching how do I continue to build up code from there on... Why does it not always work in that case? I don't understand much of how webpack works so naturally the code won't work most of the time... All of it hints that I do not understand problem well enough to specify it well enough to the ChatGPT with enough details so the ChatGPT can dump a solution that's very close to what I need. A vague question can only receive a vague answer.

## The problem has been reshaping as I was learning

I had to adjust my thinking process. Initial idea was to replace a `require('./src/mod')` by `` import(`./src/tenant/${tenant}/mod`).then( /* ... */ ) ``. Once I managed to inject such code into a desired module, a new set of problems occured.

- How do I hand over a control to the user?
- How does user receive a module?
- I replaced his whole import...
- That means I have to parse his code to retrieve his function...
- And more stuff I haven't explored
- The import that I have injected isn't bundled by webpack

OH. MY. GOD. The more I learned, the less I knew. Every new question had opened even more doors for exploration than I previously had. It felt like a queue where questions were arising at higher frequency than I had been answering them. On top of it all, I don't understand how webpack internals are working. All of the concepts were challening.

- AST parsing.
- Code replacing.
- Dependency Templates.
- Dependency Factories.
- Plugins.
- Webpack code.

Webpack code isn't straightforward to read because it's asynchronous. It's using callbacks heavily and I'm not used to that. I haven't read much asynchronous code in the past. A lot of the concepts were unfamiliar and consistently it felt like my thoughts were at 100% capacity. There was no way I could hold in all that information on my mind all at once.

### Where in all of it is the benefit I promised?

Firstly, solving hard problems that take 100% or more of mental capacity is **ALWAYS GOOD**. Especially exercising with technologies I have never seen before. It taught me the versatility of thinking when I'm facing something I've never seen before. Once again I have an oportunity to explore, unlike when everything is familiar. It felt like I was in the dark all the time as I was looking for a new direction. I was building a brick wall and all I could see was the wall that I had already built and one brick that's in my hand. Where do I put the brick?

For example I inherited from the class that made `moduleGraph.getModule(dep)` always return `undefined`. Why does it return undefined? I don't know. Guess I'll read webpack code. That didn't help. I started to look for differences between my code and webpack code. I noticed that webpack `ImportDependency` class inherited `ModuleDependency` while I inherited `Dependency`. I checked the two respective classes and realized `Dependency` is bloody empty. It was an abstract class. Inheriting from it required us to override the methods. If JavaScript was a proper programming language maybe I wouldn't have spent a few hours researching why it's not working. A bloody compiler would throw an error, `Yo, you forgot to override abstract methods, dummy!`.

It required me to use all of the knowledge that I already had, expand on it, develop new ideas, apply them, and so on...

## Debugging session

After debugging why `moduleGraph.getModule(dep)` won't return dependency I found out a few things:

- `moduleGraph.setResolvedModule(originModule, dependency, module)` never gets called with my custom dependency
- Since above mentioned method never gets called, `mgm._unassignedConnections` equals to an empty array `[]`
- Since the `_unassignedConnections` is an empty array, the connection never gets returned.
- The question is, why does the blody moduleGraph never set the `originModule`, `dependency`, and `module`.

Anyway, some rambling might help me understand the problematic somewhat better:

It has been I don't know how long since I started working on this project. I wanted to write a plugin that enables me to do tenant overriding. However as I am working on it I learned a few things. Consistency is FUCKING AWESOME. Why?

Thanks to consistency I have managed to discover many awesome aspects of webpack, it's plugin ecosystem, understand how to understand the big code base that I've never seen before. I have learned a few more `NVIM` functionalities too. I learned how to search with nvim. I learned to edit webpack code in `node_modules` through another editor `vscode` and rerun webpack compilation to debug values of webpack internal state. I have learned how rapidly I am learning because I am handling a big difficult problem at hand. I realized how difficult and awesome what I am doing is. If I kept doing it for a few months, digging for new features that I want to add to a plugin and dig through webpack code base, I would learn a lot of it.

How does it help me in general? If I wanted to learn a book, I would simply take a book, in the same way, take parts of the book, use online resources, and build stuff using the information from the book. For example I have book on mathematical proofs, linear algebra, trigonometry, calculus, algebra, and more. I can take one book, dissect it, understand it's content, play with the stuff that I don't understand. Figure out how to build new stuff using the concepts from the book. When I feel I am done with the book, I can start consuming another book and build more stuff using the stuff from the other book. All of that is awesome. So god damn awesome. I don't know what happened, but I have unlocked a side of me that I've never seen before. A consistent side to stick with one problem for a long period of time.

## Documentation

A brief explanation of how everything fits together.

### How to run

Build for all tenants:

```terminal
yarn build-all
```

Run builds built with loader and plugin:

```terminal
yarn run-all
```

Run builds built with loader:

```terminal
yarn run-all-loader
```

Run builds built with plugin:

```terminal
yarn run-all-plugin
```

### Tenant overriding

1. Declare the tenant for which the bundle is being built using cross-env.
2. The webpack configuration picks up the tenant that we're building for.
3. Any file that contains `tenant` directory next to it is potentially replaceable.
4. The tool produces a dedicated build for each tenant.

### How does it work?

Two configurations. Loader and Plugin applied to each one respectively. Each configuration builds for given tenants. Each configuration builds in respective folder within output directory.

Two major differences: Plugin resolves overriding at build time. Loader resolves overriding at runtime.

#### Common idea

Create `tenant` folder next to files we wish to override. Create `tenant/one` for tenant named `one`. Give the files the same name.

```txt
mod.js
tenant/one/mod.js
tenant/two/mod.js
tenant/three/mod.js
```

The file `mod.js` is a subject for tenant overriding. There are 4 tenants: default, one, two, three.

#### Plugin

**Resolves tenant at build time.**

Plugin works on regular `require` statement. If required file has tenant directory next to it, check if tenant directory contains the tenant we build for, and point to the same file in the tenant directory.

#### Loader

**Resolves tenant at runtime.**

Loader is more sophisticated and works only on entry file because I didn't want to spend more time figuring out all the cases exactly because it's more sophisticated. It parses the code of every file. Check if there is a variable with specific name and expect a configuration object to be assigned to it. The configuration object contains path to the file we want to import. The loader injects the code to dynamically load the file.

The final bundle is capable of changing the tenant at runtime.
