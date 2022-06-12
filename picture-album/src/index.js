import { createRoot } from 'react-dom/client';
import styled from 'styled-components';
import './index.css';
import { Album } from './Album';
import pictures from './hide-pictures';

// A picture album requirements.
//
// - Pictures are on top of each other.
// - Below the pictures are buttons that we can use to set active picture.
// - Newly visible picture has fade-in effect.
// - The saved index is index of the currently visible picture.
//   The images are array of file names.
// - The first image is the default active image.
// - The active image is on top of the others.
//
// Design:
// - The picture container is a rectangle with background darker than page.

const PageContainer = styled.article`
  margin: 0 auto;
  width: 100%;
  max-width: 1080px;
`;

const Title = styled.h1`
  margin-bottom: 16px;
  text-align: center;
`;

createRoot(document.getElementById('album')).render(
  <PageContainer>
    <Title>Attack on Titan</Title>
    {pictures.length === 0 ? (
      <h1>The album has no pictures to show :(</h1>
    ) : (
      <Album pictures={pictures} />
    )}
  </PageContainer>
);
