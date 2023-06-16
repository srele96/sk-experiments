#!/usr/bin/env node
'use strict';

const { mkdir, writeFile } = require('fs/promises');
const { join, basename } = require('path');
const { Command } = require('commander');
const program = new Command();
const { name, description, version } = require('./package.json');
const templates = require('./templates');

program.name(name).description(description).version(version);

program
  .argument('<directory>', 'new directory for an experiment')
  .option('-d, --description <description>', 'experiment description', '')
  .action((directory, { description }) => {
    // user may provide dirname or path which
    // results in invalid name for package.json
    const baseDirname = basename(directory);

    // create directory
    mkdir(directory, { recursive: true })
      .then((createdDirectoryPath) => {
        // directory successfully created
        if (typeof createdDirectoryPath === 'string') {
          console.log('Created ' + baseDirname);

          // replace placeholders with user input
          const namePlaceholder = '{name}';
          const descriptionPlaceholder = '{description}';

          const PACKAGE_JSON = templates.PACKAGE_JSON
            /* stupid formatting */
            .replace(namePlaceholder, baseDirname)
            .replace(descriptionPlaceholder, description);

          // write package.json to created directory
          writeFile(join(directory, 'package.json'), PACKAGE_JSON, 'utf-8')
            .then(() => {
              console.log('Created ' + join(baseDirname, 'package.json'));
            })
            .catch((error) => {
              console.log(
                'Error creating ' + join(baseDirname, 'package.json'),
                error
              );
            });

          // replace placeholders with user input
          const README_MD = templates.README_MD
            /* stupid formatting */
            .replace(namePlaceholder, baseDirname)
            .replace(descriptionPlaceholder, description);

          // write README.md to created directory
          writeFile(join(directory, 'README.md'), README_MD, 'utf-8')
            .then(() => {
              console.log('Created ' + join(baseDirname, 'README.md'));
            })
            .catch((error) => {
              console.log(
                'Error creating ' + join(baseDirname, 'README.md'),
                error
              );
            });

          // write empty yarn.lock to created directory
          writeFile(join(directory, 'yarn.lock'), '', 'utf-8')
            .then(() => {
              console.log('Created ' + join(baseDirname, 'yarn.lock'));
            })
            .catch((error) => {
              console.error(
                'Error creating ' + join(baseDirname, 'yarn.lock'),
                error
              );
            });
        } else {
          throw new Error('Directory already exists!');
        }
      })
      .catch((error) => {
        console.error('Error creating ' + baseDirname, error);
      });
  });

program.parse();
