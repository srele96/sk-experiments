import React from 'react';

const Button = ({ text, onClick }) => <button onClick={onClick}>{text}</button>;

// check if harmony-unused-export is present for this component
const UnusedButton = ({ text, onClick }) => (
  <button onClick={onClick}>{text}</button>
);

export { Button, UnusedButton };
