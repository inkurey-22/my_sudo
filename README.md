# my_sudo
`my_sudo` is an EPITECH project from the Unix Shell Programming unit of 1st semester.
The goal is to reproduce the `sudo` command that gives temporary root access to the user.


## Contributors
- [Théophile Riffé](https://github.com/inkurey-22)
- [Leo Batillot](https://github.com/leo-batilliot)

## Objectives
The project is entirely coded in C, without the use of the PAM library for authentication.
Groups were composed of 2 students and 3 weeks were given.

The whole standard C library was authorized except `etpw*`, `*getsp*`, `getgr*`, `*fork*`, `*clone*`, `openat*`
The main goal was to learn how `sudoers`, `shadow`, `passwd`... files worked and how permissions were managed.
Flags `-ugEs` were mandatories.
/!\ The parsing of the sudoers file is limited to users and group (other options are skipped) and every mentionned user/group is assumed to have all permissions, with password required.

## Achievements
The project is usable in its base form.
Flags `-u` and `-s` passed the tests. My mate and myself couldn't completely figure out `-g` and `-E`.

## Usage
This project is to be built by the Makefile at the root of the repo.

```bash
make run
./my_sudo [-ug] [command [args...]]
```
