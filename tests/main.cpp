
#include <kazsignal/kazsignal.h>

class MyClass {
    DEFINE_SIGNAL(sig::signal<void ()>, my_signal);
    DEFINE_SIGNAL(sig::signal<void (bool, int)>, my_other_signal);

public:
    void fire_signals() {
        my_signal_();
        my_other_signal_(true, 1);
    }
};

void check(bool value) {
    if(!value) {
        throw std::runtime_error("Test failed");
    }
}

int main(int argc, char* argv[]) {

    MyClass instance;

    int call_count = 0;

    // Connect handlers
    sig::connection conn = instance.my_signal().connect([&call_count]() {
        call_count++;
    });

    sig::scoped_connection other_conn = instance.my_other_signal().connect([&call_count](bool v, int i) {
        call_count++;
    });;

    // Emit signals
    instance.fire_signals();

    check(call_count == 2);
    check(conn.is_connected());
    check(other_conn.is_connected());

    conn.disconnect();

    check(!conn.is_connected());

    return 0;
}
