#!/usr/bin/env node
'use strict';

const { readFile, mkdir, writeFile } = require('fs/promises');
const { join, basename } = require('path');
const { Command } = require('commander');
const program = new Command();
const { name, description, version } = require('./package.json');

program.name(name).description(description).version(version);

function getTemplate(fileName) {
  if (typeof fileName !== 'string')
    throw new Error('fileName must be string, received ' + typeof fileName);
  if (fileName === '') throw new Error("fileName can't be empty string");

  // we use __dirname because templates live in the package
  return readFile(join(__dirname, fileName), 'utf-8');
}

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

          getTemplate('template-package.json')
            .then((packageJson) => {
              // replace placeholders with user input
              const namePlaceholder = '{name}';
              const descriptionPlaceholder = '{description}';

              return packageJson
                .replace(namePlaceholder, baseDirname)
                .replace(descriptionPlaceholder, description);
            })
            .then((packageJson) => {
              // write package.json to created directory
              return writeFile(
                join(directory, 'package.json'),
                packageJson,
                'utf-8'
              );
            })
            .then(() => {
              console.log('Created ' + join(baseDirname, 'package.json'));
            })
            .catch((error) => {
              console.log(
                'Error creating ' + join(baseDirname, 'package.json'),
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
