import { createElement } from 'react';
import { FormProvider, useForm, useFormContext } from 'react-hook-form';

function First() {
  const { register } = useFormContext();

  return createElement(
    'fieldset',
    null,
    createElement('legend', null, 'First'),
    createElement(
      'label',
      null,
      'foo ',
      createElement('input', { ...register('first') })
    )
  );
}

function Second() {
  const { register } = useFormContext();

  return createElement(
    'fieldset',
    null,

    createElement('legend', null, 'Second'),

    createElement(
      'label',
      null,
      'bar ',
      createElement('input', { type: 'checkbox', ...register('bar') })
    )
  );
}

function Third() {
  const { register } = useFormContext();

  const items = [
    { value: 'sk-experiments', label: 'sk-experiments' },
    { value: 'sk-engine', label: 'sk-engine' },
    { value: 'sk-learning', label: 'sk-learning' },
  ];

  return createElement(
    'fieldset',
    null,
    createElement('legend', null, 'Third'),
    createElement('p', null, 'group'),
    items.map((item) => {
      return createElement(
        'label',
        null,
        createElement('input', {
          ...register('group'),
          type: 'radio',
          value: item.value,
        }),
        item.label
      );
    })
  );
}

function App() {
  const methods = useForm();

  return createElement(
    FormProvider,
    { ...methods },
    createElement(
      'form',
      {
        onSubmit: methods.handleSubmit(
          (data, event) => {
            console.log({ data, event });
          },
          (error) => {
            console.log({ error });
          }
        ),
      },
      createElement(First),
      createElement(Second),
      createElement(Third),
      createElement('button', { type: 'submit' }, 'Submit')
    )
  );
}

export { App };
