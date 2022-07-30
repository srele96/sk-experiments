# new

Create new experiment directory consistently from one template.

## Rough implementation steps

```
take every file from template directory and insert them in the location user provides
take name and description from user and insert them in package json file

PROCEDURES:

create_file
  message "creating file ${file}"
  success
    message "successfully created file ${file}"
  error
    message "failed to create file ${file}"

---------------------------------------------------------

read_file_content
  success
    replace_file_content_with_content_user_provides
    create_file
    ...
  err
    message "failed to read file ${file}", err

---------------------------------------------------------

create_all_files_in_parallel
  message "creating all template files"
  read_file_content
  read_file_content
  read_file_content
  ...

---------------------------------------------------------

read_file_names_from_template
  message "reading template files from ${dirname}"
  success
    message "successfully read template files"
    create_all_files_in_parallel
  err
    message "failed to read template files from ${dirname}", err

---------------------------------------------------------

create_directory
  message "creating directory ${dirname}"
  success
    message "successfully created directory ${dirname}"
    read_file_names_from_template
  err
    message "failed to create directory ${dirname}", err
```

## Docs

```
new <directory>                       Creates directory with empty package.json description.
new <directory> -d, --description     Creates directory with provided description for package.json.
```

## Usage

Create a new directory with description:

```
new my-awesome-experiment -d "my awesome description"
```

Create a new directory with empty description:

```
new my-awesome-experiment
```

Create a new directory with one-word description:

```
new my-awesome-experiment -d description
```
