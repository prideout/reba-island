This is a simple image generator that demonstrates how to use the [Reba](https://github.com/prideout/reba) machine image.  It creates grayscale island shapes that look like this:

![](https://github.com/prideout/reba-island/blob/master/islands.png)

---

**How to build on OS X using Docker**

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
build/genisland example.json
```

You can also run unit tests for the Python bindings:
```
scons install
py.test
```
