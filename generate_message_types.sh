mkdir src/Messaging
mkdir src/Messaging/Types

fastrtpsgen -replace -d src/Messaging/Types MessageTypes/*.idl

rm src/Messaging/Types/*PubSubTypes.*