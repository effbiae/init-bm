this repo shows how i'd like an "init" feature to work with baremetal.sh and BareMetal-Monitor

### BareMetal-Monitor change
see [this pull request](https://github.com/ReturnInfinity/BareMetal-Monitor/pull/10)
to see a proposal for monitor to change

### baremetal.sh change
when baremetal.sh is invoked like:
```
./baremetal.sh init.app file1 file2...
```
i'd like it to create an image with init.app, file1 and file2 in bmfs.

when the pc is started, i want monitor to see that init.app is the first file and to load init.app and execute it.

we wouldn't need to check for "only one file" in monitor any more.

see the monitor PR for a patch to baremetal.sh
