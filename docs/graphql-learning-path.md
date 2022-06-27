# GraphQL learning path

A segmented story of my GraphQL learning path.

## The first interaction

The first GraphQL page getting [started link](https://graphql.org/learn) leads to the [learning page](https://graphql.org/learn/). I am learning GraphQL for the first time and feel lost. After reading the topics on the learning page, I wondered how to use GraphQL. What is this page trying to teach me? What part of the GraphQL is on this page? Are there more GraphQL tools? What GraphQL tool should I use? I had a lot of questions and no answers.

Time spent: ~2 hours.

## The second interaction

The learning problem analysis went something like this:

- GraphQL is a client-server tool.
- GraphQL client needs a GraphQL server.
- I can't use a client without a server, so I should start with the server.
- Does the GraphQL documentation offer a list of tools? They do, handy.
- Hmm, the GraphQL Apollo server should be a good start.
- Apollo server documentation looks good. I will be up and running soon.
- After the first page, I had a running GraphQL server.

Some things I tried:

- Modify a query.
- Add a variable.
- Read about caching.
- Mutations.
- ...

Time spent: 2 days

Day 1: ~1 hour.

Day 2: ~10 hours (breaks and other activities included).

Conclusions from the second round:

- Multi-language support for GraphQL.
- Multi-layer topic and relatively steep learning curve.
- Easy to get into but hard to master.

## The third interaction

The situation is getting heated. I want to use typescript, so I set up nodemon and ts-node. Five minutes in, and the typescript server runs. Fifteen minutes in, and I'm looking at the type declarations. A feature creep creeps in, and I want to use schema. The first feature creep was the typescript. The schema didn't work, and I'm reading the apollo documentation. Forty-five minutes in, nothing works. I'm wasting time. The javascript server was running, and I didn't need typescript or schema. Restored the setup to javascript and had the server running again. I made a promise to make a minimal viable product. Fighting the feature creeps continues.

I am trying to create a GQL schema for Apollo, doesn't work. Open the Apollo docs, but not much about the schema. TypeDefs and Resolvers are everywhere, but are they the way to go?

I open the GQL documentation to find out how to create a schema. No luck. Wait, that's weird. The docs for creating schema aren't the ones I used the first time. Hmm, why is there more than one documentation? What is their difference? I opened the old documentation, and it used the GraphQL express server. More than one documentation about the same thing. Are these docs about the same thing? They describe it differently, and I figured it out. The multi-layer thing:

- GraphQL schema.
- Resolvers.
- We can write schema in a file with the .gql extension.

Oh my god...

The only topic I have more problems with is C++. Yesterday I tried to figure out how does the C++ class inheritance work. Why is there the keyword public in front of the parent class? There are three class inheritance modes: private, protected, and public inheritance. The class inheritance is by default private, but they needed a public. It took me half an hour of research to figure it out.

## Closing words

I can comfortably write entry-level GraphQL apps. The experimental journey was fun. When I'm in the mood, I will look more at GraphQL. The concept feels exciting.
