# How do streams transfer data?

An attempt to understand how streams data transfer works.

## Program specifications

Create a program that reads the data and writes it elsewhere using streams.
From a readable stream, pipe the data to:

- a file
- process.stdout

Create a program to transfer executable from location A to location B.
After transfer, run the executable to verify if it works.

- create a c++ program, build and execute it verify that it runs and works
- create a javascript program that transfers the executable to another location
- run the transferred executable to verify that transfer succeeded

## Lessons learned

- streams don't care about the data they transfer
- all data is transferred through the streams

## Streams logic

- WriteStream - Writes data to a specified destination via the write function
- ReadStream - Reads data from a specified destination to the internal buffer
