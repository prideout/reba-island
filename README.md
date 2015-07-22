This is a simple image generator that demonstrates how to use the [Reba](https://github.com/prideout/reba) docker container.  It creates grayscale island shapes that look like this:

![](https://github.com/prideout/reba-island/blob/master/islands.png)

---

**How to build and run.**

First, build the Reba machine image:

```bash
cd ~/git
git clone git@github.com:prideout/reba.git
cd reba
./reba-build
```

Next, clone this repo and attach to a Reba instance:

```bash
cd ~/git
git clone git@github.com:prideout/reba-island.git
cd reba-island
. env.sh
reba
```

Type the following commands in your Reba instance to build and run the example renderer:
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

First, forward 8082 from your mac to the VirtualBox host’s port.

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

Now, you should see something when entering `localhost:8082/hello` into a browser on your mac.
