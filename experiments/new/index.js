#!/usr/bin/env node
'use strict';

const { readFile, mkdir, writeFile } = require('fs');
const { join } = require('path');
const { Command } = require('commander');
const program = new Command();
const { name, description, version } = require('./package.json');

program.name(name).description(description).version(version);

/**
 *
 * @param {string} filePath Path to a file to read
 * @returns {Promise<string>} File content
 */
function getFileContent(filePath) {
  return new Promise((resolve, reject) => {
    if (typeof filePath !== 'string')
      reject(`Expected filePath to be type of string, received ${filePath}`);
    if (filePath === '') reject('filePath cannot be an empty string');

    readFile(filePath, { encoding: 'utf-8' }, (err, data) => {
      if (err) reject(err);
      else resolve(data);
    });
  });
}

/**
 * @param {string} name For package.json
 * @param {string} description For package.json
 */
function getPackageJsonWith(name = '', description = '') {
  if (typeof name !== 'string')
    throw new Error(`Expected name to be type of string, received ${name}`);
  if (typeof description !== 'string')
    throw new Error(
      `Expected description to be type of string, received ${description}`
    );

  return getFileContent(join(__dirname, 'template', 'package.json')).then(
    (content) => {
      const placeholder = { name: '{name}', description: '{description}' };

      return content
        .replace(placeholder.name, name)
        .replace(placeholder.description, description);
    }
  );
}

/**
 * @param {string} path A name for directory.
 * @return {Promise<string>} Created directory path.
 */
function mkdirAsync(path) {
  return new Promise((resolve, reject) => {
    if (typeof path !== 'string')
      reject(`Expected path to be type of string, received ${path}`);
    if (path === '') reject('path cannot be an empty string');

    mkdir(path, { recursive: true }, (err) => {
      if (err) reject(err);
      else resolve();
    });
  });
}

/**
 * @param {string} path
 * @param {string} content
 * @return {Promise<void>}
 */
function writeFileAsync(path, content) {
  return new Promise((resolve, reject) => {
    writeFile(path, content, 'utf-8', (err) => {
      if (err) reject(err);
      else resolve();
    });
  });
}

program
  .argument('<directory>', 'new directory for an experiment')
  .option('-d, --description <description>', 'experiment description', '')
  .action((directory, { description }) => {
    mkdirAsync(directory)
      .then(() => {
        // write package.json and yarn.lock
        const writeFiles = [
          getPackageJsonWith(directory, description).then((packageJson) => {
            return writeFileAsync(join(directory, 'package.json'), packageJson);
          }),
          getFileContent(join(__dirname, 'template', 'yarn.lock')).then(
            (yarnLock) => {
              return writeFileAsync(join(directory, 'yarn.lock'), yarnLock);
            }
          ),
        ];

        return Promise.all(writeFiles);
      })
      .then(() => {
        console.log(`Created ${directory}`);
      })
      .catch(console.error);
  });

program.parse();
