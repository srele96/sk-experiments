'use strict';

const PACKAGE_JSON = `{
  "name": "{name}",
  "version": "0.1.0",
  "description": "{description}",
  "author": "Kostic Srecko",
  "repository": {
    "type": "git",
    "url": "git+https://github.com/srele96/sk-experiments.git"
  },
  "bugs": {
    "url": "https://github.com/srele96/sk-experiments/issues"
  },
  "homepage": "https://github.com/srele96/sk-experiments#readme"
}
`;

const README_MD = `# {name}

{description}
`;

module.exports = { PACKAGE_JSON, README_MD };
