#include <google/protobuf/util/json_util.h>
#include "schema/task_info.pb.h"

#include <iostream>


void PrintMessageAsString(const google::protobuf::Message& msg)
{
    google::protobuf::util::JsonPrintOptions jsonOptions;
    jsonOptions.add_whitespace = true;
    jsonOptions.always_print_primitive_fields = true;
  
    std::string result{};

    if (google::protobuf::util::Status::OK != google::protobuf::util::MessageToJsonString(msg, &result, jsonOptions))
    {
        std::cout << "Failed to print message.\n";
        return;
    }

    std::cout << result << "\n";
}

int main() {
  task_info::TaskInfo info;
  info.set_content("This is a content of message.");

  PrintMessageAsString(info);

  return 0;
}