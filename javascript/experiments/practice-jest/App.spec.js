import { render, screen } from '@testing-library/react';
import { createElement } from 'react';
import { App } from './App';

describe('', () => {
  it('should display a header', () => {
    render(createElement(App));

    expect(screen.getByText('Hello World')).toBeVisible();
  });
});
