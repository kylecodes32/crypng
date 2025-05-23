#pragma once

#define AES128 1
#define CBC 1

#include <thread>
#include <random>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <bitset>
#include "aes.h"
#include "image_handler.h"

const uint8_t LSB_ZERO = 0b00000000;
const uint8_t LSB_ONE = 0b00000001;
const uint8_t BYTE_VAL[2] = {LSB_ZERO, LSB_ONE};
const uint8_t BLOCK_SIZE = 8;

struct Block
{
    bool *block_bits;
    int length;
    int loc_x;
    int loc_y;
    uint8_t image_channels;
    uint8_t block_channel;
    double mean;
    double noise_score;
};

std::string test_aes();
void InitializeRandomSeed();
void GenerateRandomKey(unsigned char *key, size_t length);
void ThreadworthyGenerateRandomKey(unsigned char *key, size_t length);
bool GenerateRandomBit(float prob);
bool GetNthBitFromByte(unsigned char byte, int n);
bool GetBitFromArray(unsigned char *message, size_t index);
void EncodeMessageLinear(unsigned char *message, size_t length, int channel, ImageDetails image_details);
std::string DecodeMessageLinear(size_t length, int channel, ImageDetails image_details);
void TestEncode(ImageDetails image_details);
std::string TestDecode(ImageDetails image_details);
void ZeroLSB(ImageDetails image_details);
void LSBtoMSB(ImageDetails image_details);
void LSBtoMSBChannel(ImageDetails image_details, int channel);
void LSBtoMSBChannelNthBit(ImageDetails image_details, int channel, bool composite, int bit);
void PopulateBitArray(bool *lsb, bool *second_lsb, ImageDetails image_details);
std::vector<Block> CreateBlockList(bool *bits, ImageDetails image_details);
void CalculateBlockStats(Block &block, int channel);
int PartitionBlocks(std::vector<Block> &vec_blocks, int idx_low, int idx_high);
void QuicksortBlocks(std::vector<Block> &vec_blocks, int idx_low, int idx_high);
void WriteMessageToHighVarianceBlockLSB(unsigned char *message_buffer, int message_length, std::vector<Block> vec_blocks, ImageDetails image_details);
void ReadMessageFromHighVarianceBlockLSB(unsigned char *message_buffer, int message_length, std::vector<Block> vec_blocks, ImageDetails image_details);
std::size_t HashMemory(unsigned char *data, int length);

namespace XCrypt
{
    void PerformEncryptionPipeline(char *message, int message_length, unsigned char *private_key, int key_length, ImageDetails image_details, bool &complete);
    void ThreadPerformEncryptionPipeline(char *message, int message_length, unsigned char *private_key, int key_length, ImageDetails image_details, bool &complete);
    void PerformDecryptionPipeline(char *message_buffer, int &message_length, unsigned char *private_key, int key_length, ImageDetails image_details, bool &complete);
    void ThreadPerformDecryptionPipeline(char *message_buffer, int &message_length, unsigned char *private_key, int key_length, ImageDetails image_details, bool &complete);
}
