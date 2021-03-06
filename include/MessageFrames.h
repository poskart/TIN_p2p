#ifndef SRC_INFOMESSAGE_H_
#define SRC_INFOMESSAGE_H_
#include <cstdlib>
#include <string>

class InfoMessage {
public:
	InfoMessage(size_t opcode = 0);
	InfoMessage(size_t _opcode, size_t myId, std::string _hash);
	InfoMessage(size_t _opcode, size_t nodeCnt, size_t senderId);
	InfoMessage(const InfoMessage & other);
	size_t opcode;
	size_t firstField;
	size_t secondField;
	size_t thirdField;
	char hash[33];
};

#endif /* SRC_INFOMESSAGE_H_ */
