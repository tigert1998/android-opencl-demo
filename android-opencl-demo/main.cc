#include <CL/opencl.h>
#include <stdint.h>

#include <iostream>
#include <vector>

std::string GetPlatformInfo(cl_platform_id platform_id,
                            cl_platform_info param_name) {
  const uint32_t N = 1 << 10;
  char buf[N];
  uint64_t size;
  auto ret = clGetPlatformInfo(platform_id, param_name, N, buf, &size);
  if (ret != CL_SUCCESS) {
    fprintf(stderr, "clGetPlatformInfo = %d\n", ret);
    exit(1);
  }
  return std::string(buf, buf + size);
}

void LogCLPlatformsInfo() {
  const uint32_t N = 1 << 5;
  cl_platform_id platform_ids[N];
  uint32_t num_platforms;

  auto ret = clGetPlatformIDs(N, platform_ids, &num_platforms);
  if (ret != CL_SUCCESS) {
    fprintf(stderr, "clGetPlatformIDs = %d\n", ret);
    exit(1);
  }

  for (int i = 0; i < num_platforms; i++) {
    for (auto pair : std::vector<std::pair<std::string, uint32_t>>({
             {"CL_PLATFORM_PROFILE", CL_PLATFORM_PROFILE},
             {"CL_PLATFORM_VERSION", CL_PLATFORM_VERSION},
             {"CL_PLATFORM_NAME", CL_PLATFORM_NAME},
             {"CL_PLATFORM_VENDOR", CL_PLATFORM_VENDOR},
             {"CL_PLATFORM_EXTENSIONS", CL_PLATFORM_EXTENSIONS},
         })) {
      auto str = GetPlatformInfo(platform_ids[i], pair.second);
      fprintf(stdout, "%s:\n%s\n\n", pair.first.c_str(), str.c_str());
      fflush(stdout);
    }
  }
}

int main() {
  fprintf(stdout, "[Android OpenCL Demo]\n");
  fflush(stdout);

  LogCLPlatformsInfo();
  return 0;
}