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

  std::fstream output ("./addressbook.contacts", ios::out | ios::app | ios::binary);

  if (argc < 4) {
    std::cerr << \
      "Usage: ./newContact <name> <id> <email> <phone number>" \
    << std::endl;
    return 1;
  }

  addressbook* contacts = new addressbook ();
  person* contact = contacts->add_person();
  phone* mobile = contact->add_phone();

  contact->set_name (argv[1]);
  contact->set_id (std::stoi(argv[2]));
  contact->set_email (argv[3]);

  mobile->set_number (argv[4]);
  mobile->set_type (person::MOBILE);

  if (contact->IsInitialized()) {
    std::cout << contact->DebugString() << std::endl;

    if (!contacts->SerializeToOstream (&output)) {
      std::cerr << "Contact failed to write" << std::endl;
      return 1;
    }

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
  }
  else {
    std::cerr << "Contact failed to initialize." << std::endl;
    google::protobuf::ShutdownProtobufLibrary();
    return 1;
  }


}

