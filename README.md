This is a simple image generator that demonstrates how to use the [Reba](https://github.com/prideout/reba) docker container.  It creates grayscale island shapes that look like this:

![](https://github.com/prideout/reba-island/blob/master/islands.png)

---

**How to build and run on OS X.**

First, install `boot2docker` if you haven't already.

Next, clone this repo and build the machine image:

```bash
cd ~/git
git clone git@github.com:prideout/reba-island.git
cd reba-island
. env.sh
```

The script you just ran not only invoked `docker` to build your machine image, it also created an alias that lets you quickly attach to it.  Trying attaching to it now:

```
island-bash
```

Push return a few times to see a prompt.  You should be in the `/island` folder in your Linux instance.

Type the following commands inside your instance to build and run the example renderer:
```bash
scons
build/genisland test/example.json
```

You can also run unit tests for the Python bindings:
```
scons install
py.test
```

**How to start the render server.**

First, forward 8082 from your mac to the VirtualBox host’s port, which can be done like this:

```bash
VBoxManage controlvm "boot2docker-vm" natpf1 "tcp-port8082,tcp,,8082,,8082"
```

Or, you can use the VirtualBox GUI:

- After selecting the boot2docker machine, open **Settings** from the **Machine** menu (or press Cmd-S).
- In the Settings window, choose the **Network** icon at the top, then click the Port **Forwarding** button.
- Add a row to the table and use `127.0.0.1` for the Host IP column, and `8082` in both the Host Port and Guest Port columns.

Now you can run `src/server.py` in your instance, which prints out some spew like this:

```
Bottle v0.12.8 server starting up (using WSGIRefServer())...
Listening on http://0.0.0.0:8082/
Hit Ctrl-C to quit.

```

Now, you should see a welcome message when entering `localhost:8082` into a browser on your mac.
