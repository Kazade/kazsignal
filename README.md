# kazsignal

A super-simple signal/slot library for C++.

There's nothing clever about this, you can connect handlers to signals and emit them. Internally it uses a thread-safe (hopefully!) ring buffer to store the connections. You can't return values
from handlers. Handlers stay connected unless you disconnect using the returned connection, or cast that to a scoped_connection which will then deal with it for you.

# Usage

Make sure the `kazsignal` folder is on the include path. Then just...


```
#include <kazsignal/kazsignal.h>

class MyClass {
	DEFINE_SIGNAL(sig::signal<void ()>, my_signal)
	DEFINE_SIGNAL(sig::signal<void (bool, int)>, my_other_signal)
public:
	// ...
};

MyClass instance;

// Connect handlers
sig::connection conn = instance.my_signal().connect(some_func);
sig::scoped_connection other_conn = instance.my_other_signal().connect(some_other_func);


// Emit signals
instance.my_signal_();
instance.my_other_signal_(true, 1);
```

