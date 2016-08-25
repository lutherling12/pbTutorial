#include <iostream>
#include <fstream>
#include <string>

#include "addressbook.pb.h"

typedef std::ios ios;
typedef tutorial::Person person;
typedef person::PhoneNumber phone;
typedef tutorial::AddressBook addressbook;

int main (int argc, char* argv[])
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  std::fstream input ("./addressbook.contacts", ios::in | ios::binary);

  person contact;
  addressbook abc;

  if (input.is_open()) {
    // does not work
    // while (!input.eof()) {
    //   if (contact.ParseFromIstream (&input))
    //     std::cout << contact.DebugString() << std::endl;
    //   else {
    //     std::cerr << "Failed to read from file." << std::endl;
    //     return 1;
    //   }
    if (abc.ParseFromIstream (&input)) {
      std::cout << abc.DebugString() << std::endl;
      return 0;
    }
  }
  else {
    std::cerr << "Failed to open file." << std::endl;
    return 1;
  }

}