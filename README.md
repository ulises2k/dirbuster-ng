# dirbuster-ng

A small, fast, multi-threaded web content/directory brute-forcer written in C,
built on top of **libcurl** and **pthreads**. Given a target URL and a wordlist,
it requests `URL/<word>` for every entry and reports the paths that exist.

> ⚠️ **Legal / ethical use only.** This is a security testing tool. Only run it
> against systems you own or are explicitly authorized to test. Unauthorized
> scanning may be illegal.

---

## Features

- Multi-threaded engine (configurable number of workers).
- Built-in embedded wordlist (used when no dictionary is supplied).
- External wordlists (plain text, one word per line) — see `wordlists/`.
- Per-word extension fuzzing (e.g. append `.php,.bak,.old`).
- HTTP proxy support, with optional proxy authentication.
- HTTP Basic/Digest authentication.
- Custom or predefined `User-Agent` strings (browsers and crawlers).
- Output to a file, plus a quiet mode for clean reports.
- Reports paths returning HTTP **200** or **403**.

---

## Requirements

- A C compiler (`gcc` or `clang`)
- `cmake` (>= 3.5)
- `make`
- **libcurl** development headers
- **pthread** (provided by the system libc)

### Install dependencies on Kali / Debian / Ubuntu (incl. WSL)

```bash
sudo apt update
sudo apt install -y build-essential cmake libcurl4-openssl-dev
```

---

## Building

```bash
# from the project root
mkdir -p build
cd build
cmake ..
make
```

The resulting binary is `build/dirbuster-ng`.

### Building under WSL (Windows)

When the repository lives on a Windows drive, build it from inside WSL using the
`/mnt/c/...` path. Quote the path because it contains spaces:

```bash
cd "/mnt/c/Users/<user>/.../GitHub/dirbuster-ng"
mkdir -p build && cd build
cmake ..
make
```

### Installing (optional)

```bash
# from the build directory
sudo make install      # installs to <prefix>/bin (default /usr/local/bin)
```

---

## Usage

```
dirbuster-ng [options...] <url>
```

The target URL is always the **last** argument.

### Options

| Option | Argument | Description |
|--------|----------|-------------|
| `-w`   | `<nb_threads>`        | Number of worker threads (default: **8**). |
| `-d`   | `<dict>`              | Load an external text file as the dictionary. |
| `-e`   | `<ext>`               | Comma-separated list of extensions appended to each word (e.g. `php,bak`). |
| `-t`   | `<seconds>`           | Per-request HTTP timeout (default: **2**). |
| `-X`   | `<proxy:port>`        | Use an HTTP proxy for all requests. |
| `-K`   | `<user:password>`     | Credentials for proxy authentication. |
| `-A`   | `<user:password>`     | Credentials for HTTP (Basic/Digest) authentication. |
| `-U`   | `<user_agent>`        | Set a custom `User-Agent` string. |
| `-u`   | `<ua>`                | Use a predefined `User-Agent` (see table below). |
| `-W`   | `<file>`              | Save results to a file. |
| `-q`   | —                     | Quiet mode (useful together with `-W`). |
| `-V`   | —                     | Verbose: print every request URL and response code. |
| `-h`   | —                     | Print help and exit. |
| `-v`   | —                     | Print version and exit. |

### Predefined User-Agents (`-u`)

| Key     | User-Agent |
|---------|------------|
| `ff`    | Mozilla Firefox |
| `chr`   | Google Chrome |
| `saf`   | Apple Safari |
| `ope`   | Opera |
| `opem`  | Opera Mobile |
| `ie`    | Microsoft Edge |
| `fen`   | Firefox for Android |
| `bb`    | Android Mobile (Chrome) |
| `gbot`  | Google Bot |
| `bing`  | Microsoft Bing Crawler |
| `bspid` | Baidu Spider |

---

## Examples

Scan a host with the built-in wordlist:

```bash
./dirbuster-ng http://target.example.com
```

Use a custom wordlist with 20 threads and a 3-second timeout:

```bash
./dirbuster-ng -w 20 -t 3 -d ../wordlists/common.txt http://target.example.com
```

Fuzz extensions on each word:

```bash
./dirbuster-ng -d ../wordlists/common.txt -e php,bak,old http://target.example.com
```

Go through a proxy, pretending to be Google Chrome, and save the report quietly:

```bash
./dirbuster-ng -X 127.0.0.1:8080 -u chr -q -W results.txt \
               -d ../wordlists/common.txt http://target.example.com
```

Scan a site protected by HTTP Basic auth, with verbose output:

```bash
./dirbuster-ng -A admin:secret -V -d ../wordlists/common.txt http://target.example.com
```

---

## How it works

1. `main()` parses arguments and initializes a shared work queue.
2. The wordlist (built-in or from `-d`) is loaded into the queue, optionally
   expanded by the extensions given with `-e`.
3. `-w` worker threads pull words off the queue under a mutex, build
   `URL/<word>`, and issue an HTTP request via libcurl.
4. Any path returning HTTP **200** or **403** is reported (and written to the
   `-W` file when set).

---

## Project layout

```
.
├── CMakeLists.txt          # build configuration
├── README.md               # this file
├── src/
│   ├── dirbuster-ng.c      # entry point, argument parsing, worker engine
│   ├── dirbuster-ng.h      # main header / config includes
│   ├── dirbuster-ng_config.h
│   ├── queue.c / queue.h   # thread-shared work queue
│   ├── utils.c / utils.h   # string helpers (explode, trim, ...)
│   ├── uagents.c / uagents.h  # predefined User-Agent strings
│   ├── common.h            # shared constants
│   └── dict.h              # embedded default wordlist
└── wordlists/              # bundled dictionaries
```

---

## License

Dirbuster NG 0.1 — (c) 2012 WintermeW. See the source headers for details.
