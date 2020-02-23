/*
 * cpu_info.cpp
 *
 *  Created on: Dec 14, 2019
 *      Author: devel
 */


#include <intrin.h>
#include <string>
#include <unordered_set>
#include "../cpu_info.hpp"

namespace license {
using namespace std;

CpuInfo::CpuInfo() {}

CpuInfo::~CpuInfo() {}
/**
 * Detect Virtual machine using hypervisor bit.
 * @return true if the cpu hypervisor bit is set to 1
 */
bool CpuInfo::is_hypervisor_set() const {
	int cpui[4] = {0};
	__cpuid(cpui, 0x1);

	return ((cpui[2] >> 31) & 1);
}

uint32_t CpuInfo::model() const {
	int cpui[4] = {0};
	__cpuid(cpui, 0x1);
	// ax bits 0-3 stepping,4-7 model,8-11 family id,12-13 processor type
	//        14-15 reserved, 16-19 extended model, 20-27 extended family, 27-31 reserved
	// bx bits 0-7 brand index
	return (cpui[0] & 0x3FFF) | (cpui[0] & 0x3FF8000) >> 2 | (cpui[1] & 0xff) << 24;
}

string CpuInfo::vendor() const {
	// hypervisor flag false, try to get the vendor name, see if it's a virtual cpu
	int cpui[4] = {0};
	__cpuid(cpui, 0x0);
	return string(reinterpret_cast<const char *>(cpui), 12);
}

} /* namespace license */