import { ReactNode } from 'react';

interface Props {
  children: ReactNode;
  title: string;
}

function Page({ children, title }: Props) {
  return (
    <html>
      <head>
        <title>{title}</title>
      </head>
      <body>
        <div id="__root">{children}</div>
      </body>
    </html>
  );
}

export { Page };
