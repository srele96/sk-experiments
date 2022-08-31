function getUserSection() {
  const user = {
    displayName: 'Shrek',
    accountViews: 6,
  };

  const displayName = document.createElement('h2');
  const accountViews = document.createElement('p');
  const section = document.createElement('section');

  displayName.innerText = user.displayName;
  accountViews.innerText = `Account views: ${user.accountViews}`;
  section.appendChild(displayName);
  section.appendChild(accountViews);

  return section;
}

function getPermissionStatusElement(hasPermission) {
  const p = document.createElement('h2');
  p.innerText = `User ${
    hasPermission ? 'has ' : "doesn't have "
  } required permission`;

  return p;
}

function runShortCircuitExample() {
  const h1 = document.createElement('h1');
  h1.innerText = 'User profile page';

  const body = document.getElementsByTagName('body')[0];
  body.appendChild(h1);

  let hasPermission = true;
  // has permission to view user section
  hasPermission && body.appendChild(getUserSection());

  // this makes no sense, however body.appendChild is never evaluated
  hasPermission = false;
  hasPermission && body.appendChild(getPermissionStatusElement(hasPermission));
}

export { runShortCircuitExample };
