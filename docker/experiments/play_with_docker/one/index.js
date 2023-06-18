// ----------------------------------------------------------------------------
// Ignore all good practices and make services as fast as possible to use with
// docker compose.
// ----------------------------------------------------------------------------

const pg = require('pg');
const redis = require('redis');
const express = require('express');
const app = express();

const pgPool = new pg.Pool({
  user: process.env.POSTGRES_USER,
  password: process.env.POSTGRES_PASSWORD,
  database: process.env.POSTGRES_DB,
  host: 'postgres',
  port: 5432,
});

const redisClient = redis.createClient({
  url: 'redis://redis:6379',
});

console.log('Connecting to redis...');
redisClient
  .connect()
  .then(() => {
    console.log('Connected to redis.');
  })
  .catch((error) => {
    console.error('Error connecting to redis.\n', error);
  });

app.use((req, res, next) => {
  res.setHeader('Access-Control-Allow-Origin', '*');
  next();
});

app.get('/', (req, res) => {
  redisClient
    .incr('root')
    .then((value) => {
      res.send(`Request to / times: ${value}`);
    })
    .catch((error) => {
      console.error('Error incrementing root.\n', error);
      res.status(500);
      res.send('Error incrementing root.');
    });
});

app.get('/foo', (req, res) => {
  redisClient
    .incr('foo')
    .then((value) => {
      res.send(`Request to /foo times: ${value}`);
    })
    .catch((error) => {
      console.error('Error incrementing foo.\n', error);
      res.status(500);
      res.send('Error incrementing foo.');
    });
});

app.get('/bar', (req, res) => {
  redisClient
    .incr('bar')
    .then((value) => {
      res.send(`Request to /bar times: ${value}`);
    })
    .catch((error) => {
      console.error('Error incrementing bar.\n', error);
      res.status(500);
      res.send('Error incrementing bar.');
    });
});

app.get('/postgres', async (req, res) => {
  try {
    const client = await pgPool.connect();
    const result = await client.query('SELECT * FROM my_schema.users');
    client.release();
    res.status(200);
    res.json(result.rows);
  } catch (error) {
    console.error('Error getting users.\n', error);
    res.status(500);
    res.send('Error getting users.');
  }
});

app.listen(3000, () => {
  console.log('http://localhost:3000');
});
