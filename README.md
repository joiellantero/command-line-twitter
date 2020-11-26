# Command Line Twitter

DISCLAIMER: The usage of this software requires some basic knowledge in C programming. This program is not in any way associated to Twitter Company. 

This project mimics the basic functionalities of Twitter, i.e., posting a tweet, sending private messages, viewing your private messages, and viewing your wall. The application allows users to log in and out; however, once you log out, all the data associated to your account will be deleted except the posted tweets.

---
## Installation

- All the `code` required to get started

### Clone

- Clone this repo to your local machine using `https://github.com/joiellantero/command-line-twitter`

### Setup

- If you haven't installed the gcc compiler on your computer, go to `https://gcc.gnu.org/install/` to install it.

> compile the C program
```shell
$ gcc twitter.c -o twitter
```

> run the executable file
```shell
$ ./twitter name
```
- replace "name" above with your own name

### Usage

> send a tweet (private message)
```shell
$ Enter a tweet: Hello, John! #offlineTwitter @JohnDoe
```

> send a tweet (posting it publicly)
```shell
$ Enter a tweet: Hello World! #publicTweet
```

> view notifications (viewing private messages)
```shell
$ @name:
$ Hello, John! #offlineTwitter @JohnDoe
```

> view wall (viewing public posts)
```shell
$ @name:
$ Hello World! #publicTweet
```

> logout
- this deletes all data associated with user except for their posted tweets.

---
## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[MIT license](http://opensource.org/licenses/mit-license.php)**
