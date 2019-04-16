#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/publisher/Publisher.h>

using namespace eprosima::fastrtps;

typedef void(OnPubMatch_t)(Publisher *pub, MatchingInfo &info);
typedef void(OnSubMatched_t)(Subscriber *sub, MatchingInfo &info);
typedef void(OnMessage_t)(Subscriber *sub);