#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <sstream>
#include "sha256.cpp"

using namespace std;

class Block {
public:
	
	// Member variables (previously private)
	static uint32_t nextIndex;
	string Hash;
	string PrevHash;
	uint32_t index;
	int64_t nonce;
	time_t workingTime;
	vector<string> data;

	// Constructor
	Block(const vector<string>& sDataIn)
		: data(sDataIn) {
		index = nextIndex++;
		nonce = -1;
		workingTime = time(nullptr);
	}

	// Getters (previously private functions)
	string GetHash() const { 
		return Hash; 
	}

	// Mining function (previously private function)
	void MineBlock(uint32_t difficulty) {
		size_t size = (size_t)difficulty;
		vector<char> tempBuffer(size);

		for (uint32_t i = 0; i < difficulty; ++i) {
			tempBuffer[i] = '0';
		}

		string testBuffer(tempBuffer.begin(), tempBuffer.end());
		string testHash;

		do {
			nonce++;
			Hash = CalculateHash();
			testHash = Hash.substr(0, difficulty);
		} while (testHash != testBuffer);

		cout << "Block mined: " << Hash << endl;
	}

	inline string CalculateHash() const {
		stringstream streamBuffer;
		for (const std::string& line : data) {
    	streamBuffer << line;
  	}
		streamBuffer << index << workingTime << nonce << PrevHash;

		string buffer = streamBuffer.str();
		string hash = sha256(buffer);
		return hash;
	}
};

uint32_t Block::nextIndex = 0;

class Blockchain {
public:
	// Constructor
	Blockchain() {
		Block genesis = Block({"Genesis Block"});
		chain.emplace_back(genesis);
		difficulty = 1;
	};

	std::string display(const vector<string>& arr) {
		std::string output;
		for (int i = 0; i < 4; i++ ) {
			output += arr[i] + "\n";
		}
		return output;
	}

	// Function to add a new block
	void AddBlock(Block newBlock) {
		Block previousBlock = chain.back();
		string previousHash = previousBlock.Hash;
		newBlock.PrevHash = previousHash;

		newBlock.MineBlock(difficulty);
		chain.push_back(newBlock);
		std::cout << newBlock.index << std::endl;
		std::cout << display(newBlock.data);
		return;
	}

	uint32_t difficulty;
	vector<Block> chain;

	Block GetLastBlock() const { return chain.back(); }
};