# Nodejs module system

I found out that module imports form a tree.

Yesterday in blog post I've read that imports should form a tree, but now i visualized it.

Also, `module` can be appended some property, because it is object.

That is why in webpack `module.hot` can be accessed as property. I assume it is appended to modules that are ready to be hot reloaded.
