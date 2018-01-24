#include "FilesTableReceive.h"

#include <iostream>

void FilesTableReceive::execute(void)
{
	const unsigned bufSize = 25*32; // 32 is size of hash (string)
	char buf[bufSize];
	int readBytes;
	int fileNumber = 0;
	std::string tmpHash;

	do {
		memset(buf, 0, sizeof(buf));
		if ((readBytes = read(socketFd,buf, bufSize)) == -1)
			perror("reading stream message");
		if (readBytes != 0)
		{
			if(opcode == 302)
			{
				for(unsigned i = 0; i < (unsigned)readBytes/32; ++i)
				{
					tmpHash.assign(&buf[i*32], 32);
					std::cout<<"File " << fileNumber++ <<" id: "
							<< tmpHash << std::endl;
				}
			}
			else if(opcode == 303)
			{
//				for(unsigned i = 0; i < readBytes/(2 * sizeof(size_t)); ++i)
//				{
//					std::cout<<"File " << fileNumber++ <<" id: "
//							<< static_cast<size_t>(buf[2 * i * sizeof(size_t)])
//							<< ", owner id: " << static_cast<size_t>(buf[4 + 2 * i * sizeof(size_t)])
//							<< std::endl;
//				}
			}
		}
	} while (readBytes != 0);
	close(socketFd);
}
