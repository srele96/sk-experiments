# runner

Save and run one or series of commands.

You don't have to remember them any more, only aliases. Or list commands if you
forgot.

## Refine specifications without considering implementation details

Don't consider technical obstacles. Clearly specify implementation specifications
and their solutions.

## Specs

Configuration:

- add configuration
- read configuration
- delete configuration
- edit configuration

Singular command:

- add command
- read command
- delete command
- edit command

Multiple commands:

- add commands
- read commands
- delete commands
- edit commands

## Tools

- [Configuration file library](https://github.com/boostorg/property_tree).
- [CLI arguments parser library](https://github.com/boostorg/program_options).

## Informations

Answer question - Why is different config file type important?

- Check discussion [cosmiconfig - add support for TOML](https://github.com/davidtheclark/cosmiconfig/issues/150)
- Read [why json isn't a good configuration language](https://www.lucidchart.com/techblog/2018/07/16/why-json-isnt-a-good-configuration-language/) _(There are some valid points)_.
