import { createElement as e, useEffect } from 'react';
import {
  Controller,
  FormProvider,
  useForm,
  useFormContext,
} from 'react-hook-form';
import { useDispatch, useSelector } from 'react-redux';

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

function ReactHookForm() {
  const methods = useForm();

  return e(
    FormProvider,
    { ...methods },
    e(
      'form',
      {
        onSubmit: methods.handleSubmit(
          async (data, event) => {
            await new Promise((resolve) => setTimeout(resolve, 1000));

            // open modal

            // retrieve the status of the first check in the modal

            // update the status of the first check in the modal

            // if the status of the first check failed

            // show the error message
            // show user message to try again

            // retrieve the status of the second check in the modal

            // update the status of the second check in the modal

            // if the status of the second check failed

            // show the error message
            // show user message to try again

            // retrieve the status of the third check in the modal

            // update the status of the third check in the modal

            // if the status of the third check failed

            // show the error message
            // show user message to try again

            // retrieve the status of the fourth check in the modal

            // update the status of the fourth check in the modal

            // if the status of the fourth check failed

            // show the error message
            // show user message to try again

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

function MoreSamples() {
  const methods = useForm();

  // console.log({ methods });

  const defaultCheckboxValue = false;
  const checkboxValue = methods.watch('checkbox', defaultCheckboxValue);

  const defaultSomethingValue = '';
  const somethingValue = methods.watch('something', defaultSomethingValue);

  return e(
    'form',
    {
      onSubmit: methods.handleSubmit(
        (data, event) => {
          console.log({ data, event });
        },
        (error) => {
          console.error({ error });
        }
      ),
    },

    e(
      'label',
      null,
      e(Controller, {
        control: methods.control,
        name: 'something',
        defaultValue: '',
        rules: {
          required: 'Must not be empty!!!',
          pattern: {
            value: /^[a-z]+$/i,
            message: 'Only letters are allowed',
          },
        },
        render: ({ field, fieldState }) => {
          // console.log(
          //   { field, fieldState },
          //   fieldState.invalid,
          //   fieldState.error?.message
          // );

          const style = fieldState.invalid
            ? { border: '1px solid red', color: 'red' }
            : {};

          return e(
            'span',
            null,
            e('input', { style, type: 'text', ...field }),
            fieldState.invalid && e('span', null, fieldState.error?.message)
          );
        },
      }),
      e('p', null, "Something's value is `" + somethingValue + '`')
    ),

    // controller can be somewhere inside... somewhere... down? Yet it still
    // requires `methods.control`...

    e(
      'label',
      null,
      e(Controller, {
        control: methods.control,
        name: 'checkbox',
        defaultValue: defaultCheckboxValue,
        render({ field }) {
          return e('input', { type: 'checkbox', ...field });
        },
      }),
      e('p', null, 'Checkbox is ' + checkboxValue ? 'checked!' : 'not checked!')
    ),

    e('button', { type: 'submit' }, 'Submit')
  );
}

function App() {
  const dispatch = useDispatch();
  const store = useSelector((store) => store);

  useEffect(() => {
    dispatch({ type: 'foo/add', payload: 'foo' });
    dispatch({ type: 'bar/add', payload: 'bar' });
  }, [dispatch]);

  return e(
    'div',
    null,
    e(ReactHookForm),
    e(MoreSamples),
    e('h2', null, 'Redux Store'),
    e(
      'pre',
      null,
      JSON.stringify(
        store,
        (_, value) => {
          if (value instanceof Set) {
            return [...value];
          }

          return value;
        },
        2
      )
    )
  );
}

export { App };
