
#include <iostream>
#include <mosquitto.h>
#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::chrono::seconds

using namespace std;

#define mqtt_host "localhost"
#define mqtt_port 1883

void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
    if (result)
        cout << "node connection error, rc=" << result << endl;
    else
        cout << "node connected" << endl;
}

struct mosquitto *MessagingInit(const char *node_name)
{
    cout << "starting" << endl;
    uint8_t reconnect = true;
    struct mosquitto *mosq;
    int rc = 0;
    mosquitto_lib_init();
    mosq = mosquitto_new(node_name, true, 0);
    if (!mosq)
        return 0;
    mosquitto_connect_callback_set(mosq, connect_callback);
    rc = mosquitto_connect(mosq, mqtt_host, mqtt_port, 2);
    if (rc)
        return 0;
    cout << "node connecting" << endl;

    return mosq;
}

void MessagingSetMessageCallback(struct mosquitto *mosq, void (*on_message)(struct mosquitto *, void *, const struct mosquitto_message *))
{
    mosquitto_message_callback_set(mosq, on_message);
}

int MessagingSubscribe(struct mosquitto *mosq, int *mid, const char *sub, int qos)
{
    return mosquitto_subscribe(mosq, mid, sub, qos);
}

void MessagingLoop(struct mosquitto *mosq, void (*handle)(struct mosquitto *), int frequency)
{
    if (handle == nullptr)
        mosquitto_loop_forever(mosq, -1, 1);

    chrono::microseconds loop_time(0);
    if (frequency > 0)
        loop_time = chrono::microseconds(1000000 / frequency);

    for (;;)
    {
        auto start = chrono::system_clock::now();
        mosquitto_loop(mosq, 0, 1);
        if (handle)
            handle(mosq);

        auto elapsed = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now() - start);
        auto rest = loop_time - elapsed;
        if (rest.count() > 0)
            this_thread::sleep_for(rest);
    }
}