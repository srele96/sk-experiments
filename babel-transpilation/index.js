const babel = require('@babel/core');

console.log(`
----------------------------
----------------------------
Presets used:
  * @babel/preset-env
----------------------------
`);
{
  const code = `
    const person = {
      name: 'John',
      lastName: 'Doe'
    }
    
    const { name } = person
  `;

  console.log('# Without presets:\n');
  {
    // without @babel/preset-env
    const result = babel.transformSync(code, {});
    console.log(result.code);
  }

  console.log('\n# With presets:\n');
  {
    // with @babel/preset-env
    const result = babel.transformSync(code, {
      presets: ['@babel/preset-env'],
    });
    console.log(result.code);
  }
}

console.log(`
----------------------------
----------------------------
Presets used:
  * @babel/preset-env
  * @babel/preset-typescript
----------------------------
`);
{
  const code = `
    interface Person {
      name: string;
      lastName: string;
    }

    const person: Person = {
      name: 'John',
      lastName: 'Doe'
    }
  `;

  const result = babel.transformSync(code, {
    presets: [
      '@babel/preset-env',
      ['@babel/preset-typescript', { allExtensions: true }],
    ],
  });
  console.log(result.code);
}

console.log(`
----------------------------
----------------------------
Presets used:
  * @babel/preset-env
  * @babel/preset-typescript
  * @babel/preset-react
----------------------------
`);
{
  const code = `
    function App() {
      return <div>Hello World</div>
    }
  `;

  const result = babel.transformSync(code, {
    presets: ['@babel/preset-env', ['@babel/preset-react']],
  });
  console.log(result.code);
}
