# React, click handler on async loaded button

Example solution of observing node for externally added content and reacting to mutations caused by it.

## Short summary of the code

Inside our React app we have a div with id `external-content-root`. The function simulates asynchronous adding of content to this node.

Inside of asynchronously added content is button and i want to attach my event listener to it.

Possible solution is to use `MutationObserver` which will observe dom node for changes and trigger callback when they happen.

Options passed to the `observe` function allow us to react on mutations anywhere below and including this node.
