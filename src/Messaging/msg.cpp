
#include "msg.h"
#include <iostream>
#include <mosquitto.h>
#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::chrono::seconds

using namespace std;

#define mqtt_host "localhost"
#define mqtt_port 1883

void default_connect_callback(struct mosquitto *mosq, void *obj, int result)
{
    if (result)
        cout << "node connection error, rc=" << result << endl;
    else
        cout << "node connected" << endl;
}

void default_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
    cout << "Received a message on topic " << message->topic << " with length " << message->payloadlen << endl;
}

struct mosquitto *MessagingInit(const char *node_name,
                                void (*connect_callback)(struct mosquitto *mosq, void *obj, int result),
                                void (*message_callback)(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message))
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
    mosquitto_message_callback_set(mosq, message_callback);
    rc = mosquitto_connect(mosq, mqtt_host, mqtt_port, 2);
    if (rc)
        return 0;
    cout << "node connecting" << endl;

    return mosq;
}

int MessagingSubscribe(struct mosquitto *mosq, int *mid, const char *sub, int qos)
{
    return mosquitto_subscribe(mosq, mid, sub, qos);
}

int MessagingPublish(struct mosquitto *mosq, int *mid, const char *topic, int payloadlen, const void *payload, int qos, bool retain)
{
    return mosquitto_publish(mosq, mid, topic, payloadlen, payload, qos, retain);
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