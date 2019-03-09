#include <mosquitto.h>

struct mosquitto *MessagingInit(const char *node_name);
void MessagingSetMessageCallback(struct mosquitto *mosq, void (*on_message)(struct mosquitto *, void *, const struct mosquitto_message *));
int MessagingSubscribe(struct mosquitto *mosq, int *mid, const char *sub, int qos);
void MessagingLoop(struct mosquitto *mosq, void (*handle)(struct mosquitto *) = nullptr, int frequency = 0);