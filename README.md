this repo shows how i'd like an "init" feature to work with baremetal.sh and BareMetal-Monitor

when baremetal.sh is invoked like:
```
./baremetal.sh init.app file1 file2...
```
i'd like it to create an image with init.app, file1 and file2 in bmfs.

when the pc is started, i want monitor to see that init.app is the first file and to load init.app and execute it.

we wouldn't need to check for "only one file" in monitor any more.
