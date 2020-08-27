# Offline Twitter

This project mimics the basic functionality of Twitter, i.e., posting a tweet, sending private messages, viewing your private messages, and viewing your wall. The application allows users to log in and out; however, once you log out, all the data associated to your account will be deleted except the posted tweets.

---
## Installation

- All the `code` required to get started

### Clone

- Clone this repo to your local machine using `https://github.com/joiellantero/offline-twitter.git`

### Setup

- If you haven't, install the gcc compiler using `https://gcc.gnu.org/install/`

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
