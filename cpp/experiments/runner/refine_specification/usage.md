# Usage

Usage specifications for the `runner` command line interface.

## SYNOPSYS

```terminal
runner config [--create] [--interactive]
runner config [--create] [--path=<value>]
runner config [--create] [--key=<value>] [--value=<value>]

runner config [--read] [--all]
runner config [--read] [--keys]
runner config [--read] [--find=<value>]
runner config [--read] [--find-all=<value>]

runner config [--update] [--interactive]
runner config [--update] [--interactive] [--key=<key>]
runner config [--update] [--key=<value>] [--new-key=<value>] [--new-value=<value>]

runner config [--delete] [--delete-config]
runner config [--delete] [--key=<value>]
```

## DESCRIPTION

`--create`

Indicates that we want the create operation.

`--interactive`

Interactive behavior using command line interface.

`--path=<value>`

Command line interface will use the path to find the configuration.

`--key=<value>`

The key we want to work with.

`--value=<value>`

A value for the key.

`--read`

Indicates we want the read operation.

`--all`

Indicates that we want everything.

`--keys`

Indicates that we only want the keys.

`--find=<value>`

Indicates we want the first key whose content or key itself contain the value.

`--find-all=<value>`

Indicates we want every key whose content or key itself contain the value.

`--update`

Indicates we want the read operation.

`--new-key=<value>`

A new value for the key itself.

`--new-value=<value>`

A new value for the key's value.

`--delete`

Indicates we want the delete operation.

`--delete-config`

Indicates we want to delete the configuration.

## Allowed combinations

Allowed combinations are in the [SYNOPSYS](#synopsys) heading.
