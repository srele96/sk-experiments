import { createElement as e } from 'react';
import { FormProvider, useForm, useFormContext } from 'react-hook-form';

function First() {
  const { register } = useFormContext();

  return e(
    'fieldset',
    null,
    e('legend', null, 'First'),
    e('label', null, 'foo ', e('input', { ...register('first') }))
  );
}

function Second() {
  const { register } = useFormContext();

  return e(
    'fieldset',
    null,

    e('legend', null, 'Second'),

    e(
      'label',
      null,
      'bar ',
      e('input', { type: 'checkbox', ...register('bar') })
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

  return e(
    'fieldset',
    null,
    e('legend', null, 'Third'),
    e('p', null, 'group'),
    items.map((item, i) => {
      return e(
        'label',
        { key: i },
        e('input', {
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

  return e(
    FormProvider,
    { ...methods },
    e(
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
      e(First),
      e(Second),
      e(Third),
      e('button', { type: 'submit' }, 'Submit')
    )
  );
}

export { App };
