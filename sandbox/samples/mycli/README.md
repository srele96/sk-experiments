# mycli

The program `mycli` is a useless cli program!!! Kankenai!!!

## Self-Reflection

Top Gun training questionaire.

### What happened

I decided to write command line interface application to fight off the habit that I developed over the past year and half. I get boggled down into details where I feel I need to understand every single detail about every single line of code in my program.

```cpp
  namespace po = boost::program_options;
  po::options_description desc("Allowed options");
  desc.add_options()("help, h", "Help me to use `mycli`!")
      // TODO: Learn the pattern to construct<type>()
      ("file, f", po::value<std::string>(),
       "Do stuff with a file on this path.");
```

This line of code triggers me to ask:

- Why `namespace po = ...`
- Why `po::options_description`
- What does `po::options_description` do?
- Is it right to call `po::options_description` at that time?
- Is there a better place to call `po::options_description`?
- What is `desc`?
- What is `desc.add_options()`?
- Why do I call `desc.add_options()`?
- Why can I call `desc.add_options()` with `()` repeatedly?
- How else can I use `desc.add_options()`?
- And the list goes on... forever and ever...

I had been honing this habit and it led me to discovery of many things. I learned a way to learn new things. I believe I went deep into topics I never would have otherwise. It helped me develop incredible knowledge of `React.js`.

However it became uncontrollable and I could not write any software using C++ because I felt i **MUST** understand everything and I just go deep and deep wishing to understand every single thing going on in my code.

I draw a border here.

If I understand conceptually the problem and can figure out an algorithm to solve it, this is too much. Because I can write a program without asking those questions.

If I do not understand concept such as textured, level of detail, lightning, Vulkan graphics pipeline setup. How does the data in vulkan flow, etc... Then I must know such things to be able to set up a graphics pipeline.

I did not see this until now.

### What did I do right

- I drew a distinction between knowing the concepts and not knowing the concepts.
- I drew a distinction when I should ask such questions.
- I realized what I was doing wrong.
- I decided to fight off this habit and complete a program without asking such questions.
- I realized I can use that skill to learn new things and understand problems on a whole new level.
- I realized that I need to train to switch on and off that skill.

### What did I do wrong

- While writing program I would drive off in that direction to understand everything.
- I spend maybe 30% more time than without asking such questions.

### What can I learn from it

A hard one... What can I learn from it? Maybe too much of anything can be either good or bad. If I want to focus solely on learning and figuring out the problem, I can drive off into details.

- I could set an alarm and consciously decide to dive into discovery mode.
- I could switch it on when I get stuck and need to figure out a problem.

It is good that I see it as a skill to use when I need it.

It has been my default behavior since forever... I honed it through reading book on deliberate practice and self-reflecting on how to improve it.

## Docs

The file `test-file.txt` is a test file for `mycli` program.

Compile and run `mycli` program with `test-file.txt` as an argument.

```powershell
cmake --build build; ./build/samples/mycli/mycli.exe --file ".\samples\mycli\test-file.txt"
```

## Add mongo database functionality

The idea is to use the c++ command line interface to interface with the mongo database. The mongo database runs inside docker which exposes the port to host machine.

Docker is supposed to make it easier to use mongodb on the machine.

Start the mongo database inside docker.

```powershell
docker-compose up -d
```

For more information, refer to: [MongoDB conversation with ChatGPT](./mongo.conversation.txt) which helped me set it up.
