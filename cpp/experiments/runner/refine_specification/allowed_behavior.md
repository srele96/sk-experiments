# Allowed behavior

Allowed behavior pseudo code to help us abstract the problem.

## CREATE

```txt
CREATE:
  if content_exists:
    do_you_want_to_overwrite
      if yes:
        create
      else:
        terminated_action_create
  else:
    create
```

## READ

```txt
READ:
  if content_exists:
    read
  else:
    cant_read
```

## UPDATE

```txt
UPDATE:
  if content_exists:
    do_you_want_to_update
      if yes:
        update
      else:
        terminated_action_update
  else:
    cant_read
```

## DELETE

```txt
DELETE:
  if content_exists:
    do_you_want_to_delete
      if yes:
        delete
      else:
        terminated_action_delete
  else:
    cant_read
```
