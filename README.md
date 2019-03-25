# dmon #

## Overview ##

This is a file monitoring application called `dmon` , which scans a `root` directory for any changes to files underneath this folder and executes user specified actions on the files based on pattern matching rules.

For instance, suppose `dmon` was monitoring the `root` folder `/folder/to/monitor` and a file named `/folder/to/monitor/Foster the People/Helena Beat.mp3` was created. A scan of the root folder would detect that this file was created and check if there is a pattern rule that matches the name of the file.

For example, suppose there is a pattern rule that looks like this:
`CREATE *.mp3 mpv ${FULLPATH}`. When the scan detects that the `/folder/to/monitor/Foster the People/Helena Beat.mp3` is created, it will see that this file matches the `*.mp3` pattern and will execute the `mpv ${FULLPATH}` command (i.e. it will play the song).

## Objective ##

This service can be used to trigger actions, such as rebuilding a project, deploying code, etc, based on the different events (file modification, creation, or removal).


## Design ##
### Scanning ###

To begin a scan, a user should start `dmon` in the following manner:

```bash
# Scan current directory every 5 seconds

$ ./dmon .
Monitoring /usr/home
```

This will start the `dmon` program such that it scans the current directory every 5 seconds.
The user may specify a different scanning frequency via the -t command-line option:

```bash
# Scan current directory every 60 seconds
$ ./dmon -t 60 .
Monitoring /usr/home
```

### Events ###
During the scan, `dmon` will examine all the files under the `root` directory and any sub-directories (i.e. nested directories), to determine if any of the following system events occurred:

1. __CREATE__: A file has been created under the monitored directory.
2. __MODIFY__: A file has been modified under the monitored directory.
3. __DELETE__: A file has been deleted under the monitored directory.

__Note__: On the initial scan, no action is taken since `dmon` doesn't know about any of the files yet, so it doesn't know if the file was created, modified, or deleted.

### Rules ###
By default, `dmon` will load in pattern rules from the file `rules` unless otherwise specified by the `-f` flag as shown below:

```bash
# Scan current directory every 5 seconds with custom.rules
$ ./dmon -f custom.rules .
Monitoring /usr/home
```

This `rules` file contains a series of rules (one per line) specified in the following format:

```bash
EVENT       PATTERN     ACTION
```

Any empty lines or lines that begin with a # in the `rules` file are ignored. Any invalid lines (i.e. do not match the format above) displays an error message `Invalid rule: ...` and quits the program.


For example, to automatically compile a `C` program when it has been modified, you can have the following rule:

```bash
# Compilation rule
MODIFY      *.c         cc -o ${BASEPATH} ${FULLPATH}
```
This rule means that when a __MODIFY__ event is detected, any files thatmathc the pattern `*.c` should execute the command `cc -o ${BASEPATH} ${FULLPATH}`.

__Note__: The pattern is checked against both the full path of the file in question and its basename. If either the full path of the basename matches the pattern, then the rule is considered a match and the action is executed.

If a user were to modify say the `hello.c` in the root directory, then `dmon` would detect this file modification, match the rule above, print out the message below, and execute the corresponding action:

```bash
# Scan current directory every 5 seconds
$ ./dmon .
Monitoring /usr/home
Detected "CREATE" event on "hello.c"    # Detect existence of hello.c

# Modify hello.c in another terminal
Detected "MODIFY" event on "hello.c"    # Detect modification
Matched "*.c" pattern on "hello.c"      # Detect pattern match
Executing action "cc -o ${BASEPATH} ${FULLPATH}" on "hello.c"
``` 

__Note__: The loggin messages as show above are included as part of the normal operation of `dmon`.

### Environment Variables ###
To allow actions to use information about the corresponding event, `dmon` must pass the following [environmental variables] to specified command:
1. __BASEPATH__: This is the base path of the file (i.e without any proceeding extensions).
2.  __FULLPATH__: This is the full path of the file.
3. __EVENT__: This is the type of even detected.
4. __TIMESTAMP__: This is the current timestamp.

In the example above, the ${BASEPATH} and ${FULLPATH} variables will be expanded to `hello.c` and `/usr/home/hello.c` respectively.

### SIGINT ###
Upon receiving the `SIGINT` signal, `dmon` cleans up any allocated resources (where possible) and exits gracefully.

```bash
$ ./dmon .
Monitoring /usr/home

# Send Control-C
Cleaning up
Bye!
```

### Usage ###

The full set of `dmon` command-line options are shown below:

```bash
$ ./dmon -h
Usage: dmon [options] ROOT

Options:
    -h          Prints this help message
    -f RULES    Load rules from this file (default is rules)
    -t SECONDS  Time between scans (default is 5 seconds)
```

### Building the App ###
The repo includes a `Makefile` that builds and cleans the project (and all its components):

```bash
$ make          # Builds dmon

$ make clean    # Remove dmon and any intermediate files. 

```
