#include "NodeInfo.h"

void NodeInfo::addNewFileEntry(std::string hash, size_t nodeId)
{
	std::unique_lock<std::mutex> uLock(nodeInfoMtx);
	nodeFiles.insert(std::pair<std::string, size_t>(hash, nodeId));
}

void NodeInfo::removeFile(std::string hash)
{
	std::unique_lock<std::mutex> uLock(nodeInfoMtx);
	auto it = nodeFiles.find(hash);
	nodeFiles.erase(it);
}

void NodeInfo::addNewNode(struct in_addr nodeIP) {
	std::unique_lock<std::mutex> uLock(nodeInfoMtx);
	nodeMap.insert(std::pair<size_t,struct in_addr>(nodeCnt, nodeIP));
	std::cout << "Added new node:" << std::endl
				<< "\tNode ID: " << nodeCnt << std::endl
				<< "\tNode IP: " << inet_ntoa(getNodeIP(nodeCnt)) << std::endl;
	++nodeCnt;
}

void NodeInfo::removeNode(size_t nodeId) {
	std::unique_lock<std::mutex> uLock(nodeInfoMtx);
	nodeMap.erase(nodeId);
}

struct in_addr NodeInfo::getNodeIP(size_t nodeId) {
	std::unique_lock<std::mutex> uLock(nodeInfoMtx);
	std::map<size_t,struct in_addr>::iterator it = nodeMap.find(nodeId);
	if (it == nodeMap.end()) {
		struct in_addr tmp;
		tmp.s_addr = 0;
		return tmp;
	}
	return it->second;
}

void NodeInfo::setNode(size_t nodeId, struct in_addr nodeIP) { //change node IP or create new entry
	std::unique_lock<std::mutex> uLock(nodeInfoMtx);
	std::map<size_t,struct in_addr>::iterator it = nodeMap.find(nodeId);
	if (it == nodeMap.end()) {
		nodeMap.insert(std::pair<size_t,struct in_addr>(nodeId, nodeIP));
		return;
	}
	it->second = nodeIP;
}

void NodeInfo::callForEachNode(std::function<void (struct in_addr *)> callback)
{
	std::unique_lock<std::mutex> uLock(nodeInfoMtx);
	for(auto & addr : nodeMap)
		callback(&(addr.second));
}

void NodeInfo::callForEachFile(std::function<void (std::string)> callback)
{
	std::unique_lock<std::mutex> uLock(nodeInfoMtx);
	for(auto & file : nodeFiles)
		callback(file.first);
}

size_t NodeInfo::getOwnerId(std::string hash) {
	std::unique_lock<std::mutex> uLock(nodeInfoMtx);
	return nodeFiles.find(hash)->second;
}
