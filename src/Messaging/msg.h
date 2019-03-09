#include <mosquitto.h>

void default_connect_callback(struct mosquitto *mosq, void *obj, int result);
void default_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message);

struct mosquitto *MessagingInit(const char *node_name,
                                void (*connect_callback)(struct mosquitto *mosq, void *obj, int result) = default_connect_callback,
                                void (*message_callback)(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) = default_message_callback);
int MessagingSubscribe(struct mosquitto *mosq, int *mid, const char *sub, int qos);
int MessagingPublish(struct mosquitto *mosq, int *mid, const char *topic, int payloadlen, const void *payload, int qos, bool retain);
void MessagingLoop(struct mosquitto *mosq,
                   void (*handle)(struct mosquitto *) = nullptr, int frequency = 0);